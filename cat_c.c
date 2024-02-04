#include <stdio.h>
#include <stdlib.h>

void printFileContent(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(1);
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}

void writeFileContent(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(1);
    }

    int c;
    while ((c = getchar()) != EOF) {
        fputc(c, file);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (argv[1][0] == '>') {
        writeFileContent(argv[1] + 1);
    } else {
        printFileContent(argv[1]);
    }

    return 0;
}

