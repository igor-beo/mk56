/**
 * MK56 Emulator - Turbo C Style ncurses UI
 * 
 * Classic Borland Turbo C aesthetic with popup dialogs,
 * menu bar, and DOS-era color scheme.
 */

#include "mk56emu.h"
#include "mk56asm.h"
#include <locale.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <panel.h>
#include <math.h>

// ============================================================================
// COLOR SCHEME (Turbo C style)
// ============================================================================

#define COL_DESKTOP     1   // Blue background
#define COL_MENU        2   // Menu bar (white on black)
#define COL_MENU_HOT    3   // Menu hotkey (red on black)
#define COL_WINDOW      4   // Window (black on cyan)
#define COL_WINDOW_TITLE 5  // Window title (white on cyan)
#define COL_DIALOG      6   // Dialog (black on white)
#define COL_DIALOG_TITLE 7  // Dialog title (white on blue)
#define COL_INPUT       8   // Input field (white on blue)
#define COL_BUTTON      9   // Button (black on green)
#define COL_BUTTON_HOT  10  // Button hotkey
#define COL_STATUS      11  // Status bar (white on black)
#define COL_STATUS_HOT  12  // Status bar hotkey (yellow on black)
#define COL_HIGHLIGHT   13  // Highlighted line (white on blue)
#define COL_ERROR       14  // Error text (white on red)
#define COL_SHADOW      15  // Shadow (black on black)
#define COL_DISPLAY     16  // VFD display (green on black)
#define COL_DISPLAY_DIM 17  // Dim display segments
// Syntax highlighting colors
#define COL_SYN_ADDR    18  // Address (cyan)
#define COL_SYN_OPCODE  19  // Opcode/instruction (yellow)
#define COL_SYN_REG     20  // Register operand (green)
#define COL_SYN_NUM     21  // Number operand (magenta)
#define COL_SYN_LABEL   22  // Label/address target (cyan)

// ============================================================================
// UI STATE
// ============================================================================

typedef enum {
    MODE_NORMAL,
    MODE_DIALOG_INPUT_X,
    MODE_DIALOG_INPUT_REG,
    MODE_DIALOG_INPUT_REGVAL,
    MODE_DIALOG_GOTO,
    MODE_DIALOG_HELP,
    MODE_EDIT_PROGRAM,        // Edit program in place
    MODE_MENU_FILE,
    MODE_MENU_RUN,
    MODE_MENU_DEBUG,
    MODE_MENU_HELP
} UIMode;

typedef struct {
    MK56VM *vm;
    
    WINDOW *win_desktop;    // Blue desktop background
    WINDOW *win_menu;       // Top menu bar
    WINDOW *win_display;    // Vacuum-fluorescent display (X)
    WINDOW *win_stack;      // Stack window
    WINDOW *win_regs;       // Registers window
    WINDOW *win_prog;       // Program window
    WINDOW *win_status;     // Bottom status bar
    WINDOW *win_dialog;     // Popup dialog
    WINDOW *win_shadow;     // Dialog shadow
    
    PANEL *pan_dialog;
    PANEL *pan_shadow;
    
    int term_h, term_w;
    int prog_scroll;
    
    UIMode mode;
    char input_buf[64];
    int input_pos;
    int edit_reg;
    
    // Menu state
    int menu_sel;           // Selected menu item index
    int menu_count;         // Number of items in current menu
    int menu_x;             // Menu X position
    const char **menu_items; // Current menu items
    
    // Program editing state
    int edit_line;          // Current line being edited in program
    char edit_buf[64];      // Edit buffer for current instruction
    int edit_cursor;        // Cursor position in edit buffer (bytes)
    char status_msg[80];    // Last edit error
    
} MK56UI;

static MK56UI ui;

// ============================================================================
// INITIALIZATION
// ============================================================================

static void init_colors(void) {
    start_color();
    use_default_colors();
    
    // Define color pairs - Dark blue background with yellow/white borders
    init_pair(COL_DESKTOP,     COLOR_WHITE,  COLOR_BLUE);
    init_pair(COL_MENU,        COLOR_BLACK,  COLOR_WHITE);
    init_pair(COL_MENU_HOT,    COLOR_RED,    COLOR_WHITE);
    init_pair(COL_WINDOW,      COLOR_WHITE,  COLOR_BLUE);   // White on dark blue
    init_pair(COL_WINDOW_TITLE,COLOR_YELLOW, COLOR_BLUE);   // Yellow titles
    init_pair(COL_DIALOG,      COLOR_BLACK,  COLOR_WHITE);
    init_pair(COL_DIALOG_TITLE,COLOR_WHITE,  COLOR_BLUE);
    init_pair(COL_INPUT,       COLOR_WHITE,  COLOR_BLUE);
    init_pair(COL_BUTTON,      COLOR_BLACK,  COLOR_GREEN);
    init_pair(COL_BUTTON_HOT,  COLOR_RED,    COLOR_GREEN);
    init_pair(COL_STATUS,      COLOR_WHITE,  COLOR_BLACK);  // White on black
    init_pair(COL_STATUS_HOT,  COLOR_YELLOW, COLOR_BLACK);  // Yellow hotkeys
    init_pair(COL_HIGHLIGHT,   COLOR_YELLOW, COLOR_BLUE);   // Yellow highlight
    init_pair(COL_ERROR,       COLOR_WHITE,  COLOR_RED);
    init_pair(COL_SHADOW,      COLOR_BLACK,  COLOR_BLACK);
    init_pair(COL_DISPLAY,     COLOR_GREEN,  COLOR_BLACK);  // Green VFD on black
    init_pair(COL_DISPLAY_DIM, COLOR_BLACK,  COLOR_BLACK);
    // Syntax highlighting
    init_pair(COL_SYN_ADDR,    COLOR_CYAN,   COLOR_BLUE);   // Address
    init_pair(COL_SYN_OPCODE,  COLOR_YELLOW, COLOR_BLUE);   // Opcode
    init_pair(COL_SYN_REG,     COLOR_GREEN,  COLOR_BLUE);   // Register
    init_pair(COL_SYN_NUM,     COLOR_MAGENTA,COLOR_BLUE);   // Number
    init_pair(COL_SYN_LABEL,   COLOR_CYAN,   COLOR_BLUE);   // Label/jump target
}

// ============================================================================
// DRAWING UTILITIES
// ============================================================================

