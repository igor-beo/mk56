/**
 * MK56 Emulator - ncurses UI
 */

#include "mk56emu.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ============================================================================
// UI LAYOUT
// ============================================================================

#define WIN_STACK_W     24
#define WIN_REGS_W      24
#define WIN_PROG_W      32
#define WIN_STATUS_H    3
#define WIN_INPUT_H     3

typedef enum {
    MODE_NORMAL,
    MODE_INPUT_X,       // Entering value for X register
    MODE_INPUT_REG,     // Entering register number
    MODE_INPUT_REGVAL   // Entering value for selected register
} InputMode;

typedef struct {
    MK56VM *vm;
    
    WINDOW *win_stack;      // Stack display
    WINDOW *win_regs;       // Registers display
    WINDOW *win_prog;       // Program listing
    WINDOW *win_status;     // Status bar
    WINDOW *win_input;      // Input line
    WINDOW *win_help;       // Help window
    
    int term_h, term_w;
    int prog_scroll;        // Program view scroll offset
    bool show_help;
    char input_buf[64];
    int input_pos;
    InputMode mode;
    int edit_reg;           // Register being edited (0-13)
    
} MK56UI;

static MK56UI ui;

// ============================================================================
// DRAWING
// ============================================================================

static void draw_box(WINDOW *win, const char *title) {
    box(win, 0, 0);
    if (title) {
        int w = getmaxx(win);
        int len = strlen(title);
        mvwprintw(win, 0, (w - len - 2) / 2, " %s ", title);
    }
}

static void draw_stack(void) {
    werase(ui.win_stack);
    draw_box(ui.win_stack, "Stack");
    
    const char *names[] = {"X", "Y", "Z", "T"};
    for (int i = 0; i < 4; i++) {
        double val = vm_get_stack(ui.vm, i);
        if (i == 0) wattron(ui.win_stack, A_BOLD);
        mvwprintw(ui.win_stack, 2 + i, 2, "%s: %12.6g", names[i], val);
        if (i == 0) wattroff(ui.win_stack, A_BOLD);
    }
    
    mvwprintw(ui.win_stack, 7, 2, "LastX: %10.6g", ui.vm->lastx);
    
    wrefresh(ui.win_stack);
}

static void draw_registers(void) {
    werase(ui.win_regs);
    draw_box(ui.win_regs, "Registers");
    
    for (int i = 0; i < 14; i++) {
        double val = vm_get_reg(ui.vm, i);
        char name[4];
        if (i < 10) snprintf(name, sizeof(name), "R%d", i);
        else snprintf(name, sizeof(name), "R%c", 'A' + i - 10);
        
        int row = 2 + (i % 7);
        int col = (i < 7) ? 2 : 13;
        
        if (val != 0) wattron(ui.win_regs, A_BOLD);
        mvwprintw(ui.win_regs, row, col, "%s:%7.3g", name, val);
        if (val != 0) wattroff(ui.win_regs, A_BOLD);
    }
    
    wrefresh(ui.win_regs);
}

static void draw_program(void) {
    werase(ui.win_prog);
    draw_box(ui.win_prog, "Program");
    
    int h = getmaxy(ui.win_prog) - 2;
    int addr = ui.prog_scroll;
    
    // Auto-scroll to keep PC visible
    if ((int)ui.vm->pc < ui.prog_scroll) {
        ui.prog_scroll = ui.vm->pc;
        addr = ui.prog_scroll;
    } else if ((int)ui.vm->pc >= ui.prog_scroll + h) {
        ui.prog_scroll = ui.vm->pc - h + 1;
        addr = ui.prog_scroll;
    }
    
    for (int row = 0; row < h && addr < (int)ui.vm->program_size; row++) {
        char disasm[32];
        int size = vm_disasm(ui.vm, addr, disasm, sizeof(disasm));
        
        bool is_pc = (addr == ui.vm->pc);
        bool is_bp = ui.vm->breakpoints[addr];
        
        if (is_pc) wattron(ui.win_prog, A_REVERSE);
        if (is_bp) wattron(ui.win_prog, A_BOLD | COLOR_PAIR(1));
        
        mvwprintw(ui.win_prog, row + 1, 1, "%c%03d: %-20s",
            is_bp ? '*' : ' ', addr, disasm);
        
        if (is_pc) wattroff(ui.win_prog, A_REVERSE);
        if (is_bp) wattroff(ui.win_prog, A_BOLD | COLOR_PAIR(1));
        
        addr += size;
    }
    
    wrefresh(ui.win_prog);
}

