#pragma once

#include <string>
#include <cassert>

#include "TokenKind.hpp"
#include "shelly/ast/Location.hpp"

namespace shelly::ast
{

/// @brief Token - This structure provides full information about a lexed token.
///
///        It is not intended to be space efficient, it is intended to return as much
///        information as possible about each returned token.
///
///        This is expected to be compressed into a smaller form if memory footprint
///        is important.
class Token {
public:

    /// @brief Instantiates a token without data.
    /// @param tokenKind Token kind.
    /// @param location  Token location.
    Token(TokenKind tokenKind, Location location) : tokenKind(tokenKind), location(location)
    {
        assert(!isStringLiteral() && "You must assign data to a STRING_LITERAL token!");
    }

    /// @brief Instantiates a token containing data.
    /// @param tokenKind Token kind.
    /// @param location  Token location.
    /// @param data      Token data.
    Token(TokenKind tokenKind, Location location, const std::string& data) : tokenKind(tokenKind), location(location), data(data)
    {
        assert(isStringLiteral() && "Cannot assign data to a non-STRING_LITERAL token!");
    }

    /// @brief Returns kind of this token.
    /// @return Kind of this token.
    inline TokenKind getKind() const { return tokenKind; }

    /// @brief Check if token is of kind tokenKind.
    /// @param tokenKind Token kind for which the check is performed.
    /// @return True if the token kinds match. Otherwise, false.
    inline bool is(TokenKind tokenKind) const { return this->tokenKind == tokenKind; }

    /// @brief Check if the token is a string literal token.
    /// @return True if the token is a string literal token.
    inline bool isStringLiteral() const { return this->tokenKind == TokenKind::STRING_LITERAL; }
    
    /// @brief Returns token data.
    /// @return Token data.
    inline const std::string& getData() const {
        assert(isStringLiteral() && "Cannot get data from a non-STRING_LITERAL token!");
        return data;
    }

    /// @brief Returns token location information.
    /// @return Token location information.
    inline Location getLocation() const { return location; }

protected:
private:

    TokenKind tokenKind;
    Location location;
    std::string data;

};

} // namespace shelly::ast