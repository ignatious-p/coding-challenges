/**
 * @file ccwc.hpp
 * @author Ignatious Peiris (159990296+iggypei@users.noreply.github.com)
 * @version 0.1
 * @date 09-09-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

static const std::set<std::string> kAllowedInputOptions = {"-l", "-w", "-c",
                                                           "-m", "default"};

// TODO: Implement argument parsing using new API
enum class Option { LINES = 0, WORDS, BYTES, CHARACTERS, DEFAULT, INVALID };

// TODO: Implement argument parsing using new API
static const std::unordered_map<std::string, Option> kOptionMap = {
    {"-l", Option::LINES},
    {"-w", Option::WORDS},
    {"-c", Option::BYTES},
    {"-m", Option::CHARACTERS},
    {"default", Option::DEFAULT}};

// TODO: Implement argument parsing using new API
struct ConfigInfo {
    bool& reading_from_file;
    Option& option;
    std::vector<std::string>& file_names;
};