static void draw_window_frame(WINDOW *win, const char *title, int color_pair) {
    int h, w;
    getmaxyx(win, h, w);
    
    wbkgd(win, COLOR_PAIR(color_pair));
    werase(win);
    
    // Draw border using ncurses ACS characters (yellow on blue)
    wattron(win, COLOR_PAIR(COL_WINDOW_TITLE) | A_BOLD);
    
    // Use ACS box drawing characters (portable)
    mvwaddch(win, 0, 0, ACS_ULCORNER);
    for (int i = 1; i < w - 1; i++) mvwaddch(win, 0, i, ACS_HLINE);
    mvwaddch(win, 0, w - 1, ACS_URCORNER);
    
    mvwaddch(win, h - 1, 0, ACS_LLCORNER);
    for (int i = 1; i < w - 1; i++) mvwaddch(win, h - 1, i, ACS_HLINE);
    mvwaddch(win, h - 1, w - 1, ACS_LRCORNER);
    
    for (int i = 1; i < h - 1; i++) {
        mvwaddch(win, i, 0, ACS_VLINE);
        mvwaddch(win, i, w - 1, ACS_VLINE);
    }
    
    // Title in yellow
    if (title) {
        int title_len = strlen(title);
        int title_x = (w - title_len - 2) / 2;
        if (title_x < 2) title_x = 2;
        mvwprintw(win, 0, title_x, " %s ", title);
    }
    
    wattroff(win, COLOR_PAIR(COL_WINDOW_TITLE) | A_BOLD);
}

static void draw_button(WINDOW *win, int y, int x, const char *label, bool selected) {
    if (selected) {
        wattron(win, COLOR_PAIR(COL_BUTTON) | A_BOLD);
    } else {
        wattron(win, COLOR_PAIR(COL_DIALOG));
    }
    mvwprintw(win, y, x, "[ %s ]", label);
    if (selected) {
        wattroff(win, COLOR_PAIR(COL_BUTTON) | A_BOLD);
    } else {
        wattroff(win, COLOR_PAIR(COL_DIALOG));
    }
}

static void draw_input_field(WINDOW *win, int y, int x, int width, 
                             const char *value, bool active) {
    if (active) {
        wattron(win, COLOR_PAIR(COL_INPUT));
    } else {
        wattron(win, COLOR_PAIR(COL_DIALOG) | A_REVERSE);
    }
    
    mvwprintw(win, y, x, " ");
    for (int i = 0; i < width - 2; i++) {
        if (value && i < (int)strlen(value)) {
            waddch(win, value[i]);
        } else {
            waddch(win, ' ');
        }
    }
    waddch(win, ' ');
    
    // Cursor
    if (active && value) {
        int cursor_pos = x + 1 + strlen(value);
        if (cursor_pos < x + width - 1) {
            mvwaddch(win, y, cursor_pos, '_' | A_BLINK);
        }
    }
    
    if (active) {
        wattroff(win, COLOR_PAIR(COL_INPUT));
    } else {
        wattroff(win, COLOR_PAIR(COL_DIALOG) | A_REVERSE);
    }
}

// ============================================================================
// MAIN WINDOWS
// ============================================================================

static void draw_desktop(void) {
    wbkgd(ui.win_desktop, COLOR_PAIR(COL_DESKTOP));
    werase(ui.win_desktop);
    
    // Fill with pattern (optional - classic DOS look)
    wattron(ui.win_desktop, COLOR_PAIR(COL_DESKTOP));
    for (int y = 1; y < ui.term_h - 1; y++) {
        for (int x = 0; x < ui.term_w; x++) {
            mvwaddch(ui.win_desktop, y, x, ACS_CKBOARD);
        }
    }
    wattroff(ui.win_desktop, COLOR_PAIR(COL_DESKTOP));
    
    wrefresh(ui.win_desktop);
}

static void draw_menu_bar(void) {
    werase(ui.win_menu);
    wbkgd(ui.win_menu, COLOR_PAIR(COL_MENU));
    
    mvwprintw(ui.win_menu, 0, 1, " ");
    
    // Menu items with hotkeys
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    waddch(ui.win_menu, 'F');
    wattroff(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU));
    wprintw(ui.win_menu, "ile  ");
    
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    waddch(ui.win_menu, 'R');
    wattroff(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU));
    wprintw(ui.win_menu, "un  ");
    
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    waddch(ui.win_menu, 'D');
    wattroff(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU));
    wprintw(ui.win_menu, "ebug  ");
    
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    waddch(ui.win_menu, 'H');
    wattroff(ui.win_menu, COLOR_PAIR(COL_MENU_HOT));
    wattron(ui.win_menu, COLOR_PAIR(COL_MENU));
    wprintw(ui.win_menu, "elp");
    
    // Title centered
    const char *title = " MK-56 Emulator ";
    mvwprintw(ui.win_menu, 0, (ui.term_w - strlen(title)) / 2, "%s", title);
    
    wattroff(ui.win_menu, COLOR_PAIR(COL_MENU));
    wrefresh(ui.win_menu);
}

// 7-segment digits (3 rows, 4 chars wide)
static const char *BIG_DIGITS[16][3] = {
    {" __ ", "|  |", "|__|"},  // 0
    {"    ", "   |", "   |"},  // 1
    {" __ ", " __|", "|__ "},  // 2
    {" __ ", " __|", " __|"},  // 3
    {"    ", "|__|", "   |"},  // 4
    {" __ ", "|__ ", " __|"},  // 5
    {" __ ", "|__ ", "|__|"},  // 6
    {" __ ", "   |", "   |"},  // 7
    {" __ ", "|__|", "|__|"},  // 8
    {" __ ", "|__|", " __|"},  // 9
    {"    ", " -- ", "    "},  // - (minus)
    {"    ", "    ", " .  "},  // . (dot)
    {" __ ", "|__ ", "|__ "},  // E
    {"    ", "    ", "    "},  // space
    {"    ", " -| ", "    "},  // +
    {" __ ", "|   ", "|   "}   // Г (for ЕГГОГ)
};

static int char_to_digit_index(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == '-') return 10;
    if (c == '.') return 11;
    if (c == 'e' || c == 'E') return 12;
    if (c == '+') return 14;
    if (c == 'G') return 15;
    return 13;
}

