#include <stdio.h>

#include "../include/PrintFile.h"

int main(int argc, char** argv) {
    FILE* file = nullptr;
    State* state = InitialiseState(argc, argv);
    if (state == nullptr) {
        return 1;
    }

    if (!GetReadingFromFile(state)) {
        file = stdin;
        PrintFile(state, file);
    } else {
        for (int i = 0; i < GetNumberOfFiles(state); i++) {
            file = fopen(GetFileName(state, i), "r");
            if (file == nullptr) {
                continue;
            }

            PrintFile(state, file);

            fclose(file);
        }
    }

    CleanupState(state);
}
