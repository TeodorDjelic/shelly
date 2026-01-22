#include <map>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "shelly/ast/lexer/Lexer.hpp"

using namespace shelly::ast;

using LexerTestParam = std::pair<std::string, std::vector<Token>>;
class LexerTest : public ::testing::TestWithParam<LexerTestParam> {};

TEST_P(LexerTest, LexerProducesExpectedTokensSuccess) {
    const auto& [input, expectedTokens] = GetParam();

    Lexer lexer(input);

    std::vector<Token> actual;

    while (lexer.hasTokensLeft()) {
        actual.push_back(lexer.consume().value());
    }

    ASSERT_EQ(actual.size(), expectedTokens.size());

    for (size_t i = 0; i < actual.size(); ++i) {
        EXPECT_EQ(actual[i].getKind(), expectedTokens[i].getKind());

        EXPECT_EQ(actual[i].getLocation().getCharPosition(), expectedTokens[i].getLocation().getCharPosition())
            << "Token index " << i;

            
        EXPECT_EQ(actual[i].getLocation().getLinePosition(), expectedTokens[i].getLocation().getLinePosition())
            << "Token index " << i;

        if (actual[i].getKind() == TokenKind::STRING_LITERAL) {
            EXPECT_EQ(actual[i].getData(), expectedTokens[i].getData())
                << "Token index " << i;
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    LexerCases,
    LexerTest,
    ::testing::Values(
        LexerTestParam{
            "test.cmd > < ab",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test.cmd"),
                Token(TokenKind::OUTPUT_REDIRECTION, Location(1, 10)),
                Token(TokenKind::INPUT_REDIRECTION, Location(1, 12)),
                Token(TokenKind::STRING_LITERAL, Location(1, 14), "ab"),
            }
        },
        LexerTestParam{
            "test.cmd ab | < | prog",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test.cmd"),
                Token(TokenKind::STRING_LITERAL, Location(1, 10), "ab"),
                Token(TokenKind::PIPE, Location(1, 13)),
                Token(TokenKind::INPUT_REDIRECTION, Location(1, 15)),
                Token(TokenKind::PIPE, Location(1, 17)),
                Token(TokenKind::STRING_LITERAL, Location(1, 19), "prog"),
            }
        },
        LexerTestParam{
            "test.cmd ab 2>test",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test.cmd"),
                Token(TokenKind::STRING_LITERAL, Location(1, 10), "ab"),
                Token(TokenKind::ERROR_REDIRECTION, Location(1, 13)),
                Token(TokenKind::STRING_LITERAL, Location(1, 15), "test"),
            }
        },
        LexerTestParam{
            "",
            {
            }
        }
    )
);