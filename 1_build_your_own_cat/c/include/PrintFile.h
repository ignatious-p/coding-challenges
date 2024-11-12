#include <bits/types/FILE.h>  // FILE

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __state State;

// Initialise State data
void* InitialiseState(int arg_count, char** arg_values);
// Cleanup State data
void CleanupState(State* state);

bool GetReadingFromFile(State* state);
int GetNumberOfFiles(State* state);
// Gets the file name at a given index
char* GetFileName(State* state, int index);

// Prints file contents to stdout
void PrintFile(State* state, FILE* file);

#ifdef __cplusplus
}
#endif