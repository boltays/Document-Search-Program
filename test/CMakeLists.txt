# We need thread support
find_package(Threads REQUIRED)


#if(CMAKE_COMPILER_IS_GNUCXX)
#    add_definitions(-std=gnu++0x)
#endif()

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include")



add_library(inverted_index ${PROJECT_SOURCE_DIR}/src/inverted_index.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

target_link_libraries(inverted_index PUBLIC -lstdc++fs)

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(TARGET inverted_index PROPERTY CXX_STANDARD 17)
set_property(TARGET inverted_index PROPERTY CXX_STANDARD_REQUIRED ON)




add_executable(test_main test_main.cpp)

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(TARGET test_main PROPERTY CXX_STANDARD 17)
set_property(TARGET test_main PROPERTY CXX_STANDARD_REQUIRED ON)



target_link_libraries(
    test_main
    inverted_index
    libgtest
)
