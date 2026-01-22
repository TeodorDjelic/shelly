add_gtests(LexerTests
    LexerSuite.cpp
)

target_link_libraries(LexerTests PRIVATE lexer)