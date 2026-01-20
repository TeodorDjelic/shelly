add_library(platform_posix
    PosixPipe.cpp
    PosixPipeHandle.cpp
    PosixProcess.cpp
    PosixProcessHandle.cpp
)

target_include_directories(platform_posix
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)