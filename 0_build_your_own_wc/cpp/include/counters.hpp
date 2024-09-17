/**
 * @file counters.hpp
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @version 0.1
 * @date 04-09-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <algorithm>
#include <cctype>
#include <span>
#include <string_view>

namespace counters {
// Given a string counts the number of bytes in it
inline size_t CountBytes(std::u8string_view& input_string) {
    if (input_string.empty()) {
        return 0;
    }

    return input_string.length();
};

// Given a string counts the number of lines in it
inline size_t CountLines(std::u8string_view& input_string) {
    if (input_string.empty()) {
        return 0;
    }

    return std::count(input_string.begin(), input_string.end(), u8'\n');
};

// Given a string counts the number of words in it
inline size_t CountWords(std::u8string_view& input_string) {
    if (input_string.empty()) {
        return 0;
    }

    size_t word_count = 0;

    // Idea 1: Using "rising edge" transition from a whitespace character to a
    // non-whitespace character.
    bool curr = false, prev = false;
    for (const char8_t& character : input_string) {
        curr = std::isspace(character);

        // Was the previous character a whitespace AND is the current
        // character NOT a whitespace?
        if ((prev == true && curr == false) ||
            (word_count == 0 && curr == false)) {
            word_count++;
        };

        // Update prev with curr after or we will never transition!
        prev = curr;
    }

    // Idea 2: Using a regex pattern to split the string into character
    // sequences separated by any whitespace character. This is gonna be a
    // bit slower but by replacing the regex you can search for anything.
    // But then again it is a regex. :(
    // FIXME: bad_cast is thrown during runtime
    // // Define a regex pattern that matches all non-whitespace characters
    // static const std::basic_regex word_regex(u8"\\S+",
    // std::regex::ECMAScript);

    // // Use a regex iterator to count matches
    // auto words_begin = std::regex_iterator(input_string.begin(),
    //                                        input_string.end(), word_regex);
    // // An iterator with nothing
    // auto words_end = std::regex_iterator<const char8_t*>();

    // word_count = std::distance(words_begin, words_end);

    return word_count;
};

// Given a string counts the number of characters in it because simply counting
// the bytes (using string::length() or strlen()) will not give you the correct
// character count for strings containing multi-byte characters.
inline size_t CountCharacters(std::u8string_view& input_string) {
    if (input_string.empty()) {
        return 0;
    }

    size_t char_count = 0;

    // Iterate through the string, examining each byte:
    // If the byte starts with a 0, it's a single-byte character.
    // If it starts with 110, it's the start of a 2-byte character.
    // If it starts with 1110, it's the start of a 3-byte character.
    // If it starts with 11110, it's the start of a 4-byte character.

    // Therefore:
    // single byte range = 0b00000000 -> 0b01111111 (0 ->127)
    // double byte range = 0b11000000 -> 0b11011111 (192 -> 223)
    // triple byte range = 0b11100000 -> 0b11101111 (224 -> 239)
    // quadle byte range = 0b11110000 -> 0b11110111 (240 -> 247)

    constexpr std::byte sbc{0b00000000};
    constexpr std::byte dbc{0b11000000};
    constexpr std::byte tbc{0b11100000};
    constexpr std::byte qbc{0b11110000};

    constexpr std::byte esbc{0b01111111};
    constexpr std::byte edbc{0b11011111};
    constexpr std::byte etbc{0b11101111};
    constexpr std::byte eqbc{0b11110111};

    // "view" the input as bytes
    auto input_bytes = std::as_bytes(std::span(input_string));

    for (const std::byte& input_byte : input_bytes) {
        if (qbc <= input_byte && input_byte <= eqbc) {
            char_count++;
        } else if (tbc <= input_byte && input_byte <= etbc) {
            char_count++;
        } else if (dbc <= input_byte && input_byte <= edbc) {
            char_count++;
        } else if (sbc <= input_byte && input_byte <= esbc) {
            char_count++;
        } else {
            continue;
        }
    }

    return char_count;
};

}  // namespace counters
