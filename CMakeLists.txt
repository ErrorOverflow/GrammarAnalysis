cmake_minimum_required(VERSION 3.10)
project(GrammarAnalysis)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 98)

add_executable(GrammarAnalysis WordAnalysis.cpp)