static void draw_status(void) {
    werase(ui.win_status);
    
    // State
    const char *state_str;
    int color = 0;
    switch (ui.vm->state) {
        case VM_STOPPED: state_str = "STOPPED"; color = 3; break;
        case VM_RUNNING: state_str = "RUNNING"; color = 2; break;
        case VM_HALTED:  state_str = "HALTED";  color = 3; break;
        case VM_ERROR:   state_str = "ERROR";   color = 1; break;
        default: state_str = "???"; break;
    }
    
    wattron(ui.win_status, COLOR_PAIR(color) | A_BOLD);
    mvwprintw(ui.win_status, 0, 1, "[%s]", state_str);
    wattroff(ui.win_status, COLOR_PAIR(color) | A_BOLD);
    
    // PC and cycles
    mvwprintw(ui.win_status, 0, 14, "PC:%03d  Cycles:%llu",
        ui.vm->pc, (unsigned long long)ui.vm->cycles);
    
    // Error message
    if (ui.vm->error != ERR_NONE) {
        wattron(ui.win_status, COLOR_PAIR(1));
        mvwprintw(ui.win_status, 1, 1, "Error: %s", vm_error_str(ui.vm->error));
        wattroff(ui.win_status, COLOR_PAIR(1));
    }
    
    // Help hint
    mvwprintw(ui.win_status, 1, ui.term_w - 20, "Press ? for help");
    
    wrefresh(ui.win_status);
}

static const char* reg_name(int r) {
    static char buf[4];
    if (r < 10) snprintf(buf, sizeof(buf), "R%d", r);
    else snprintf(buf, sizeof(buf), "R%c", 'A' + r - 10);
    return buf;
}

static void draw_input(void) {
    werase(ui.win_input);
    draw_box(ui.win_input, NULL);
    
    switch (ui.mode) {
        case MODE_INPUT_X:
            mvwprintw(ui.win_input, 1, 2, "X = %s_", ui.input_buf);
            break;
        case MODE_INPUT_REG:
            mvwprintw(ui.win_input, 1, 2, "Edit register (0-9, A-D): %s_", ui.input_buf);
            break;
        case MODE_INPUT_REGVAL:
            mvwprintw(ui.win_input, 1, 2, "%s = %s_", reg_name(ui.edit_reg), ui.input_buf);
            break;
        default:
            mvwprintw(ui.win_input, 1, 2, "X = %.10g", vm_get_x(ui.vm));
            break;
    }
    
    wrefresh(ui.win_input);
}

static void draw_help(void) {
    if (!ui.show_help) return;
    
    int h = 18, w = 50;
    int y = (ui.term_h - h) / 2;
    int x = (ui.term_w - w) / 2;
    
    if (!ui.win_help) {
        ui.win_help = newwin(h, w, y, x);
    }
    
    werase(ui.win_help);
    draw_box(ui.win_help, "Help");
    
    mvwprintw(ui.win_help, 2, 3, "SPACE / s  - Step one instruction");
    mvwprintw(ui.win_help, 3, 3, "r          - Run until halt/break");
    mvwprintw(ui.win_help, 4, 3, "R          - Reset VM");
    mvwprintw(ui.win_help, 5, 3, "i          - Input value to X");
    mvwprintw(ui.win_help, 6, 3, "e          - Edit register value");
    mvwprintw(ui.win_help, 7, 3, "b          - Toggle breakpoint at PC");
    mvwprintw(ui.win_help, 8, 3, "c          - Clear all breakpoints");
    mvwprintw(ui.win_help, 9, 3, "UP/DOWN    - Scroll program");
    mvwprintw(ui.win_help, 10, 3, "g          - Go to PC");
    mvwprintw(ui.win_help, 11, 3, "0-9        - Quick input digit");
    mvwprintw(ui.win_help, 12, 3, "?          - Toggle this help");
    mvwprintw(ui.win_help, 13, 3, "q          - Quit");
    mvwprintw(ui.win_help, 14, 3, "ESC        - Cancel input");
    
    mvwprintw(ui.win_help, h - 2, (w - 22) / 2, "Press any key to close");
    
    wrefresh(ui.win_help);
}

static void draw_all(void) {
    draw_stack();
    draw_registers();
    draw_program();
    draw_status();
    draw_input();
    if (ui.show_help) draw_help();
}

// ============================================================================
// INPUT HANDLING
// ============================================================================

static void reset_input(void) {
    ui.mode = MODE_NORMAL;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
}

static int parse_reg_name(const char *s) {
    if (!s || !s[0]) return -1;
    char c = toupper((unsigned char)s[0]);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'D') return 10 + c - 'A';
    return -1;
}