static void draw_display(void) {
    int h, w;
    getmaxyx(ui.win_display, h, w);
    
    // Black background for the display
    wbkgd(ui.win_display, COLOR_PAIR(COL_DISPLAY));
    werase(ui.win_display);
    
    // Draw yellow border using ACS characters
    wattron(ui.win_display, COLOR_PAIR(COL_WINDOW_TITLE) | A_BOLD);
    mvwaddch(ui.win_display, 0, 0, ACS_ULCORNER);
    for (int i = 1; i < w - 1; i++) mvwaddch(ui.win_display, 0, i, ACS_HLINE);
    mvwaddch(ui.win_display, 0, w - 1, ACS_URCORNER);
    mvwaddch(ui.win_display, h - 1, 0, ACS_LLCORNER);
    for (int i = 1; i < w - 1; i++) mvwaddch(ui.win_display, h - 1, i, ACS_HLINE);
    mvwaddch(ui.win_display, h - 1, w - 1, ACS_LRCORNER);
    for (int i = 1; i < h - 1; i++) {
        mvwaddch(ui.win_display, i, 0, ACS_VLINE);
        mvwaddch(ui.win_display, i, w - 1, ACS_VLINE);
    }
    
    // Title
    mvwprintw(ui.win_display, 0, 2, " Display ");
    wattroff(ui.win_display, COLOR_PAIR(COL_WINDOW_TITLE) | A_BOLD);
    
    // Format X as the calculator shows it; ЕГГОГ on error
    char display_str[32];
    if (ui.vm->state == VM_ERROR) {
        snprintf(display_str, sizeof(display_str), "EGG0G");
    } else {
        char shown[40];
        size_t n = 0;
        vm_format_display(ui.vm, shown, sizeof(shown));
        for (const char *c = shown; *c && n + 1 < sizeof(display_str); c++)
            display_str[n++] = (*c == ',') ? '.' : *c;
        display_str[n] = '\0';
    }
    
    // Draw 7-segment digits with padding
    wattron(ui.win_display, COLOR_PAIR(COL_DISPLAY) | A_BOLD);
    
    int digit_width = 4;
    int num_len = strlen(display_str);
    int total_width = num_len * digit_width;
    int start_x = (w - total_width) / 2;
    if (start_x < 2) start_x = 2;
    int start_y = (h - 3) / 2;  // Center vertically (3 rows of digits)
    if (start_y < 1) start_y = 1;
    
    for (int i = 0; i < num_len && i < 16; i++) {
        int idx = char_to_digit_index(display_str[i]);
        for (int row = 0; row < 3; row++) {
            mvwprintw(ui.win_display, start_y + row, start_x + i * digit_width, 
                      "%s", BIG_DIGITS[idx][row]);
        }
    }
    
    wattroff(ui.win_display, COLOR_PAIR(COL_DISPLAY) | A_BOLD);
    
    wrefresh(ui.win_display);
}

// Helper to draw a single hotkey hint
static void draw_hotkey(const char *key, const char *label) {
    wattron(ui.win_status, COLOR_PAIR(COL_STATUS_HOT) | A_BOLD);
    wprintw(ui.win_status, "%s", key);
    wattroff(ui.win_status, COLOR_PAIR(COL_STATUS_HOT) | A_BOLD);
    wattron(ui.win_status, COLOR_PAIR(COL_STATUS));
    wprintw(ui.win_status, "%s ", label);
}

static void draw_status_bar(void) {
    werase(ui.win_status);
    wbkgd(ui.win_status, COLOR_PAIR(COL_STATUS));
    wattron(ui.win_status, COLOR_PAIR(COL_STATUS));
    
    wmove(ui.win_status, 0, 1);
    
    if (ui.mode == MODE_EDIT_PROGRAM) {
        // Edit mode hints
        draw_hotkey("Enter", "Insert");
        draw_hotkey("Esc", "Cancel");
        draw_hotkey("Up/Dn", "Move");
        
        wattron(ui.win_status, COLOR_PAIR(COL_STATUS_HOT) | A_BOLD);
        if (ui.status_msg[0]) {
            wattron(ui.win_status, COLOR_PAIR(COL_ERROR) | A_BOLD);
            const char *msg = strstr(ui.status_msg, ": ");   // drop "Line 1: "
            mvwprintw(ui.win_status, 0, 36, " %s ", msg ? msg + 2 : ui.status_msg);
            wattron(ui.win_status, COLOR_PAIR(COL_STATUS_HOT) | A_BOLD);
        }
        mvwprintw(ui.win_status, 0, ui.term_w - 30, "[EDIT] Step:%02d", ui.edit_line);
    } else {
        // Normal mode hints (F-keys only - Turbo C style)
        draw_hotkey("F1", "Help");
        draw_hotkey("F4", "Edit");
        draw_hotkey("F5", "Input");
        draw_hotkey("F6", "Brk");
        draw_hotkey("F7", "Step");
        draw_hotkey("F8", "Run");
        draw_hotkey("F9", "Reset");
        draw_hotkey("G", "Angle");
        draw_hotkey("Q", "uit");
    
        // VM state on right
        const char *state_str;
        int color = COL_STATUS;
        switch (ui.vm->state) {
            case VM_STOPPED: state_str = "STOPPED"; break;
            case VM_RUNNING: state_str = "RUNNING"; break;
            case VM_HALTED:  state_str = "HALTED";  break;
            case VM_ERROR:   state_str = "ERROR"; color = COL_ERROR; break;
            default: state_str = "???"; break;
        }
        
        wattron(ui.win_status, COLOR_PAIR(color) | A_BOLD);
        static const char *angles[] = { "RAD", "DEG", "GRD" };
        mvwprintw(ui.win_status, 0, ui.term_w - 30, "%s [%s] PC:%02d",
                  angles[ui.vm->angle], state_str, ui.vm->pc);
        wattroff(ui.win_status, COLOR_PAIR(color) | A_BOLD);
    }
    
    wattroff(ui.win_status, COLOR_PAIR(COL_STATUS));
    wrefresh(ui.win_status);
}

static void draw_stack_window(void) {
    draw_window_frame(ui.win_stack, " Stack ", COL_WINDOW);
    
    wattron(ui.win_stack, COLOR_PAIR(COL_WINDOW));
    
    const char *names[] = {"X", "Y", "Z", "T"};
    for (int i = 0; i < 4; i++) {
        double val = vm_get_stack(ui.vm, i);
        if (i == 0) wattron(ui.win_stack, A_BOLD);
        mvwprintw(ui.win_stack, 2 + i, 2, "%s: %14.8g", names[i], val);
        if (i == 0) wattroff(ui.win_stack, A_BOLD);
    }
    
    // Separator
    mvwaddch(ui.win_stack, 7, 0, ACS_LTEE);
    for (int i = 1; i < 23; i++) mvwaddch(ui.win_stack, 7, i, ACS_HLINE);
    mvwaddch(ui.win_stack, 7, 23, ACS_RTEE);
    
    mvwprintw(ui.win_stack, 8, 2, "X1: %14.8g", ui.vm->lastx);
    
    wattroff(ui.win_stack, COLOR_PAIR(COL_WINDOW));
    wrefresh(ui.win_stack);
}

