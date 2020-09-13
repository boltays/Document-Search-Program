cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test LANGUAGES CXX)


add_executable(main
  main.cpp
  src/inverted_index.cpp
  include/inverted_index.hpp
)

target_link_libraries(main PUBLIC -lstdc++fs)

# c++17 ----
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

include_directories(${PROJECT_INCLUDE_DIR})
include_directories(include)

add_subdirectory(test)



