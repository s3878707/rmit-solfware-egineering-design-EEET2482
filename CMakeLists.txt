cmake_minimum_required(VERSION 3.24)
project(GroupAsm)

set(CMAKE_CXX_STANDARD 17)

add_executable(GroupAsm main.cpp Member.cpp Member.h House.cpp House.h Application.cpp Application.h Database.cpp Database.h Admin.cpp Admin.h)
