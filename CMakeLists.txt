cmake_minimum_required(VERSION 3.5.1)
project(boost_test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
