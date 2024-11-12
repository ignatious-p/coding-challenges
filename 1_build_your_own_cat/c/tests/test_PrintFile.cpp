#include <catch2/catch_test_macros.hpp>
#include <cstddef>

#include "../include/PrintFile.h"

SCENARIO("TESTING PrintFiles", "[PrintFile]") {
    GIVEN("Invalid environment variables") {
        int argc = 0;
        char** argv = nullptr;
        State* state = (State*)InitialiseState(argc, argv);
        REQUIRE(state == nullptr);
    };

    GIVEN(" variables") {
        int argc = 1;
        char* argv[] = {"programname", ""};
        State* state = (State*)InitialiseState(argc, argv);
        REQUIRE(state == nullptr);
    };

    // GIVEN("Whitespace string") {
    //     std::u8string input;
    //     input.append(u8" ");

    //     std::u8string_view input_v(input);

    //     byte_count = counters::CountBytes(input_v);
    //     line_count = counters::CountLines(input_v);
    //     word_count = counters::CountWords(input_v);
    //     char_count = counters::CountCharacters(input_v);

    //     THEN("Byte count") { REQUIRE(byte_count == 1); }
    //     THEN("Line count") { REQUIRE(line_count == 0); }
    //     THEN("Word count") { REQUIRE(word_count == 0); }
    //     THEN("Char count") { REQUIRE(char_count == 1); }
    // }

    // void* InitialiseState(int arg_count, char** arg_values);
    // // Cleanup State data
    // void CleanupState(State * state);

    // bool GetReadingFromFile(State * state);
    // int GetNumberOfFiles(State * state);
    // // Gets the file name at a given index
    // char* GetFileName(State * state, int index);

    // // Prints file contents to stdout
    // void PrintFile(State * state, FILE * file);
}
