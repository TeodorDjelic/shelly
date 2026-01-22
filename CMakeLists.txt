cmake_minimum_required(VERSION 3.20)
project(Shelly VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTS "Build tests" ON)

add_subdirectory(src)

if (ENABLE_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()