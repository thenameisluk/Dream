cmake_minimum_required(VERSION 3.20)
project(dream)


set(interpreter-src 
src/interpreter/interpreter.cpp
)

set(parser-src 
src/parser/parser.cpp
)

set(lexer-src
src/lexer/lexer.cpp
)

#i dream
add_executable(idream
src/interpreter/main.cpp
${interpreter-src}
${parser-src}
${lexer-src}
)

target_include_directories(idream PUBLIC include/)