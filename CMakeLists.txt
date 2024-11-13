cmake_minimum_required(VERSION 3.29)
project(Term_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Term_Project
        include/Database.h
        src/main/Includes.cpp
        src/main/Main.cpp
        src/main/Menu.cpp
        include/Inventory.h
        include/Clientele.h
        src/main/Utilities.cpp
        include/Customer.h
        include/Product.h)

add_subdirectory(google_tests)