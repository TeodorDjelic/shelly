#pragma once

#include <optional>

#include "Token.hpp"

namespace shelly::ast {

/// @brief Responsible for lexing an issued command from the terminal. State is mutable, and methods have side-effects.
///        
///        Lexer should be instantiated on a per-input basis.
class Lexer {
public:

    /// @brief Instantiate a lexer for an issued command from the terminal.
    /// @param input Issued command.
    explicit Lexer(std::string input);

    /// @brief Moves the token pointer to the next token, and returns it.
    ///
    ///        If lexer reached the end of the issued command, optional will be returned with no value inside.
    /// @return Optional that contains the next token if it exists and end of the issued command is not reached.
    std::optional<Token> nextToken();

    /// @brief Returns the token pointed at by the token pointer.
    /// @return Optional that contains the current token if it exists.
    std::optional<Token> currentToken();

    /// @brief Returns true if end of the issued command is not reacher. Otherwise, false.
    /// @return True if end of the issued command is not reacher. Otherwise, false.
    bool hasTokensLeft();

protected:
private:
};

} // namespace shelly::ast