#include "shelly/ast/lexer/Lexer.hpp"
#include "shelly/ast/nodes/CommandASTNode.hpp"
#include <optional>

namespace shelly::ast
{
    
class Parser {
public:

    Parser(Lexer& lexer) : lexer(lexer) {}

    std::optional<CommandASTNode> parse();

protected:
private:

    Lexer& lexer;

};

} // namespace shelly::ast
