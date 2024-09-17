#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/print_lines.h"

#define BUF_SIZE 256

int main(int argc, char** argv) {
    char** file_names = nullptr;
    FILE* file = nullptr;
    char buff[BUF_SIZE] = {0};
    size_t num_files = 0;

    printMe();

    // if we have any arguments, we need to parse them for options and files
    if (argc > 1) {
        assert(argv[1] != nullptr);  // this is only needed
        if (argv[1][0] == '-') {
            // we are reading from stdin
            if (strncmp(argv[1], "-", 2) == 0) {
                file_names = nullptr;
                num_files = 0;
            } else if (strncmp(argv[1], "-n", 3) == 0) {
            } else if (strncmp(argv[1], "-b", 3) == 0) {
            } else {
                printf("Invalid arguments!\n");
                return EXIT_FAILURE;
            }

            // naïvely assume that the remaining args are files
            if (argc > 2) {
                file_names = argv + 2;
                num_files = argc - 2;
            }
        } else {
            file_names = argv + 1;
            num_files = argc - 1;
        }

    } else {
        file_names = nullptr;
        num_files = 0;
    }

    //
    if (num_files == 0 && file_names == nullptr) {
        file = stdin;
        while (!feof(file)) {
            if (fgets(buff, BUF_SIZE, file) != nullptr) {
                printf("%s", buff);
            }
        }
    } else {
        for (size_t i = 0; i < num_files; i++) {
            file = fopen(file_names[i], "r");

            // implement a function that takes in
            if (file == nullptr) {
                return EXIT_FAILURE;
            }

            while (!feof(file)) {
                if (fgets(buff, BUF_SIZE, file) != nullptr) {
                    printf("%s", buff);
                }
            }

            fclose(file);
        }
    }
}
