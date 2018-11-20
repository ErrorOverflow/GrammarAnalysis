cmake_minimum_required(VERSION 3.12)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(GrammarAnalysis main.cpp WordAnalysis.cpp WordAnalysis.h FileIO.cpp FileIO.h lib.cpp lib.h LexicalAnalysis.cpp LexicalAnalysis.h Exception.cpp Exception.h)