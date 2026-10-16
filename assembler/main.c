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
    printf("Usage: %s input.asm|input.mk56 [-o output.bin] [-l listing.lst] [-v]\n\n", prog);
    printf("*.mk56 files are original listings (\"ИП0 Fx² 2 × С/П\"); others are MK56-ASM.\n\n");
    printf("Options:\n");
    printf("  -o FILE   Output binary file (default: input.bin)\n");
    printf("  -l FILE   Generate listing file\n");
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

int main(int argc, char **argv) {
    const char *input_path = NULL;
    const char *output_path = NULL;
    const char *listing_path = NULL;
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
    free(source);
    
    if (verbose) {
        printf("  Found %zu labels\n", as.label_count);
    }
    
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
