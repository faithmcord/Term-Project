cmake_minimum_required(VERSION 3.10)
project(Google_tests)

# Add Google Test library
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Create the InventoryTests executable and link it with Google Test
add_executable(InventoryTests unit_tests/InventoryTest.cpp)
target_link_libraries(InventoryTests gtest gtest_main)

# Create the ClienteleTests executable and link it with Google Test
add_executable(ClienteleTests unit_tests/ClienteleTest.cpp)
target_link_libraries(ClienteleTests gtest gtest_main)
