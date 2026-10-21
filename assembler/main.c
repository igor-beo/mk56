/**
 * MK56-ASM Assembler - Command Line Interface
 * Build: make (gcc -O2 -std=c11 -I../common -o mk56asm mk56asm.c main.c ../common/mk56_isa.c -lm)
 */

#include "mk56asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

static void print_usage(const char *prog) {
    printf("MK56-ASM Assembler v1.0\n\n");
    printf("Usage: %s input.asm|input.mk56 [-o output.bin] [-l listing.lst] [-s source.asm] [-v]\n\n", prog);
    printf("*.mk56 files are original listings (\"ИП0 Fx² 2 × С/П\"); others are MK56-ASM.\n\n");
    printf("Options:\n");
    printf("  -o FILE   Output binary file (default: input.bin)\n");
    printf("  -l FILE   Generate listing file\n");
    printf("  -s FILE   Write the program as MK56-ASM source (\"-\" for stdout)\n");
    printf("  -v        Verbose output\n");
    printf("  -h        Show this help\n");
}

static char* read_file(const char *path, size_t *size) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    
    long len = -1;
    if (fseek(f, 0, SEEK_END) == 0) len = ftell(f);
    if (len < 0 || fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    
    char *buf = malloc((size_t)len + 1);
    if (!buf || fread(buf, 1, (size_t)len, f) != (size_t)len) { free(buf); fclose(f); return NULL; }
    buf[len] = '\0';
    fclose(f);
    if (strlen(buf) != (size_t)len) { free(buf); return NULL; }    /* NUL byte: not a text file */
    
    if (size) *size = (size_t)len;
    return buf;
}

static bool write_file(const char *path, const void *data, size_t size) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    fwrite(data, 1, size, f);
    fclose(f);
    return true;
}

/* -s output, bounded */
static char out[65536];
static size_t out_len;
static bool out_full;

static void put(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = out_full ? -1 : vsnprintf(out + out_len, sizeof out - out_len, fmt, ap);
    va_end(ap);
    if (n < 0 || (size_t)n >= sizeof out - out_len) out_full = true;
    else out_len += (size_t)n;
}

static const char LEGEND[] = "; Each line: instruction ; address, keys, codes";

/* -s: the input's leading comment block (description and test
 * directives), then the program as MK56-ASM, checked by reassembling. */
static int write_source(const Assembler *as, const char *source, const char *path) {
    const char *p = source;
    while (*p) {
        const char *s = p;
        while (*s == ' ' || *s == '\t') s++;
        if (*s != ';' && *s != '\n' && *s != '\r') break;
        const char *eol = strchr(p, '\n');
        int len = (int)(eol ? (size_t)(eol - p) + 1 : strlen(p));
        if (strncmp(s, LEGEND, sizeof LEGEND - 1) != 0) put("%.*s", len, p);
        p += len;
    }
    while (out_len > 1 && out[out_len - 1] == '\n' && out[out_len - 2] == '\n') out[--out_len] = '\0';
    if (as->listing_syntax) {
        /* Keep the listing as printed, which mk56test checks against the code */
        put("; As printed:\n");
        for (const char *q = p; *q; ) {
            const char *eol = strchr(q, '\n');
            size_t len = eol ? (size_t)(eol - q) : strlen(q);
            while (len && (q[len - 1] == '\r' || q[len - 1] == ' ')) len--;
            const char *t = q;
            while (len && (*t == ' ' || *t == '\t')) { t++; len--; }
            if (len && *t != ';') put(";   %.*s\n", (int)len, t);
            q = eol ? eol + 1 : q + strlen(q);
        }
        put(";\n");
    }
    put("%s\n\n", LEGEND);

    size_t n;
    const uint8_t *bin = asm_get_binary(as, &n);
    char code[16384];
    asm_to_source(bin, n, code, sizeof code);
    put("%s", code);
    if (out_full) {
        fprintf(stderr, "Error: source longer than %zu bytes\n", sizeof out);
        return 1;
    }

    static Assembler check;
    if (!asm_assemble(&check, out) || check.binary_size != n ||
        memcmp(check.binary, bin, n) != 0) {
        fprintf(stderr, "Error: generated source does not reassemble to the same program%s%s\n",
                asm_get_error(&check) ? ": " : "", asm_get_error(&check) ? asm_get_error(&check) : "");
        return 1;
    }
    if (strcmp(path, "-") == 0) { fputs(out, stdout); return 0; }
    if (!write_file(path, out, out_len)) {
        fprintf(stderr, "Error: Cannot write file: %s\n", path);
        return 1;
    }
    printf("Source: %s (%zu steps)\n", path, n);
    return 0;
}

int main(int argc, char **argv) {
    const char *input_path = NULL;
    const char *output_path = NULL;
    const char *listing_path = NULL;
    const char *source_path = NULL;
    bool verbose = false;
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_path = argv[++i];
        } else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
            listing_path = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            source_path = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = true;
        } else if (argv[i][0] != '-') {
            input_path = argv[i];
        }
    }
    
    if (!input_path) {
        print_usage(argv[0]);
        return 1;
    }
    
    // Generate default output path
    char default_output[1024];
    if (!output_path) {
        const char *slash = strrchr(input_path, '/');
        const char *dot = strrchr(input_path, '.');
        size_t stem = dot && (!slash || dot > slash) ? (size_t)(dot - input_path) : strlen(input_path);
        if (stem + 5 > sizeof default_output) {
            fprintf(stderr, "Error: input path too long; use -o\n");
            return 1;
        }
        snprintf(default_output, sizeof default_output, "%.*s.bin", (int)stem, input_path);
        output_path = default_output;
    }
    
    // Read source file
    if (verbose) printf("Assembling: %s\n", input_path);
    
    size_t src_size;
    char *source = read_file(input_path, &src_size);
    if (!source) {
        fprintf(stderr, "Error: Cannot read file: %s\n", input_path);
        return 1;
    }
    
    // Assemble
    Assembler as;
    const char *ext = strrchr(input_path, '.');
    bool listing = ext && strcmp(ext, ".mk56") == 0;
    if (!asm_assemble_ex(&as, source, listing)) {
        fprintf(stderr, "Assembly error: %s\n", asm_get_error(&as));
        free(source);
        return 1;
    }
    
    if (verbose) {
        printf("  Found %zu labels\n", as.label_count);
    }

    if (source_path) {
        int rc = write_source(&as, source, source_path);
        free(source);
        return rc;
    }
    free(source);
    
    // Write binary
    size_t bin_size;
    const uint8_t *binary = asm_get_binary(&as, &bin_size);
    
    if (!write_file(output_path, binary, bin_size)) {
        fprintf(stderr, "Error: Cannot write file: %s\n", output_path);
        return 1;
    }
    printf("Output: %s (%zu steps)\n", output_path, bin_size);
    
    // Write listing
    if (listing_path) {
        static char text[65536];
        asm_get_listing(&as, text, sizeof text);
        if (!write_file(listing_path, text, strlen(text))) {
            fprintf(stderr, "Error: Cannot write listing: %s\n", listing_path);
            return 1;
        }
        printf("Listing: %s\n", listing_path);
    }
    
    if (verbose) {
        printf("\nAssembly Listing:\n");
        static char text[65536];
        asm_get_listing(&as, text, sizeof text);
        printf("%s", text);
    }
    
    return 0;
}
