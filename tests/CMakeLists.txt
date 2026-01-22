function (add_gtests test_dirname)
    add_executable(${test_dirname}
        ${ARGN}
    )

    target_include_directories(${test_dirname}
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(${test_dirname}
        PRIVATE
        GTest::gtest
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(${test_dirname})
endfunction()

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/third_party/googletest
    ${CMAKE_BINARY_DIR}/googletest-build
)