#include "PrintFile.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define _X_OPEN_SOURCE 700
#include <stdio.h>  //getline

#define BUF_SIZE (size_t)10

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
    size_t __line_count;
} State;

[[nodiscard]] void* InitialiseState(int arg_count, char** arg_values) {
    if (arg_count < 1 || arg_values == nullptr) {
        fprintf(stderr, "expected\t\t|\treceived\n");
        fprintf(stderr, "----------\t\t|\t----------\n");
        fprintf(stderr, "arg_count >= 1\t\t|\t arg_count == %d\n", arg_count);
        fprintf(stderr, "arg_values != nullptr\t|\t arg_values == %p\n",
                arg_values);
        return nullptr;
    }

    // Create and initialise a State struct
    State* state = malloc(sizeof(*state));
    if (state == nullptr) return nullptr;

    State temp = {.__reading_from_file = false,
                  .__variant = DEFAULT,
                  .__num_files = 0,
                  .__file_names = nullptr};
    *state = temp;

    // if we have any arguments, we need to parse them for options and files
    if (arg_count > 1) {
        if (arg_values[1] == nullptr) return nullptr;
        if (arg_values[1][0] == '-') {
            // we are reading from stdin
            if (strncmp(arg_values[1], "-", 2) == 0) {
                state->__variant = DEFAULT;
            } else if (strncmp(arg_values[1], "-n", 3) == 0) {
                state->__variant = INCLUDING_BLANKS;
            } else if (strncmp(arg_values[1], "-b", 3) == 0) {
                state->__variant = EXCLUDING_BLANKS;
            } else {
                fprintf(stderr, "Invalid arguments!\n");
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
            state->__reading_from_file = true;
            state->__num_files = arg_count - 1;
            state->__file_names = arg_values + 1;
        }
    }

    return state;
}

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
    assert(index <= options->__num_files);
    return options->__file_names[index];
}

int GetNumberOfFiles(State* options) { return options->__num_files; }

void PrintFile(State* options, FILE* file) {
    if (options == nullptr || file == nullptr) {
        fprintf(stderr, "expected\t\t|\treceived\n");
        fprintf(stderr, "----------\t\t|\t----------\n");
        fprintf(stderr, "options != nullptr\t\t|\t options == %p\n", options);
        fprintf(stderr, "file != nullptr\t\t|\t file == %p\n", file);
        return;
    }

    char* buff = malloc(BUF_SIZE * sizeof(*buff));
    if (buff == nullptr) return;

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

// Prints
void PrintLine(State* options, char* buff) {
    if (options == nullptr || buff == nullptr) {
        fprintf(stderr, "expected\t\t|\treceived\n");
        fprintf(stderr, "----------\t\t|\t----------\n");
        fprintf(stderr, "options != nullptr\t\t|\t options == %p\n", options);
        fprintf(stderr, "buff != nullptr\t\t|\t buff == %p\n", buff);
        return;
    }

    switch (options->__variant) {
        case DEFAULT:
            printf("%s", buff);
            break;
        case INCLUDING_BLANKS:
            printf("%lu  %s", ++(options->__line_count), buff);
            break;
        case EXCLUDING_BLANKS:
            if (strncmp(buff, "\n", 2) != 0) {
                printf("%lu  %s", ++(options->__line_count), buff);
            } else {
                printf("%s", buff);
            }
            break;
        default:
            break;
    }
};
