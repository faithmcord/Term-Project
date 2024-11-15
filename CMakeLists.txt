cmake_minimum_required(VERSION 3.29)
project(Term_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Term_Project
        include/Database.h
        src/main/Menu.cpp
        include/Inventory.h
        include/Clientele.h
        include/Customer.h
        include/Product.h
        include/Transaction.h)

add_subdirectory(google_tests)