// Format register value to fit in 7 columns, keeping as many digits as fit
static void format_reg_value(char *buf, size_t size, double v) {
    for (int digits = 7; digits >= 1; digits--) {
        char tmp[32], *e;
        snprintf(tmp, sizeof tmp, "%.*g", digits, v);
        // Compact the exponent: "e+07" -> "e7", "e-05" -> "e-5"
        if ((e = strchr(tmp, 'e')) != NULL) {
            char *d = e + 1, *src = e + 1;
            if (*src == '+') src++;
            else if (*src == '-') *d++ = *src++;
            while (*src == '0' && src[1]) src++;
            memmove(d, src, strlen(src) + 1);
        }
        if (strlen(tmp) <= 7 || digits == 1) {
            snprintf(buf, size, "%.7s", tmp);
            return;
        }
    }
}

static void draw_registers_window(void) {
    draw_window_frame(ui.win_regs, " Registers ", COL_WINDOW);
    
    wattron(ui.win_regs, COLOR_PAIR(COL_WINDOW));
    
    // Fixed columns: "R0:xxxxxxx R7:xxxxxxx"
    // Window is 26 wide, inside is 24
    // Col1: pos 1 (R0:+7chars=10), Col2: pos 13 (R7:+7chars=10)
    for (int i = 0; i < 7; i++) {
        double v1 = vm_get_reg(ui.vm, i);
        double v2 = vm_get_reg(ui.vm, i + 7);
        
        char n1[4], n2[4], val1[10], val2[10];
        if (i < 10) snprintf(n1, sizeof(n1), "R%d", i);
        else snprintf(n1, sizeof(n1), "R%c", 'A' + i - 10);
        
        int j = i + 7;
        if (j < 10) snprintf(n2, sizeof(n2), "R%d", j);
        else snprintf(n2, sizeof(n2), "R%c", 'A' + j - 10);
        
        format_reg_value(val1, sizeof(val1), v1);
        format_reg_value(val2, sizeof(val2), v2);
        
        // Print at fixed positions
        mvwprintw(ui.win_regs, 2 + i, 1, "%s:%7s", n1, val1);
        mvwprintw(ui.win_regs, 2 + i, 13, "%s:%7s", n2, val2);
    }
    
    wattroff(ui.win_regs, COLOR_PAIR(COL_WINDOW));
    wrefresh(ui.win_regs);
}

// Draw a single instruction with syntax highlighting
static void draw_instruction_highlighted(WINDOW *win, int row, int col, 
                                          const char *disasm, bool is_pc) {
    // Parse: "OPCODE" or "OPCODE ARG"
    char opcode[16] = {0}, arg[16] = {0};
    int n = sscanf(disasm, "%15s %15s", opcode, arg);
    bool is_reg = arg[0] == '(' || (arg[0] == 'R' && arg[1]);
    
    int x = col;
    
    // Draw opcode (yellow)
    if (is_pc) {
        wattron(win, COLOR_PAIR(COL_HIGHLIGHT) | A_BOLD);
    } else {
        wattron(win, COLOR_PAIR(COL_SYN_OPCODE) | A_BOLD);
    }
    mvwprintw(win, row, x, "%-6s", opcode);
    x += 6;
    
    if (n >= 2 && arg[0]) {
        // Determine argument type and color
        int arg_color = is_reg ? COL_SYN_REG : COL_SYN_LABEL;
        
        if (is_pc) {
            wattron(win, COLOR_PAIR(COL_HIGHLIGHT) | A_BOLD);
        } else {
            wattroff(win, A_BOLD);
            wattron(win, COLOR_PAIR(arg_color));
        }
        mvwprintw(win, row, x, "%s", arg);
    }
    
    wattroff(win, A_BOLD);
}

static void draw_program_window(void) {
    draw_window_frame(ui.win_prog, " Program ", COL_WINDOW);
    
    int h, w;
    getmaxyx(ui.win_prog, h, w);
    int visible_lines = h - 2;
    
    // Auto-scroll to keep PC visible
    if ((int)ui.vm->pc < ui.prog_scroll) {
        ui.prog_scroll = ui.vm->pc;
    } else if ((int)ui.vm->pc >= ui.prog_scroll + visible_lines) {
        ui.prog_scroll = ui.vm->pc - visible_lines + 1;
    }
    
    uint16_t addr = 0;
    int line = 0;
    int display_line = 0;
    
    // In edit mode, also scroll to keep edit line visible
    if (ui.mode == MODE_EDIT_PROGRAM) {
        if (ui.edit_line < ui.prog_scroll) {
            ui.prog_scroll = ui.edit_line;
        } else if (ui.edit_line >= ui.prog_scroll + visible_lines) {
            ui.prog_scroll = ui.edit_line - visible_lines + 1;
        }
    }
    
    while (addr < MK56_PROGRAM_SIZE && display_line < visible_lines) {
        char disasm[32], key[40], codes[8];
        int size = vm_disasm(ui.vm, addr, disasm, sizeof(disasm));
        mk56_disasm(ui.vm->program, addr, false, key, sizeof(key));
        if (size == 2) {
            snprintf(codes, sizeof(codes), "%02X %02X", ui.vm->program[addr],
                     ui.vm->program[(addr + 1) % MK56_PROGRAM_SIZE]);
        } else {
            snprintf(codes, sizeof(codes), "%02X", ui.vm->program[addr]);
        }
        
        if (line >= ui.prog_scroll) {
            int row = 1 + display_line;
            bool is_pc = (addr == ui.vm->pc);
            bool is_bp = ui.vm->breakpoints[addr];
            bool is_edit = (ui.mode == MODE_EDIT_PROGRAM && (int)addr == ui.edit_line);
            
            // Clear the line first: original notation is UTF-8, so columns
            // are placed absolutely rather than padded
            wattron(ui.win_prog, COLOR_PAIR(COL_WINDOW));
            mvwhline(ui.win_prog, row, 1, ' ', w - 2);
            
            char marker = is_bp ? '*' : (is_pc ? '>' : (is_edit ? '#' : ' '));
            
            if (is_edit) {
                wattron(ui.win_prog, COLOR_PAIR(COL_INPUT) | A_BOLD);
                mvwprintw(ui.win_prog, row, 1, "%c%02d: ", marker, addr);
                wattron(ui.win_prog, COLOR_PAIR(COL_INPUT));
                mvwhline(ui.win_prog, row, 6, ' ', w - 8);
                mvwprintw(ui.win_prog, row, 6, "%s", ui.edit_buf);
                
                // Cursor column counts characters, not UTF-8 bytes
                int col = 0;
                for (int i = 0; i < ui.edit_cursor; i++)
                    if ((ui.edit_buf[i] & 0xC0) != 0x80) col++;
                mvwaddch(ui.win_prog, row, 6 + col, '_' | A_BLINK);
            } else {
                int color = is_pc ? COL_HIGHLIGHT : COL_SYN_ADDR;
                wattron(ui.win_prog, COLOR_PAIR(color) | (is_pc ? A_BOLD : 0));
                mvwprintw(ui.win_prog, row, 1, "%c%02d: ", marker, addr);
                mvwprintw(ui.win_prog, row, 6, "%s", codes);
                wattroff(ui.win_prog, A_BOLD);
                wattron(ui.win_prog, COLOR_PAIR(is_pc ? COL_HIGHLIGHT : COL_SYN_NUM));
                mvwprintw(ui.win_prog, row, 13, "%s", key);
                draw_instruction_highlighted(ui.win_prog, row, 25, disasm, is_pc);
            }
            
            display_line++;
        }
        
        addr += size;
        line++;
    }
    
    wattroff(ui.win_prog, COLOR_PAIR(COL_WINDOW));
    wrefresh(ui.win_prog);
}

