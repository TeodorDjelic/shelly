#include <map>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "shelly/ast/lexer/Lexer.hpp"

using namespace shelly::ast;
using LexerTestParam = std::pair<std::string, std::vector<Token>>;
class LexerTest : public ::testing::TestWithParam<LexerTestParam> {};

void expectTokensEqual(const Token& token1, const Token& token2) {
    EXPECT_EQ(token1.getKind(), token2.getKind());

    EXPECT_EQ(token1.getLocation().getCharPosition(), token2.getLocation().getCharPosition());

        
    EXPECT_EQ(token1.getLocation().getLinePosition(), token2.getLocation().getLinePosition());

    if (token1.getKind() == TokenKind::STRING_LITERAL) {
        EXPECT_EQ(token1.getData(), token2.getData());
    }
}

TEST(LexerTest, LexerPeekApiVerification) {
    std::string input = "test.cmd arg1 >output <input";

    Lexer lexer(input);

    std::vector<Token> actual;

    while (lexer.hasTokensLeft()) {

        Token token1 = lexer.peek().value();
        Token token2 = lexer.peek().value();
        Token token3 = lexer.consume().value();

        expectTokensEqual(token1, token2);
        expectTokensEqual(token2, token3);
        expectTokensEqual(token1, token3);
    }
}

INSTANTIATE_TEST_SUITE_P(
    StringsAndErrorRedirectionsLexedCorrectly,
    LexerTest,
    ::testing::Values(
        LexerTestParam(
            "test.cmd 2>test",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test.cmd"),
                Token(TokenKind::ERROR_REDIRECTION, Location(1, 10)),
                Token(TokenKind::STRING_LITERAL, Location(1, 12), "test"),
            }
        ),
        LexerTestParam(
            "test.cmd 2test",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test.cmd"),
                Token(TokenKind::STRING_LITERAL, Location(1, 10), "2test"),
            }
        ),
        LexerTestParam(
            "test.cmd >2test",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test.cmd"),
                Token(TokenKind::OUTPUT_REDIRECTION, Location(1, 10)),
                Token(TokenKind::STRING_LITERAL, Location(1, 11), "2test"),
            }
        )
    )
);

INSTANTIATE_TEST_SUITE_P(
    LexerProducesExpectedTokensSuccess,
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

TEST_P(LexerTest, LexerTokensTests) {
    const auto& [input, expectedTokens] = GetParam();

    Lexer lexer(input);

    std::vector<Token> actual;

    while (lexer.hasTokensLeft()) {
        actual.push_back(lexer.consume().value());
    }

    ASSERT_EQ(actual.size(), expectedTokens.size());

    for (size_t i = 0; i < actual.size(); ++i) {
        expectTokensEqual(actual[i], expectedTokens[i]);
    }
}