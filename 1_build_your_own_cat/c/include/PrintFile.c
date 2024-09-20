#include "PrintFile.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define _X_OPEN_SOURCE 700
#include <stdio.h>  //getline

#define BUF_SIZE (size_t)1024

typedef enum __variant : char {
    DEFAULT = 0,
    INCLUDING_BLANKS,
    EXCLUDING_BLANKS
} Variant;

typedef struct __state {
    bool __reading_from_file;
    Variant __variant;
    int __num_files;
    char** __file_names;
} State;

void CleanupState(State* options) {
    if (options != nullptr) {
        free(options);
    }
}

bool GetReadingFromFile(State* options) {
    assert(options != nullptr);
    return options->__reading_from_file;
}

char* GetFileName(State* options, int index) {
    assert(options != nullptr);
    return options->__file_names[index];
}

int GetNumberOfFiles(State* options) { return options->__num_files; }

[[nodiscard]] void* InitialiseState(int arg_count, char** arg_values) {
    if (arg_count < 1 || arg_values == nullptr) {
        printf("expected\t\t|\treceived\n");
        printf("----------\t\t|\t----------\n");
        printf("arg_count >= 1\t\t|\t arg_count == %d\n", arg_count);
        printf("arg_values != nullptr\t|\t arg_values == %p\n", arg_values);
        return nullptr;
    }

    // Create and initialise a State struct
    State* state = malloc(sizeof(*state));
    State temp = {.__reading_from_file = false,
                  .__variant = DEFAULT,
                  .__num_files = 0,
                  .__file_names = nullptr};
    *state = temp;

    // if we have any arguments, we need to parse them for options and files
    if (arg_count > 1) {
        assert(arg_values[1] != nullptr);
        if (arg_values[1][0] == '-') {
            // we are reading from stdin
            if (strncmp(arg_values[1], "-", 2) == 0) {
                state->__variant = DEFAULT;
            } else if (strncmp(arg_values[1], "-n", 3) == 0) {
                state->__variant = INCLUDING_BLANKS;
            } else if (strncmp(arg_values[1], "-b", 3) == 0) {
                state->__variant = EXCLUDING_BLANKS;
            } else {
                printf("Invalid arguments!\n");
                return nullptr;
            }
            // naïvely assume that the remaining args are files
            // and override the initialised defaults
            if (arg_count > 2) {
                state->__reading_from_file = true;
                state->__num_files = arg_count - 2;
                state->__file_names = arg_values + 2;
            }
        } else {
            State temp = {.__reading_from_file = true,
                          .__variant = DEFAULT,
                          .__num_files = arg_count - 1,
                          .__file_names = arg_values + 1};
            *state = temp;
        }
    }

    return state;
}

void PrintFile(State* options, FILE* file) {
    if (options == nullptr || file == nullptr) {
        printf("expected\t\t|\treceived\n");
        printf("----------\t\t|\t----------\n");
        printf("options != nullptr\t\t|\t options == %p\n", options);
        printf("file != nullptr\t\t|\t file == %p\n", file);
        return;
    }

    char* buff = malloc(BUF_SIZE * sizeof(*buff));
    size_t initial_buff_size = BUF_SIZE;
    static int line_count = 0;

    while (!feof(file)) {
        // getline can increase the size of the buffer
        if (getline(&buff, &initial_buff_size, file) != -1) {
            switch (options->__variant) {
                case DEFAULT:
                    printf("%s", buff);
                    break;
                case INCLUDING_BLANKS:
                    printf("%d  %s", ++line_count, buff);
                    break;
                case EXCLUDING_BLANKS:
                    if (strncmp(buff, "\n", 2) != 0) {
                        printf("%d  %s", ++line_count, buff);
                    } else {
                        printf("%s", buff);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    free(buff);
};