// ============================================================================
// POPUP DIALOGS
// ============================================================================

static void show_dialog(const char *title, const char *prompt, int width, int height) {
    int y = (ui.term_h - height) / 2;
    int x = (ui.term_w - width) / 2;
    
    // Create shadow
    if (ui.win_shadow) delwin(ui.win_shadow);
    ui.win_shadow = newwin(height, width, y + 1, x + 2);
    wbkgd(ui.win_shadow, COLOR_PAIR(COL_SHADOW));
    werase(ui.win_shadow);
    
    // Create dialog
    if (ui.win_dialog) delwin(ui.win_dialog);
    ui.win_dialog = newwin(height, width, y, x);
    
    // Draw dialog frame
    wbkgd(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    werase(ui.win_dialog);
    
    // Border
    wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    box(ui.win_dialog, 0, 0);
    
    // Title bar
    wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG_TITLE));
    mvwhline(ui.win_dialog, 0, 1, ' ', width - 2);
    int title_x = (width - strlen(title)) / 2;
    mvwprintw(ui.win_dialog, 0, title_x, " %s ", title);
    wattroff(ui.win_dialog, COLOR_PAIR(COL_DIALOG_TITLE));
    
    // Prompt
    wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    mvwprintw(ui.win_dialog, 2, 2, "%s", prompt);
    wattroff(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    
    // Refresh shadow first, then dialog
    wrefresh(ui.win_shadow);
    wrefresh(ui.win_dialog);
}

static void update_dialog_input(void) {
    if (!ui.win_dialog) return;
    
    int w = getmaxx(ui.win_dialog);
    
    // Draw input field
    draw_input_field(ui.win_dialog, 3, 2, w - 4, ui.input_buf, true);
    
    // Draw buttons
    int btn_y = 5;
    draw_button(ui.win_dialog, btn_y, w/2 - 12, "OK", true);
    draw_button(ui.win_dialog, btn_y, w/2 + 2, "Cancel", false);
    
    wrefresh(ui.win_dialog);
}

static void draw_all(void);  // Forward declaration

static void close_dialog(void) {
    if (ui.win_dialog) {
        werase(ui.win_dialog);
        wrefresh(ui.win_dialog);
        delwin(ui.win_dialog);
        ui.win_dialog = NULL;
    }
    if (ui.win_shadow) {
        werase(ui.win_shadow);
        wrefresh(ui.win_shadow);
        delwin(ui.win_shadow);
        ui.win_shadow = NULL;
    }
    
    ui.mode = MODE_NORMAL;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
    
    // Redraw ALL windows properly
    touchwin(ui.win_desktop);
    touchwin(ui.win_display);
    touchwin(ui.win_stack);
    touchwin(ui.win_regs);
    touchwin(ui.win_prog);
    touchwin(ui.win_menu);
    touchwin(ui.win_status);
    draw_all();
}

static void open_input_x_dialog(void) {
    ui.mode = MODE_DIALOG_INPUT_X;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
    
    show_dialog("Input Value", "Enter value for X register:", 40, 8);
    update_dialog_input();
}

// ============================================================================
// DROPDOWN MENUS
// ============================================================================

