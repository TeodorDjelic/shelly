add_library(core
    Shell.cpp
)

target_include_directories(core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core
    PRIVATE platform
)

target_link_libraries(core
    PRIVATE ast
)