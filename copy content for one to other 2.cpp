#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <sourcefile> <destinationfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest_file = fopen(argv[2], "w");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, dest_file);
    }

    fclose(source_file);
    fclose(dest_file);

    printf("File copied successfully.\n");
    return 0;
}

