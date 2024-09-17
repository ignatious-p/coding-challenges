/**
 * @file test_argument_parser.cpp
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @version 0.1
 * @date 09-09-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>

#include "argument_parser.hpp"

SCENARIO("TESTING ARGUMENT PARSER", "[argument_parser]") {
    std::string option;
    std::vector<std::string> file_names;
    bool reading_from_file;
    int argc;
    std::vector<std::string> argv;

    GIVEN("NO ARGUMENTS") {
        argc = 1;
        argv = {"./ccwc"};
        int ret = parse_arguments::Parse(argc, argv, reading_from_file, option,
                                         file_names);

        REQUIRE(ret == EXIT_SUCCESS);
        REQUIRE(reading_from_file == false);
        REQUIRE(option == "default");
        REQUIRE(file_names.size() == 0);
    }

    GIVEN("ONE ARGUMENT") {
        argc = 2;
        WHEN("Argument is a filename") {
            argv = {"./ccwc", "test.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("desc") {
                REQUIRE(ret == EXIT_SUCCESS);
                REQUIRE(reading_from_file == true);
                REQUIRE(option == "default");
                REQUIRE(file_names.size() == 1);
                REQUIRE(file_names[0] == argv[1]);
            }
        }

        WHEN("Argument is a valid option") {
            argv = {"./ccwc", "-l"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("desc") {
                REQUIRE(ret == EXIT_SUCCESS);
                REQUIRE(reading_from_file == false);
                REQUIRE(option == argv[1]);
                REQUIRE(file_names.size() == 0);
            }
        }

        WHEN("Argument is an invalid option") {
            argv = {"./ccwc", "-p"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("Reading from file is false, and we fail ") {
                REQUIRE(ret == EXIT_FAILURE);
                REQUIRE(reading_from_file == false);
                REQUIRE(option.size() == 0);
                REQUIRE(file_names.size() == 0);
            }
        }
    }

    GIVEN("TWO ARGUMENTS") {
        argc = 3;
        WHEN("Arguments are a valid option and a filename") {
            argv = {"./ccwc", "-l", "test.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("desc") {
                REQUIRE(ret == EXIT_SUCCESS);
                REQUIRE(reading_from_file == true);
                REQUIRE(option.size() != 0);
                REQUIRE(option == argv[1]);
                REQUIRE(file_names.size() == 1);
                REQUIRE(file_names[0] == argv[2]);
            }
        }

        WHEN("Arguments are an invalid option and a filename") {
            argv = {"./ccwc", "-p", "test.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("desc") {
                REQUIRE(ret == EXIT_FAILURE);
                REQUIRE(reading_from_file == true);
                REQUIRE(option.size() == 0);
                REQUIRE(file_names.size() == 1);
                REQUIRE(file_names[0] == argv[2]);
            }
        }

        WHEN("Arguments are two file names") {
            argv = {"./ccwc", "wasd.txt", "test.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);

            THEN("desc") {
                REQUIRE(ret == EXIT_SUCCESS);
                REQUIRE(reading_from_file == true);
                REQUIRE(option.size() != 1);
                REQUIRE(option.compare("default") == 0);
                REQUIRE(file_names.size() == 2);
                REQUIRE(file_names[0] == argv[1]);
                REQUIRE(file_names[1] == argv[2]);
            }
        }
    }

    GIVEN("THREE OR MORE ARGUMENTS") {
        argc = 4;
        WHEN("Arguments are a valid option and 2 filenames") {
            argv = {"./ccwc", "-l", "test.txt", "test2.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("desc") {
                REQUIRE(ret == EXIT_SUCCESS);
                REQUIRE(reading_from_file == true);
                REQUIRE(option.size() != 0);
                REQUIRE(option == argv[1]);
                REQUIRE(file_names.size() != 0);
                REQUIRE(file_names[0] == argv[2]);
                REQUIRE(file_names[1] == argv[3]);
            }
        }

        WHEN("Arguments are an invalid option and 2 filenames") {
            argv = {"./ccwc", "-p", "test.txt", "test2.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);
            THEN("desc") {
                REQUIRE(ret == EXIT_FAILURE);
                REQUIRE(reading_from_file == true);
                REQUIRE(option.size() == 0);
                REQUIRE(file_names.size() != 0);
                REQUIRE(file_names[0] == argv[2]);
                REQUIRE(file_names[1] == argv[3]);
            }
        }

        WHEN("Arguments are three file names") {
            argv = {"./ccwc", "wasd.txt", "test.txt", "test2.txt"};

            int ret = parse_arguments::Parse(argc, argv, reading_from_file,
                                             option, file_names);

            THEN("desc") {
                REQUIRE(ret == EXIT_SUCCESS);
                REQUIRE(reading_from_file == true);
                REQUIRE(option.size() != 0);
                REQUIRE(option.compare("default") == 0);
                REQUIRE(file_names.size() == 3);
                REQUIRE(file_names[0] == argv[1]);
                REQUIRE(file_names[1] == argv[2]);
                REQUIRE(file_names[2] == argv[3]);
            }
        }
    }
}
