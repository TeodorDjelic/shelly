#include "shelly/ast/lexer/Lexer.hpp"

namespace shelly::ast
{

Lexer::Lexer(std::string input) : input(input) {}

std::optional<Token> Lexer::consume() {
    loadNextToken();
    if (!nextTokenLoaded) {
        return std::nullopt;
    }
    
    nextTokenLoaded = false;
    return nextToken;
}

std::optional<Token> Lexer::peek() {
    loadNextToken();
    if (!nextTokenLoaded) {
        return std::nullopt;
    }

    return nextToken;
}

bool Lexer::hasTokensLeft() {
    skipWhitespace();
    return hasCharsLeft();
}

void Lexer::loadNextToken() {

    if (nextTokenLoaded) {
        return;
    }

    if (!hasTokensLeft()) {
        return;
    }
    
    Location tokenLocation = Location(1, charPointer + 1);

    OperationResult tokenLexingResult = OperationResult::Success;

    char currChar = getAndRetainChar();
    switch (currChar) {
        case '|': {
            getAndAdvanceChar();
            nextToken = Token(TokenKind::PIPE, tokenLocation);
            break;
        }
        case '>': {
            getAndAdvanceChar();
            nextToken = Token(TokenKind::OUTPUT_REDIRECTION, tokenLocation);
            break;
        }
        case '<': {
            getAndAdvanceChar();
            nextToken = Token(TokenKind::INPUT_REDIRECTION, tokenLocation);
            break;
        }
        case '2': {
            getAndAdvanceChar();
            if (hasCharsLeft() && getAndRetainChar() == '>') {
                getAndAdvanceChar();
                nextToken = Token(TokenKind::ERROR_REDIRECTION, tokenLocation);
                break;
            }
            reverseAdvanceChar();
        }
        [[fallthrough]];
        default: {
            tokenLexingResult = loadStringLiteral();
            break;
        }
    }

    if (tokenLexingResult != OperationResult::Success) {
        nextToken = Token(TokenKind::UNKNOWN, tokenLocation);
    }
    nextTokenLoaded = true;
}

char Lexer::getAndAdvanceChar() {
    return input[charPointer++];
}

char Lexer::getAndRetainChar() {
    return input[charPointer];
}

void Lexer::reverseAdvanceChar() {
    charPointer--;
}

inline bool Lexer::hasCharsLeft() {
    return charPointer < input.size();
}

void Lexer::skipWhitespace() {
    while (hasCharsLeft() && whitespace.contains(getAndRetainChar())) {
        getAndAdvanceChar();
    }
}

Lexer::OperationResult Lexer::loadStringLiteral() {
    uint16_t startingChar = charPointer + 1;
    std::string tokenData;

    while (hasCharsLeft()) {
        char c = getAndRetainChar();
        if (whitespace.contains(c) || c == '|' || c == '>' || c == '<') {
            break;
        }
        tokenData += getAndAdvanceChar();
    }

    nextToken = Token(TokenKind::STRING_LITERAL, Location(1, startingChar), tokenData);

    return OperationResult::Success;
}

} // namespace shelly::ast