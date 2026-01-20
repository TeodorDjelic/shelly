#pragma once

#include <set>

namespace shelly::ast
{

/// @brief Provides a simple uniform namespace for tokens inside a single command.
enum TokenKind {
    STRING_LITERAL,
    PIPE,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    ERROR_REDIRECTION,
    UNKNOWN
};

/// @todo migrate whitespace set to a config file.
const std::set<char> whitespace = {' ', '\t', '\n', '\r', '\v', '\f'};

} // namespace shelly::ast