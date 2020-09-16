cmake_minimum_required(VERSION 3.5)

project(CompilerRust)

set(SOURCES
    Ast.cpp
    Generator.cpp
    Lexer.cpp
    Log.cpp
    Node.cpp
    Parser.cpp
    Source.cpp
    Token.cpp
    Variable.cpp
    Variable_table.cpp
)

set(HEADERS
    Ast.h
    Generator.h
    Lexer.h
    Log.h
    Node.h
    Parser.h
    Token.h
    Variable.h
    Variable_table.h
)

add_executable(CompilerRust ${SOURCES} ${HEADERS})
set_target_properties(
    CompilerRust PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
