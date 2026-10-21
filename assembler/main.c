/**
 * MK56-ASM Assembler - Command Line Interface
 * Build: gcc -O2 -Wall -std=c11 -o mk56asm mk56asm.c main.c -lm
 */

#include "mk56asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *buf = malloc(len + 1);
    if (!buf) { fclose(f); return NULL; }
    
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    
    if (size) *size = len;
    return buf;
}

static bool write_file(const char *path, const void *data, size_t size) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    fwrite(data, 1, size, f);
    fclose(f);
    return true;
}

/* -s: the input's leading comment block (description and test
 * directives), then the program as MK56-ASM, checked by reassembling. */
static int write_source(const Assembler *as, const char *source, const char *path) {
    static char out[65536];
    size_t off = 0;
    const char *p = source;
    while (*p) {
        const char *s = p;
        while (*s == ' ' || *s == '\t') s++;
        if (*s != ';' && *s != '\n' && *s != '\r') break;
        const char *eol = strchr(p, '\n');
        size_t len = eol ? (size_t)(eol - p) + 1 : strlen(p);
        if (off + len < sizeof out) { memcpy(out + off, p, len); off += len; }
        p += len;
    }
    if (as->listing_syntax) {
        /* Keep the listing as printed, which mk56test checks against the code */
        off += (size_t)snprintf(out + off, sizeof out - off, "; As printed:\n");
        for (const char *q = p; *q; ) {
            const char *eol = strchr(q, '\n');
            size_t len = eol ? (size_t)(eol - q) : strlen(q);
            while (len && (q[len - 1] == '\r' || q[len - 1] == ' ')) len--;
            const char *t = q;
            while (len && (*t == ' ' || *t == '\t')) { t++; len--; }
            if (len && *t != ';' && off + len + 8 < sizeof out)
                off += (size_t)snprintf(out + off, sizeof out - off, ";   %.*s\n", (int)len, t);
            q = eol ? eol + 1 : q + strlen(q);
        }
        off += (size_t)snprintf(out + off, sizeof out - off, ";\n");
    }
    off += (size_t)snprintf(out + off, sizeof out - off,
        "; Each line: instruction ; address, keys, codes\n\n");

    size_t n;
    const uint8_t *bin = asm_get_binary(as, &n);
    off += asm_to_source(bin, n, out + off, sizeof out - off);

    static Assembler check;
    if (!asm_assemble(&check, out) || check.binary_size != n ||
        memcmp(check.binary, bin, n) != 0) {
        fprintf(stderr, "Error: generated source does not reassemble to the same program%s%s\n",
                asm_get_error(&check) ? ": " : "", asm_get_error(&check) ? asm_get_error(&check) : "");
        return 1;
    }
    if (strcmp(path, "-") == 0) { fputs(out, stdout); return 0; }
    if (!write_file(path, out, off)) {
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
    char default_output[256];
    if (!output_path) {
        strncpy(default_output, input_path, sizeof(default_output) - 5);
        char *dot = strrchr(default_output, '.');
        if (dot) *dot = '\0';
        strcat(default_output, ".bin");
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
        char listing[8192];
        asm_get_listing(&as, listing, sizeof(listing));
        if (!write_file(listing_path, listing, strlen(listing))) {
            fprintf(stderr, "Error: Cannot write listing: %s\n", listing_path);
            return 1;
        }
        printf("Listing: %s\n", listing_path);
    }
    
    if (verbose) {
        printf("\nAssembly Listing:\n");
        char listing[8192];
        asm_get_listing(&as, listing, sizeof(listing));
        printf("%s", listing);
    }
    
    return 0;
}
