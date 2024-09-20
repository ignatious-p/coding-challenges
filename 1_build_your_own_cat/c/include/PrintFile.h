#include <bits/types/FILE.h>  // FILE

typedef struct __state State;

void* InitialiseState(int arg_count, char** arg_values);
void CleanupState(State* state);
bool GetReadingFromFile(State* state);
int GetNumberOfFiles(State* state);
char* GetFileName(State* state, int index);

void PrintFile(State* state, FILE* file);