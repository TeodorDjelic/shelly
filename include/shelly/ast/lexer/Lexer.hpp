#pragma once

#include <optional>

#include "shelly/common/OperationResult.hpp"

#include "Token.hpp"

namespace shelly::ast {

/// @brief Responsible for lexing an issued command from the terminal. State is mutable, and methods have side-effects.
///        
///        Lexer should be instantiated on a per-input basis.
/// @todo Add support for quoted strings, double quoted strings, tick quoted strings, and escaped characters.
class Lexer {
public:

    /// @brief Instantiate a lexer for an issued command from the terminal.
    /// @param input Issued command.
    explicit Lexer(std::string input);

    /// @brief Returns the next token, and then moves the token pointer to the next token.
    ///
    ///        If lexer reached the end of the issued command, optional will be returned with no value inside.
    /// @return Optional that contains the next token if it exists and the end of the issued command is not reached.
    std::optional<Token> consume();

    /// @brief Returns the next token, without moving the token pointer to the next token.
    ///
    ///        If lexer reached the end of the issued command, optional will be returned with no value inside.
    /// @return Optional that contains the current token if it exists.
    std::optional<Token> peek();

    /// @brief Returns true if end of the issued command is not reached. Otherwise, false.
    /// @return True if end of the issued command is not reached. Otherwise, false.
    bool hasTokensLeft();

protected:
private:

    std::optional<Token> nextToken;
    bool nextTokenLoaded = false;

    std::string input;
    uint16_t charPointer = 0;

    inline char getAndAdvanceChar();
    inline char getAndRetainChar();
    inline void reverseAdvanceChar();
    inline bool hasCharsLeft();

    void skipWhitespace();

    void loadNextToken();

    inline OperationResult loadStringLiteral();

};

} // namespace shelly::ast