add_library(platform INTERFACE)

target_include_directories(platform
    INTERFACE 
        ${PROJECT_SOURCE_DIR}/include
)

if(WIN32)
    add_subdirectory(windows)
    target_link_libraries(platform INTERFACE platform_windows)
else()
    add_subdirectory(posix)
    target_link_libraries(platform INTERFACE platform_posix)
endif()