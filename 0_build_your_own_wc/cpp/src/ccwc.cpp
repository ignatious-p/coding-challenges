/**
 * @file ccwc.cpp
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @version 0.1
 * @date 09-09-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ccwc.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <print>
#include <string>
#include <string_view>

#include "argument_parser.hpp"
#include "counters.hpp"

struct Counts {
   public:
    size_t line_count = 0;
    size_t word_count = 0;
    size_t byte_count = 0;
    size_t char_count = 0;

    void operator+=(Counts& c) {
        line_count += c.line_count;
        word_count += c.word_count;
        byte_count += c.byte_count;
        char_count += c.char_count;
    }
};

inline void PrintOutput(std::string& option, Counts& counts,
                        const std::string& file_path_string) {
    // Number of lines, words and bytes in the stream
    if (option == "default") {
        std::cout << counts.line_count << " " << counts.word_count << " "
                  << counts.byte_count << " ";
    }
    // Number of lines in stream
    else if (option == "-l") {
        std::cout << counts.line_count << " ";
    }
    // Number of words in the file
    else if (option == "-w") {
        std::cout << counts.word_count << " ";
    }
    // Number of bytes in the stream
    else if (option == "-c") {
        // Could also use the size of the file on disk
        // byte_count = fs::file_size(file_path);

        std::cout << counts.byte_count << " ";
    }
    // Number of characters in the file
    else if (option == "-m") {
        std::cout << counts.char_count << " ";
    }

    std::cout << (file_path_string.length() == 0 ? "" : file_path_string)
              << '\n';
};

inline void GetCounts(std::string& option, Counts& counts,
                      std::u8string_view& content_v) {
    if (option == "default") {
        counts.line_count = counters::CountLines(content_v);
        counts.word_count = counters::CountWords(content_v);
        counts.byte_count = counters::CountBytes(content_v);
    } else if (option == "-l") {
        counts.line_count = counters::CountLines(content_v);
    } else if (option == "-w") {
        counts.word_count = counters::CountWords(content_v);
    } else if (option == "-c") {
        counts.byte_count = counters::CountBytes(content_v);
    } else if (option == "-m") {
        counts.char_count = counters::CountCharacters(content_v);
    }
};

int main(int argc, char** argv) {
    namespace fs = std::filesystem;

    // For the parser
    std::vector<std::string> argv_vector;
    bool reading_from_file = true;
    std::string option;
    std::vector<std::string> file_names;

    // For counters
    std::u8string content;
    content.reserve(4096 * 100);
    std::u8string_view content_v;
    argv_vector.reserve(255);
    Counts counts;

    // Convert argv into a vector, for convenience
    for (int i = 0; i < argc; i++) {
        argv_vector.emplace_back(argv[i]);
    }

    int ret = parse_arguments::Parse(argc, argv_vector, reading_from_file,
                                     option, file_names);
    if (ret == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    if (!reading_from_file) {
        content.assign((std::istreambuf_iterator<char>(std::cin)),
                       std::istreambuf_iterator<char>());

        content_v = content;

        GetCounts(option, counts, content_v);

        PrintOutput(option, counts, "");

    } else {
        Counts sum_counts;

        for (const std::string& file_name : file_names) {
            fs::path file_path;
            file_path = fs::path(file_name);

            // Handle possible errors in accessing the file
            if (!fs::exists(file_path)) {
                std::println(std::cerr, "File doesn't exist!");
                continue;
            } else if (!fs::is_regular_file(file_path)) {
                std::println(std::cerr, "Invalid file type!");
                continue;
            } else {
                // upgrade to a relative path
                file_path = fs::relative(file_name);
            };

            // Opening a file and assigning the appropriate
            std::ifstream file;
            file = std::ifstream(file_path, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Failed to open file " << file_path.string()
                          << '\n';
                continue;
            }

            content.assign((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
            content_v = content;

            GetCounts(option, counts, content_v);

            file.close();

            sum_counts += counts;

            PrintOutput(option, counts, file_path.string());
        }

        // If we have entered more than 1 file, print a totals row
        if (file_names.size() > 1) {
            PrintOutput(option, sum_counts, "Total");
        }
    }

    return EXIT_SUCCESS;
}
