add_library(lexer
    Lexer.cpp
)

target_include_directories(lexer
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)