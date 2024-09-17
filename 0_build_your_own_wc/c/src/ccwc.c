/**
 * @file ccwc.c
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @brief 
 * @version 0.1
 * @date 17-09-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <alloca.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// lines, words, bytes characters
typedef enum _allowed_inputs : unsigned char {
    LINES = 'l',
    WORDS = 'w',
    BYTES = 'c',
    CHARS = 'm',
} AllowedInputs;

typedef enum _mode : unsigned char {
    INVALID = 0,
    FIND_DEFAULT,
    FIND_LINES,
    FIND_WORDS,
    FIND_BYTES,
    FIND_CHARS,
} ProgramMode;

typedef struct _settings {
    bool reading_from_file;
    ProgramMode mode;
    const char** file_names;
    int num_files;
} Settings;

int main(int argc, char** argv) {
    Settings settings = {.reading_from_file = true,
                         .mode = FIND_DEFAULT,
                         .file_names = nullptr,
                         .num_files = 0};

    FILE* file;

    // Populate Settings struct
    if (argc > 1) {
        // check if the first argument is supposed to be a flag
        if (argv[1][0] == '-') {
            switch (argv[1][1]) {
                case LINES:
                    settings.mode = FIND_LINES;
                    break;
                case WORDS:
                    settings.mode = FIND_WORDS;
                    break;
                case BYTES:
                    settings.mode = FIND_BYTES;
                    break;
                case CHARS:
                    settings.mode = FIND_CHARS;
                    break;
                default:
                    settings.mode = INVALID;
                    break;
            }

            // we are reading from stdin with the earlier options
            if (argc == 2) {
                settings.reading_from_file = false;
            } else {
                // assume that the remaining args are files
                // and add them to the list of files
                settings.num_files = argc - 2;
                settings.file_names = (const char**)(argv + 2);
            }
        }
        // no arguments entered, all are assumed files
        else {
            settings.mode = FIND_DEFAULT;
            // assume that the remaining args are files
            // and add them to the list of files
            settings.num_files = argc - 1;
            settings.file_names = (const char**)(argv + 1);
        }
    }
    // we are reading from stdin,
    // with default options
    else {
        settings.reading_from_file = false;
        settings.mode = FIND_DEFAULT;
    };

    // Check for invalid options and do something about it
    if (settings.mode == INVALID) {
        printf("Invalid options\n");
        return EXIT_FAILURE;
    };

    if (!settings.reading_from_file) {
    } else {
        for (int i = 0; i < settings.num_files; i++) {
            // todo: check for fopen error code
            file = fopen(settings.file_names[i], "r");
            char buffer[256];

            fgets(buffer, 256, file);
        }
    }

    // Now we need to get the counts

    for (int i = 0; i < settings.num_files; i++) {
        if (settings.file_names[i] != nullptr) {
            printf("file %d : %s\n", i, settings.file_names[i]);
        }
    }
}