static void handle_input_char(int ch) {
    if (ch == 27) {  // ESC - cancel
        reset_input();
        return;
    }
    
    if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
        if (ui.input_pos > 0) {
            ui.input_buf[--ui.input_pos] = '\0';
        }
        return;
    }
    
    if (ch == '\n' || ch == KEY_ENTER) {
        // Submit based on mode
        switch (ui.mode) {
            case MODE_INPUT_X:
                if (ui.input_buf[0]) {
                    vm_input(ui.vm, atof(ui.input_buf));
                }
                reset_input();
                break;
                
            case MODE_INPUT_REG: {
                int reg = parse_reg_name(ui.input_buf);
                if (reg >= 0 && reg < 14) {
                    ui.edit_reg = reg;
                    ui.mode = MODE_INPUT_REGVAL;
                    ui.input_buf[0] = '\0';
                    ui.input_pos = 0;
                } else {
                    reset_input();  // Invalid register
                }
                break;
            }
            
            case MODE_INPUT_REGVAL:
                if (ui.input_buf[0]) {
                    ui.vm->regs[ui.edit_reg] = atof(ui.input_buf);
                }
                reset_input();
                break;
                
            default:
                reset_input();
                break;
        }
        return;
    }
    
    // Accept input characters
    bool accept = false;
    if (ui.mode == MODE_INPUT_REG) {
        // Register names: 0-9, A-D
        accept = isdigit(ch) || (toupper(ch) >= 'A' && toupper(ch) <= 'D');
    } else {
        // Numeric input
        accept = isdigit(ch) || ch == '.' || ch == '-' || ch == 'e' || ch == 'E' || ch == '+';
    }
    
    if (accept && ui.input_pos < (int)sizeof(ui.input_buf) - 1) {
        ui.input_buf[ui.input_pos++] = ch;
        ui.input_buf[ui.input_pos] = '\0';
    }
}

static void handle_key(int ch) {
    if (ui.mode != MODE_NORMAL) {
        handle_input_char(ch);
        return;
    }
    
    if (ui.show_help) {
        ui.show_help = false;
        if (ui.win_help) {
            delwin(ui.win_help);
            ui.win_help = NULL;
        }
        touchwin(stdscr);
        draw_all();
        return;
    }
    
    switch (ch) {
        case 'q':
        case 'Q':
            endwin();
            exit(0);
            break;
            
        case '?':
            ui.show_help = true;
            break;
            
        case ' ':
        case 's':
            vm_step(ui.vm);
            break;
            
        case 'r':
            vm_run(ui.vm);
            break;
            
        case 'R':
            vm_reset(ui.vm);
            break;
            
        case 'i':
            ui.mode = MODE_INPUT_X;
            ui.input_buf[0] = '\0';
            ui.input_pos = 0;
            break;
            
        case 'e':
            ui.mode = MODE_INPUT_REG;
            ui.input_buf[0] = '\0';
            ui.input_pos = 0;
            break;
            
        case 'b':
            vm_set_breakpoint(ui.vm, ui.vm->pc, !ui.vm->breakpoints[ui.vm->pc]);
            break;
            
        case 'c':
            memset(ui.vm->breakpoints, 0, sizeof(ui.vm->breakpoints));
            break;
            
        case KEY_UP:
            if (ui.prog_scroll > 0) ui.prog_scroll--;
            break;
            
        case KEY_DOWN:
            ui.prog_scroll++;
            break;
            
        case KEY_PPAGE:
            ui.prog_scroll -= 10;
            if (ui.prog_scroll < 0) ui.prog_scroll = 0;
            break;
            
        case KEY_NPAGE:
            ui.prog_scroll += 10;
            break;
            
        case 'g':
            ui.prog_scroll = ui.vm->pc;
            break;
            
        // Quick digit input
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            vm_input(ui.vm, ch - '0');
            break;
            
        case '.':
            ui.mode = MODE_INPUT_X;
            ui.input_buf[0] = '0';
            ui.input_buf[1] = '.';
            ui.input_buf[2] = '\0';
            ui.input_pos = 2;
            break;
    }
}

// ============================================================================
// MAIN UI LOOP
// ============================================================================

void ui_init(MK56VM *vm) {
    ui.vm = vm;
    ui.prog_scroll = 0;
    ui.show_help = false;
    ui.mode = MODE_NORMAL;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Colors
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
    }
    
    getmaxyx(stdscr, ui.term_h, ui.term_w);
    
    // Create windows
    int prog_h = ui.term_h - WIN_STATUS_H - WIN_INPUT_H;
    int left_w = WIN_STACK_W;
    int right_x = left_w;
    
    ui.win_stack = newwin(9, left_w, 0, 0);
    ui.win_regs = newwin(prog_h - 9, left_w, 9, 0);
    ui.win_prog = newwin(prog_h, ui.term_w - left_w, 0, right_x);
    ui.win_status = newwin(WIN_STATUS_H, ui.term_w, prog_h, 0);
    ui.win_input = newwin(WIN_INPUT_H, ui.term_w, prog_h + WIN_STATUS_H, 0);
    ui.win_help = NULL;
    
    refresh();
}

void ui_run(void) {
    while (1) {
        draw_all();
        int ch = getch();
        handle_key(ch);
    }
}

void ui_cleanup(void) {
    if (ui.win_stack) delwin(ui.win_stack);
    if (ui.win_regs) delwin(ui.win_regs);
    if (ui.win_prog) delwin(ui.win_prog);
    if (ui.win_status) delwin(ui.win_status);
    if (ui.win_input) delwin(ui.win_input);
    if (ui.win_help) delwin(ui.win_help);
    endwin();
}

// External declarations for main.c
void ui_init(MK56VM *vm);
void ui_run(void);
void ui_cleanup(void);
