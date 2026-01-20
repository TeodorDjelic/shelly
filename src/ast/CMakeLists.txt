add_library(ast INTERFACE)

add_subdirectory(lexer)
target_link_libraries(ast INTERFACE lexer)

add_subdirectory(parser)
target_link_libraries(ast INTERFACE parser)