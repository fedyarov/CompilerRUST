cmake_minimum_required(VERSION 3.5)

project(CompilerRust)

set(SOURCES
    Source.cpp
    Lexer.cpp
)

set(HEADERS
    Lexer.h
)

add_executable(CompilerRust ${SOURCES} ${HEADERS})
set_target_properties(
    CompilerRust PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
