/**
 * @file argument_parser.hpp
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @version 0.1
 * @date 09-09-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstdlib>
#include <iostream>
#include <print>
#include <string>
#include <vector>

#include "ccwc.hpp"

namespace parse_arguments {

[[nodiscard]] inline int Parse(int& argc, std::vector<std::string>& argv,
                               bool& reading_from_file, std::string& option,
                               std::vector<std::string>& file_names) {
    // Set the default flag
    reading_from_file = true;

    if (argc > 1) {
        if (argv[1][0] == '-') {
            if (kAllowedInputOptions.contains(argv[1])) {
                option = argv[1];
            } else {
                // invalid options entered
                option = "";
            }

            if (argc == 2) {
                reading_from_file = false;
            } else {
                // assume that the remaining args are files
                for (int i = 2; i < argc; i++) {
                    file_names.emplace_back(argv[i]);
                }
            }

        } else {
            option = "default";
            for (int i = 1; i < argc; i++) {
                file_names.emplace_back(argv[i]);
            }
        }
    } else {
        option = "default";
        reading_from_file = false;
    }

    // // NOTE: The following commented out code is so that you can understand
    // // how the program is supposed to run. The actual implementation has been
    // // optimized.
    // // ccwc
    // if (argc == 1) {
    //     option = "default";
    //     reading_from_file = false;
    // } else if (argc == 2) {
    //     // ccwc [option]
    //     if (argv[1][0] == '-') {
    //         reading_from_file = false;
    //         if (allowed_options.contains(argv[1])) {
    //             option = argv[1];
    //         } else {
    //             return EXIT_FAILURE;
    //         }
    //     }
    //     // ccwc [path_to_file]
    //     else {
    //         option = "default";
    //         file_names.emplace_back(argv[1]);
    //     }
    // }
    // // ccwc [option] [path_to_file] [path_to_file2] ...
    // else if (argc >= 3) {
    //     // Check if the first arg was supposed to be a flag
    //     if (argv[1][0] == '-') {
    //         // assume that the rest are files
    //         for (int i = 2; i < argc; i++) {
    //             file_names.emplace_back(argv[i]);
    //         }
    //         if (allowed_options.contains(argv[1])) {
    //             option = argv[1];
    //         } else {
    //             return EXIT_FAILURE;
    //         }
    //         // we only have files as inputs
    //     } else {
    //         option = "default";
    //         for (int i = 1; i < argc; i++) {
    //             file_names.emplace_back(argv[i]);
    //         }
    //     }
    // };

    // Handle possible errors in the options
    if (!kAllowedInputOptions.contains(option)) {
        std::println(std::cerr, "Invalid option!");
        std::println(std::cerr, "[USAGE]: {} [option(optional)] [path_to_file]",
                     argv[0]);
        std::println(std::cerr, "Options: -c -l -w -m");
        return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
};

// TODO: Implement argument parsing using new API
[[nodiscard]] inline int Parse(int& argc, std::vector<std::string>& argv,
                               ConfigInfo& config) {
    // Set the default flag
    config.reading_from_file = true;

    if (argc > 1) {
        if (argv[1][0] == '-') {
            if (kOptionMap.contains(argv[1])) {
                config.option = kOptionMap.at(argv[1]);
            } else {
                config.option = Option::INVALID;
            }

            // Secial case
            if (argc == 2) {
                config.reading_from_file = false;
            } else {
                // assume that the rest are files
                for (int i = 2; i < argc; i++) {
                    config.file_names.emplace_back(argv[i]);
                }
            };

        } else {
            config.option = Option::DEFAULT;
            for (int i = 1; i < argc; i++) {
                config.file_names.emplace_back(argv[i]);
            }
        }
    } else {
        config.option = Option::DEFAULT;
        config.reading_from_file = false;
    }

    // Handle possible errors in the options
    if (config.option == Option::INVALID) {
        std::println(std::cerr, "Invalid option!");
        std::println(std::cerr, "[USAGE]: {} [option(optional)] [path_to_file]",
                     argv[0]);
        std::println(std::cerr, "Options: -c -l -w -m");
        return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
};

}  // namespace parse_arguments
