cmake_minimum_required(VERSION 3.20)
project(dream-lang)




set(parser-src 
src/parser/parser.cpp
src/parser/lexer.cpp
src/parser/ast.cpp
)

set(interpreter-src
src/interpreter/interpreter.cpp
)

#i dream
add_executable(dream
src/main.cpp
${interpreter-src}
${parser-src}
)

target_include_directories(dream PUBLIC include/)