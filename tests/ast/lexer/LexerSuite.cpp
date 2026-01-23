
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "shelly/ast/lexer/Lexer.hpp"

using namespace shelly::ast;
using LexerTestParam = std::pair<std::string, std::vector<Token>>;
class LexerTest : public ::testing::TestWithParam<LexerTestParam> {};

void expectTokensEqual(const Token& expectedToken, const Token& actualToken) {
    EXPECT_EQ(expectedToken.getKind(), actualToken.getKind());

    EXPECT_EQ(expectedToken.getLocation().getCharPosition(), actualToken.getLocation().getCharPosition());


    EXPECT_EQ(expectedToken.getLocation().getLinePosition(), actualToken.getLocation().getLinePosition());

    if (expectedToken.getKind() == TokenKind::STRING_LITERAL) {
        EXPECT_EQ(expectedToken.getData(), actualToken.getData());
    }
}

TEST(LexerTest, LexerConsumeApiVerificationWhenHasTokensLeftIsFalseAndEmptyInput) {
    std::string input = "";

    Lexer lexer(input);

    EXPECT_FALSE(lexer.consume().has_value());
}

TEST(LexerTest, LexerPeekApiVerificationWhenHasTokensLeftIsFalseAndEmptyInput) {
    std::string input = "";

    Lexer lexer(input);

    EXPECT_FALSE(lexer.peek().has_value());
}

TEST(LexerTest, LexerConsumeApiVerificationWhenHasTokensLeftIsFalseAndNonEmptyInput) {
    std::string input = "test.cmd arg1 >output <input";

    Lexer lexer(input);

    Token lastToken(TokenKind::UNKNOWN, Location(0, 0));

    while (lexer.hasTokensLeft()) {
        lastToken = lexer.consume().value();
    }

    EXPECT_FALSE(lexer.consume().has_value());
}

TEST(LexerTest, LexerPeekApiVerificationWhenHasTokensLeftIsFalseAndNonEmptyInput) {
    std::string input = "test.cmd arg1 >output <input";

    Lexer lexer(input);

    while (lexer.hasTokensLeft()) {
        lexer.consume().value();
    }

    EXPECT_FALSE(lexer.peek().has_value());

}

TEST(LexerTest, LexerPeekConsumeApiVerificationWhenHasTokensLeftIsTrue) {
    std::string input = "test.cmd arg1 >output <input";

    Lexer lexer(input);

    while (lexer.hasTokensLeft()) {

        Token token1 = lexer.peek().value();
        Token token2 = lexer.peek().value();
        Token token3 = lexer.consume().value();

        expectTokensEqual(token1, token2);
        expectTokensEqual(token2, token3);
        expectTokensEqual(token1, token3);
    }
}

TEST(LexerTest, LexerHasTokensLeftApiVerificationWhenInputIsEmptyString) {
    std::string input = "";

    Lexer lexer(input);
    EXPECT_FALSE(lexer.hasTokensLeft());
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

INSTANTIATE_TEST_SUITE_P(
    LexerProducesExpectedTokensWhenNoWhitespaces,
    LexerTest,
    ::testing::Values(
        LexerTestParam{
            "test1.cmd|test2.cmd",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test1.cmd"),
                Token(TokenKind::PIPE, Location(1, 10)),
                Token(TokenKind::STRING_LITERAL, Location(1, 11), "test2.cmd"),
            }
        },
        LexerTestParam{
            "test1.cmd>output",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test1.cmd"),
                Token(TokenKind::OUTPUT_REDIRECTION, Location(1, 10)),
                Token(TokenKind::STRING_LITERAL, Location(1, 11), "output"),
            }
        },
        LexerTestParam{
            "test1.cmd<input",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test1.cmd"),
                Token(TokenKind::INPUT_REDIRECTION, Location(1, 10)),
                Token(TokenKind::STRING_LITERAL, Location(1, 11), "input"),
            }
        },
        LexerTestParam{
            "test1.cmd2>output",
            {
                Token(TokenKind::STRING_LITERAL, Location(1, 1), "test1.cmd2"),
                Token(TokenKind::OUTPUT_REDIRECTION, Location(1, 11)),
                Token(TokenKind::STRING_LITERAL, Location(1, 12), "output"),
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
        expectTokensEqual(expectedTokens[i], actual[i]);
    }
}