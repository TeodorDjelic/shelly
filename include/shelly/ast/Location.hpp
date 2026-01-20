#pragma once

#include <cstdint>

namespace shelly::ast
{

/// @brief Contains information about a location inside an issued command.
///
///        Indexing starts at 1.
class Location {
public:

    /// @brief Instantiate a location inside an issued command.
    /// @param linePosition line number.
    /// @param charPosition position within the line, measured in characters.
    explicit Location(uint16_t linePosition, uint16_t charPosition): linePosition(linePosition), charPosition(charPosition) {}
    
    /// @brief Returns the line number.
    /// @return 16-bit integer line number.
    inline uint16_t getLinePosition() { return linePosition; }

    /// @brief Returns the position within the line, measured in characters.
    /// @return 16-bit integer character position.
    inline uint16_t getCharPosition() { return charPosition; }

protected:
private:

    uint16_t linePosition;
    uint16_t charPosition;

};

} // namespace shelly::ast
