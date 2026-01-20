add_library(platform_windows
    WindowsPipeHandle.cpp
    WindowsPipe.cpp
    WindowsProcessHandle.cpp
    WindowsProcess.cpp
)

target_include_directories(platform_windows
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(platform_windows
    PRIVATE kernel32
)