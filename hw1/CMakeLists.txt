cmake_minimum_required(VERSION 3.12) # Optional..
project(hw1)

set(CMAKE_CXX_STANDARD 14) # C++ 14 is needed for the following commands!
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g") # -O0 flag to disable compiler optimizations
# to give more precise breakpoints stops.

FIND_PACKAGE(BISON) # Those two should be installed on your toolchain.
FIND_PACKAGE(FLEX)  # (For cygwin guide look at the pdf inside this repo).

#BISON_TARGET(
#        Parser
#        parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp # path to save output
#)

FLEX_TARGET(
        Lexer
        scanner.lex ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

#ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(a part_a.cpp ${FLEX_Lexer_OUTPUTS})

ADD_EXECUTABLE(b part_b.cpp ${FLEX_Lexer_OUTPUTS})