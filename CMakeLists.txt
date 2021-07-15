cmake_minimum_required(VERSION 3.0.0)
project(cparser VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
add_executable(cparser main.cpp src/lexer.cpp src/parser.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