static void redraw_menu(void) {
    if (!ui.win_dialog || !ui.menu_items) return;
    
    int width = 24;
    
    wbkgd(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    werase(ui.win_dialog);
    box(ui.win_dialog, 0, 0);
    
    for (int i = 0; i < ui.menu_count; i++) {
        if (ui.menu_items[i][0] == '-') {
            // Separator line
            wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
            mvwaddch(ui.win_dialog, i + 1, 0, ACS_LTEE);
            for (int j = 1; j < width - 1; j++) 
                mvwaddch(ui.win_dialog, i + 1, j, ACS_HLINE);
            mvwaddch(ui.win_dialog, i + 1, width - 1, ACS_RTEE);
            wattroff(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
        } else {
            // Menu item - highlight if selected
            if (i == ui.menu_sel) {
                wattron(ui.win_dialog, COLOR_PAIR(COL_HIGHLIGHT) | A_BOLD);
                mvwhline(ui.win_dialog, i + 1, 1, ' ', width - 2);
                mvwprintw(ui.win_dialog, i + 1, 2, "%s", ui.menu_items[i]);
                wattroff(ui.win_dialog, COLOR_PAIR(COL_HIGHLIGHT) | A_BOLD);
            } else {
                wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
                mvwprintw(ui.win_dialog, i + 1, 2, "%s", ui.menu_items[i]);
                wattroff(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
            }
        }
    }
    
    wrefresh(ui.win_dialog);
}

static void show_dropdown_menu(int x, const char *title, const char **items, int count) {
    (void)title;  // Unused
    
    int width = 24;
    int height = count + 2;
    
    // Store menu state
    ui.menu_items = items;
    ui.menu_count = count;
    ui.menu_x = x;
    ui.menu_sel = 0;
    
    // Skip separator for initial selection
    while (ui.menu_sel < count && items[ui.menu_sel][0] == '-') {
        ui.menu_sel++;
    }
    
    // Create shadow
    if (ui.win_shadow) delwin(ui.win_shadow);
    ui.win_shadow = newwin(height, width, 2, x + 2);
    wbkgd(ui.win_shadow, COLOR_PAIR(COL_SHADOW));
    werase(ui.win_shadow);
    wrefresh(ui.win_shadow);
    
    // Create menu window
    if (ui.win_dialog) delwin(ui.win_dialog);
    ui.win_dialog = newwin(height, width, 1, x);
    
    redraw_menu();
}

static void show_file_menu(void) {
    static const char *items[] = {
        "Quit          Q"
    };
    ui.mode = MODE_MENU_FILE;
    ui.menu_sel = 0;
    show_dropdown_menu(1, "File", items, 1);
}

static void show_run_menu(void) {
    static const char *items[] = {
        "Step          F7",
        "Run           F8",
        "-",
        "Reset         F9"
    };
    ui.mode = MODE_MENU_RUN;
    ui.menu_sel = 0;
    show_dropdown_menu(7, "Run", items, 4);
}

static void show_debug_menu(void) {
    static const char *items[] = {
        "Input X       I",
        "Edit Reg      E",
        "-",
        "Breakpoint    B",
        "Clear BPs     C"
    };
    ui.mode = MODE_MENU_DEBUG;
    ui.menu_sel = 0;
    show_dropdown_menu(13, "Debug", items, 5);
}

static void show_help_menu(void) {
    static const char *items[] = {
        "Help          F1"
    };
    ui.mode = MODE_MENU_HELP;
    ui.menu_sel = 0;
    show_dropdown_menu(21, "Help", items, 1);
}

// ============================================================================
// HELP DIALOG
// ============================================================================

static void show_help_dialog(void) {
    ui.mode = MODE_DIALOG_HELP;
    
    int width = 50;
    int height = 20;
    int y = (ui.term_h - height) / 2;
    int x = (ui.term_w - width) / 2;
    
    // Shadow
    if (ui.win_shadow) delwin(ui.win_shadow);
    ui.win_shadow = newwin(height, width, y + 1, x + 2);
    wbkgd(ui.win_shadow, COLOR_PAIR(COL_SHADOW));
    werase(ui.win_shadow);
    wrefresh(ui.win_shadow);
    
    // Dialog
    if (ui.win_dialog) delwin(ui.win_dialog);
    ui.win_dialog = newwin(height, width, y, x);
    
    wbkgd(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    werase(ui.win_dialog);
    box(ui.win_dialog, 0, 0);
    
    // Title
    wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG_TITLE));
    mvwhline(ui.win_dialog, 0, 1, ' ', width - 2);
    mvwprintw(ui.win_dialog, 0, (width - 6) / 2, " Help ");
    wattroff(ui.win_dialog, COLOR_PAIR(COL_DIALOG_TITLE));
    
    // Content
    wattron(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    mvwprintw(ui.win_dialog, 2,  2, "MK-56 Emulator - Keyboard Reference");
    mvwprintw(ui.win_dialog, 3,  2, "------------------------------------");
    mvwprintw(ui.win_dialog, 5,  2, "F1          Help (this screen)");
    mvwprintw(ui.win_dialog, 6,  2, "F4          Edit (RCL R3 or ИП3)");
    mvwprintw(ui.win_dialog, 7,  2, "F5          Input value to X");
    mvwprintw(ui.win_dialog, 8,  2, "F6          Toggle breakpoint");
    mvwprintw(ui.win_dialog, 9,  2, "F7          Step instruction");
    mvwprintw(ui.win_dialog, 10, 2, "F8          Run until halt/break");
    mvwprintw(ui.win_dialog, 11, 2, "F9          Reset VM");
    mvwprintw(ui.win_dialog, 12, 2, "F10 / G     Menu / angle Р-Г-ГРД");
    mvwprintw(ui.win_dialog, 13, 2, "Up/Down     Scroll program");
    mvwprintw(ui.win_dialog, 14, 2, "PgUp/PgDn   Scroll by page");
    mvwprintw(ui.win_dialog, 15, 2, "Home/End    Go to start/end");
    mvwprintw(ui.win_dialog, 16, 2, "Q           Quit");
    
    // Button
    wattron(ui.win_dialog, COLOR_PAIR(COL_BUTTON) | A_BOLD);
    mvwprintw(ui.win_dialog, height - 2, (width - 8) / 2, "[ OK ]");
    wattroff(ui.win_dialog, COLOR_PAIR(COL_BUTTON) | A_BOLD);
    
    wattroff(ui.win_dialog, COLOR_PAIR(COL_DIALOG));
    wrefresh(ui.win_dialog);
}

static void open_input_reg_dialog(void) {
    ui.mode = MODE_DIALOG_INPUT_REG;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
    
    show_dialog("Edit Register", "Register (0-9, A-D):", 40, 8);
    update_dialog_input();
}

static void open_input_regval_dialog(void) {
    ui.mode = MODE_DIALOG_INPUT_REGVAL;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
    
    char title[32];
    snprintf(title, sizeof(title), "Edit R%s", mk56_reg_name(ui.edit_reg));
    char prompt[48];
    snprintf(prompt, sizeof(prompt), "Enter value for R%s:", mk56_reg_name(ui.edit_reg));
    
    show_dialog(title, prompt, 40, 8);
    update_dialog_input();
}

// ============================================================================
// INPUT HANDLING
// ============================================================================

static int parse_reg_name(const char *s) {
    if (!s || !s[0]) return -1;
    char c = toupper((unsigned char)s[0]);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'D') return 10 + c - 'A';
    return -1;
}

static void handle_dialog_input(int ch) {
    if (ch == 27) {  // ESC - cancel
        close_dialog();
        return;
    }
    
    if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
        if (ui.input_pos > 0) {
            ui.input_buf[--ui.input_pos] = '\0';
            update_dialog_input();
        }
        return;
    }
    
    if (ch == '\n' || ch == KEY_ENTER) {
        // Submit based on mode
        switch (ui.mode) {
            case MODE_DIALOG_INPUT_X:
                if (ui.input_buf[0]) {
                    vm_input(ui.vm, atof(ui.input_buf));
                }
                close_dialog();
                break;
                
            case MODE_DIALOG_INPUT_REG: {
                int reg = parse_reg_name(ui.input_buf);
                if (reg >= 0 && reg < 14) {
                    ui.edit_reg = reg;
                    close_dialog();
                    open_input_regval_dialog();
                } else {
                    close_dialog();
                }
                break;
            }
            
            case MODE_DIALOG_INPUT_REGVAL:
                if (ui.input_buf[0] && vm_value_ok(atof(ui.input_buf))) {
                    ui.vm->regs[ui.edit_reg] = atof(ui.input_buf);
                    ui.vm->reg_code[ui.edit_reg] = false;
                }
                close_dialog();
                break;
                
            default:
                close_dialog();
                break;
        }
        return;
    }
    
    // Accept input characters
    bool accept = false;
    if (ch < 0 || ch > 255) {
        accept = false;
    } else if (ui.mode == MODE_DIALOG_INPUT_REG) {
        accept = isdigit(ch) || (toupper(ch) >= 'A' && toupper(ch) <= 'D');
    } else {
        accept = isdigit(ch) || ch == '.' || ch == '-' || 
                 ch == 'e' || ch == 'E' || ch == '+';
    }
    
    if (accept && ui.input_pos < (int)sizeof(ui.input_buf) - 1) {
        ui.input_buf[ui.input_pos++] = ch;
        ui.input_buf[ui.input_pos] = '\0';
        update_dialog_input();
    }
}

static void execute_menu_item(void) {
    // Save state before closing (close_dialog resets mode)
    UIMode saved_mode = ui.mode;
    int saved_sel = ui.menu_sel;
    
    close_dialog();
    
    switch (saved_mode) {
        case MODE_MENU_FILE:
            if (saved_sel == 0) { endwin(); exit(0); }  // Quit
            break;
            
        case MODE_MENU_RUN:
            if (saved_sel == 0) vm_step(ui.vm);        // Step
            else if (saved_sel == 1) vm_run(ui.vm);   // Run
            else if (saved_sel == 3) vm_reset(ui.vm); // Reset
            break;
            
        case MODE_MENU_DEBUG:
            if (saved_sel == 0) open_input_x_dialog();     // Input X
            else if (saved_sel == 1) open_input_reg_dialog(); // Edit Reg
            else if (saved_sel == 3) vm_set_breakpoint(ui.vm, ui.vm->pc, 
                                        !ui.vm->breakpoints[ui.vm->pc]); // Breakpoint
            else if (saved_sel == 4) memset(ui.vm->breakpoints, 0, 
                                        sizeof(ui.vm->breakpoints)); // Clear BPs
            break;
            
        case MODE_MENU_HELP:
            if (saved_sel == 0) show_help_dialog();  // Help
            break;
            
        default:
            break;
    }
}

static void handle_menu_key(int ch) {
    // ESC closes menu
    if (ch == 27) {
        close_dialog();
        return;
    }
    
    // Enter executes selected item
    if (ch == '\n' || ch == KEY_ENTER) {
        execute_menu_item();
        return;
    }
    
    // Save current mode before any menu switch
    UIMode current_menu = ui.mode;
    
    // Navigate within menu
    switch (ch) {
        case KEY_UP:
            // Move up, skip separators
            do {
                ui.menu_sel--;
                if (ui.menu_sel < 0) ui.menu_sel = ui.menu_count - 1;
            } while (ui.menu_items[ui.menu_sel][0] == '-');
            redraw_menu();
            break;
            
        case KEY_DOWN:
            // Move down, skip separators
            do {
                ui.menu_sel++;
                if (ui.menu_sel >= ui.menu_count) ui.menu_sel = 0;
            } while (ui.menu_items[ui.menu_sel][0] == '-');
            redraw_menu();
            break;
            
        case KEY_LEFT:
            // Switch to previous menu
            if (ui.win_dialog) { delwin(ui.win_dialog); ui.win_dialog = NULL; }
            if (ui.win_shadow) { delwin(ui.win_shadow); ui.win_shadow = NULL; }
            switch (current_menu) {
                case MODE_MENU_RUN: show_file_menu(); break;
                case MODE_MENU_DEBUG: show_run_menu(); break;
                case MODE_MENU_HELP: show_debug_menu(); break;
                default: show_help_menu(); break;
            }
            break;
            
        case KEY_RIGHT:
            // Switch to next menu
            if (ui.win_dialog) { delwin(ui.win_dialog); ui.win_dialog = NULL; }
            if (ui.win_shadow) { delwin(ui.win_shadow); ui.win_shadow = NULL; }
            switch (current_menu) {
                case MODE_MENU_FILE: show_run_menu(); break;
                case MODE_MENU_RUN: show_debug_menu(); break;
                case MODE_MENU_DEBUG: show_help_menu(); break;
                default: show_file_menu(); break;
            }
            break;
            
        // Letter keys to switch menus
        case 'f': case 'F':
            if (ui.win_dialog) { delwin(ui.win_dialog); ui.win_dialog = NULL; }
            if (ui.win_shadow) { delwin(ui.win_shadow); ui.win_shadow = NULL; }
            show_file_menu();
            break;
        case 'r': case 'R':
            if (ui.win_dialog) { delwin(ui.win_dialog); ui.win_dialog = NULL; }
            if (ui.win_shadow) { delwin(ui.win_shadow); ui.win_shadow = NULL; }
            show_run_menu();
            break;
        case 'd': case 'D':
            if (ui.win_dialog) { delwin(ui.win_dialog); ui.win_dialog = NULL; }
            if (ui.win_shadow) { delwin(ui.win_shadow); ui.win_shadow = NULL; }
            show_debug_menu();
            break;
        case 'h': case 'H':
            if (ui.win_dialog) { delwin(ui.win_dialog); ui.win_dialog = NULL; }
            if (ui.win_shadow) { delwin(ui.win_shadow); ui.win_shadow = NULL; }
            show_help_menu();
            break;
            
        // Q quits from menu
        case 'q': case 'Q':
            close_dialog();
            endwin();
            exit(0);
            break;
    }
}

static void handle_key(int ch) {
    // Help dialog - any key closes
    if (ui.mode == MODE_DIALOG_HELP) {
        close_dialog();
        return;
    }
    
    // Program editing mode
    if (ui.mode == MODE_EDIT_PROGRAM) {
        if (ch == 27) {  // ESC - cancel
            ui.mode = MODE_NORMAL;
        } else if (ch == '\n' || ch == '\r' || ch == KEY_ENTER) {
            // Assemble one statement and store it at the edit step
            if (ui.edit_buf[0]) {
                uint8_t steps[MK56_PROGRAM_SIZE];
                char error[sizeof(ui.status_msg)] = {0};
                int len = asm_encode_line(ui.edit_buf, steps, sizeof(steps), error, sizeof(error));
                if (len > 0 && ui.edit_line + len <= MK56_PROGRAM_SIZE) {
                    memcpy(&ui.vm->program[ui.edit_line], steps, (size_t)len);
                    if ((size_t)(ui.edit_line + len) > ui.vm->program_size) {
                        ui.vm->program_size = ui.edit_line + len;
                    }
                    ui.edit_line = (ui.edit_line + len) % MK56_PROGRAM_SIZE;
                    ui.edit_buf[0] = '\0';
                    ui.edit_cursor = 0;
                    ui.status_msg[0] = '\0';
                } else {
                    snprintf(ui.status_msg, sizeof(ui.status_msg), "%s",
                             len > 0 ? "Does not fit before step 98" : error);
                }
            } else {
                ui.mode = MODE_NORMAL;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            // Remove a whole UTF-8 character
            while (ui.edit_cursor > 0 && (ui.edit_buf[ui.edit_cursor - 1] & 0xC0) == 0x80)
                ui.edit_cursor--;
            if (ui.edit_cursor > 0) ui.edit_cursor--;
            ui.edit_buf[ui.edit_cursor] = '\0';
        } else if (ch == KEY_UP) {
            if (ui.edit_line > 0) ui.edit_line--;
            ui.edit_buf[0] = '\0';
            ui.edit_cursor = 0;
        } else if (ch == KEY_DOWN) {
            if (ui.edit_line < MK56_PROGRAM_SIZE - 1) ui.edit_line++;
            ui.edit_buf[0] = '\0';
            ui.edit_cursor = 0;
        } else if ((isprint(ch) || (ch >= 0x80 && ch <= 0xFF)) && ui.edit_cursor < 60) {
            ui.edit_buf[ui.edit_cursor++] = ch;
            ui.edit_buf[ui.edit_cursor] = '\0';
        }
        return;
    }
    
    // Menu mode
    if (ui.mode >= MODE_MENU_FILE && ui.mode <= MODE_MENU_HELP) {
        handle_menu_key(ch);
        return;
    }
    
    // Dialog mode (single field)
    if (ui.mode != MODE_NORMAL) {
        handle_dialog_input(ch);
        return;
    }
    
    switch (ch) {
        // F1 = Help
        case KEY_F(1):
            show_help_dialog();
            break;
            
        // F4 = Edit program
        case KEY_F(4):
            ui.mode = MODE_EDIT_PROGRAM;
            ui.edit_line = ui.vm->pc;
            ui.edit_buf[0] = '\0';
            ui.edit_cursor = 0;
            break;
            
        // F5 = Input X
        case KEY_F(5):
            open_input_x_dialog();
            break;
            
        // F6 = Toggle breakpoint
        case KEY_F(6):
            vm_set_breakpoint(ui.vm, ui.vm->pc, !ui.vm->breakpoints[ui.vm->pc]);
            break;
            
        // F7 = Step
        case KEY_F(7):
            vm_step(ui.vm);
            break;
            
        // F8 = Run
        case KEY_F(8):
            vm_run(ui.vm);
            break;
            
        // F9 = Reset
        case KEY_F(9):
            vm_reset(ui.vm);
            break;
            
        // G = angle switch Р / Г / ГРД
        case 'g':
        case 'G':
            ui.vm->angle = (AngleMode)((ui.vm->angle + 1) % 3);
            break;
            
        // F10 = Menu
        case KEY_F(10):
            show_file_menu();
            break;
            
        // Q = Quit (ESC is handled separately in edit mode)
        case 'q':
        case 'Q':
            endwin();
            exit(0);
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
            
        case KEY_HOME:
            ui.prog_scroll = 0;
            break;
            
        case KEY_END:
            ui.prog_scroll = ui.vm->program_size > 10 ? ui.vm->program_size - 10 : 0;
            break;
    }
}

// ============================================================================
// MAIN DRAW LOOP
// ============================================================================

static void draw_all(void) {
    draw_menu_bar();
    draw_display();
    draw_stack_window();
    draw_registers_window();
    draw_program_window();
    draw_status_bar();
    
    // If a dialog/menu is open, refresh it on top
    if (ui.win_shadow) {
        touchwin(ui.win_shadow);
        wrefresh(ui.win_shadow);
    }
    if (ui.win_dialog) {
        touchwin(ui.win_dialog);
        wrefresh(ui.win_dialog);
    }
}

// ============================================================================
// PUBLIC API
// ============================================================================

void ui_init(MK56VM *vm) {
    ui.vm = vm;
    ui.prog_scroll = 0;
    ui.mode = MODE_NORMAL;
    ui.input_buf[0] = '\0';
    ui.input_pos = 0;
    ui.win_dialog = NULL;
    ui.win_shadow = NULL;
    
    // Initialize ncurses (UTF-8 for the original key notation)
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    init_colors();
    
    getmaxyx(stdscr, ui.term_h, ui.term_w);
    
    // Create windows
    ui.win_desktop = newwin(ui.term_h, ui.term_w, 0, 0);
    ui.win_menu = newwin(1, ui.term_w, 0, 0);
    ui.win_status = newwin(1, ui.term_w, ui.term_h - 1, 0);
    
    // Layout with display at top
    // Row 0: menu bar
    // Row 1-6: display (7-segment digits with padding)
    // Row 7+: stack/regs on left, program on right
    int display_h = 6;
    int left_w = 26;
    int prog_w = ui.term_w - left_w;
    int content_start = 1 + display_h;  // After menu and display
    int content_h = ui.term_h - 2 - display_h;  // minus menu, status, display
    
    ui.win_display = newwin(display_h, ui.term_w, 1, 0);
    ui.win_stack = newwin(10, left_w, content_start, 0);
    ui.win_regs = newwin(content_h - 10, left_w, content_start + 10, 0);
    ui.win_prog = newwin(content_h, prog_w, content_start, left_w);
    
    draw_desktop();
    refresh();  // Ensure stdscr is updated
}

void ui_run(void) {
    // Initial draw and force screen update
    draw_all();
    refresh();
    doupdate();
    
    int ch;
    while (1) {
        ch = getch();
        handle_key(ch);
        
        // Always redraw main windows (menus/dialogs draw on top)
        draw_all();
    }
}

void ui_cleanup(void) {
    if (ui.win_dialog) delwin(ui.win_dialog);
    if (ui.win_shadow) delwin(ui.win_shadow);
    delwin(ui.win_display);
    delwin(ui.win_stack);
    delwin(ui.win_regs);
    delwin(ui.win_prog);
    delwin(ui.win_menu);
    delwin(ui.win_status);
    delwin(ui.win_desktop);
    endwin();
}
