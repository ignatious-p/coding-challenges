/**
 * @file test_counters.cpp
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @version 0.1
 * @date 09-09-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include "counters.hpp"

SCENARIO("TESTING COUNTERS", "[counters]") {
    size_t byte_count = 0, line_count = 0, word_count = 0, char_count = 0;

    GIVEN("An empty string") {
        std::u8string input;
        input.append(u8"");

        std::u8string_view input_v(input);

        byte_count = counters::CountBytes(input_v);
        line_count = counters::CountLines(input_v);
        word_count = counters::CountWords(input_v);
        char_count = counters::CountCharacters(input_v);

        THEN("Byte count") { REQUIRE(byte_count == 0); }
        THEN("Line count") { REQUIRE(line_count == 0); }
        THEN("Word count") { REQUIRE(word_count == 0); }
        THEN("Char count") { REQUIRE(char_count == 0); }
    }

    GIVEN("Whitespace string") {
        std::u8string input;
        input.append(u8" ");

        std::u8string_view input_v(input);

        byte_count = counters::CountBytes(input_v);
        line_count = counters::CountLines(input_v);
        word_count = counters::CountWords(input_v);
        char_count = counters::CountCharacters(input_v);

        THEN("Byte count") { REQUIRE(byte_count == 1); }
        THEN("Line count") { REQUIRE(line_count == 0); }
        THEN("Word count") { REQUIRE(word_count == 0); }
        THEN("Char count") { REQUIRE(char_count == 1); }
    }

    GIVEN("A single word (ascii)") {
        std::u8string input;
        input.append(u8"beans");
        std::u8string_view input_v(input);

        byte_count = counters::CountBytes(input_v);
        line_count = counters::CountLines(input_v);
        word_count = counters::CountWords(input_v);
        char_count = counters::CountCharacters(input_v);

        THEN("Byte count") { REQUIRE(byte_count == 5); }
        THEN("Line count") { REQUIRE(line_count == 0); }
        THEN("Word count") { REQUIRE(word_count == 1); }
        THEN("Char count") { REQUIRE(char_count == 5); }
    }

    GIVEN("A single word (utf-8)") {
        std::u8string input;
        input.append(u8"heiße");
        std::u8string_view input_v(input);

        byte_count = counters::CountBytes(input_v);
        line_count = counters::CountLines(input_v);
        word_count = counters::CountWords(input_v);
        char_count = counters::CountCharacters(input_v);

        THEN("Byte count") { REQUIRE(byte_count == 6); }
        THEN("Line count") { REQUIRE(line_count == 0); }
        THEN("Word count") { REQUIRE(word_count == 1); }
        THEN("Char count") { REQUIRE(char_count == 5); }
    }

    GIVEN("5 lines of text (ascii)") {
        // I need absolute paths here for some reason...
        // idgi...
        auto file_path = std::filesystem::path(
            "/home/ignatious/devel/coding-challenges/0_build_your_own_wc/cpp/"
            "tests/5_lines_ascii.txt");

        auto file = std::ifstream(file_path, std::ios::binary);

        std::u8string input;
        input.assign((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
        std::u8string_view input_v(input);

        byte_count = counters::CountBytes(input_v);
        line_count = counters::CountLines(input_v);
        word_count = counters::CountWords(input_v);
        char_count = counters::CountCharacters(input_v);

        file.close();
        THEN("Byte count") { REQUIRE(byte_count == (size_t)213); }
        THEN("Line count") { REQUIRE(line_count == (size_t)5); }
        THEN("Word count") { REQUIRE(word_count == (size_t)40); }
        THEN("Char count") { REQUIRE(char_count == (size_t)213); }
    }

    GIVEN("5 lines of text (utf-8)") {
        // I need absolute paths here for some reason...
        // idgi...
        auto file_path = std::filesystem::path(
            "/home/ignatious/devel/coding-challenges/0_build_your_own_wc/cpp/"
            "tests/5_lines_utf8.txt");

        auto file = std::ifstream(file_path, std::ios::binary);

        std::u8string input;
        input.assign((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
        std::u8string_view input_v(input);

        byte_count = counters::CountBytes(input_v);
        line_count = counters::CountLines(input_v);
        word_count = counters::CountWords(input_v);
        char_count = counters::CountCharacters(input_v);

        file.close();
        THEN("Byte count") { REQUIRE(byte_count == (size_t)258); }
        THEN("Line count") { REQUIRE(line_count == (size_t)5); }
        THEN("Word count") { REQUIRE(word_count == (size_t)41); }
        THEN("Char count") { REQUIRE(char_count == (size_t)255); }
    }
}
