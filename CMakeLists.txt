cmake_minimum_required(VERSION 3.5.1)
project(boost_test)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system thread date_time)

include_directories(
  .
  include
  ${Boost_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/serial_port.cpp
  src/serial_helper.cpp
  src/log/console_log.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
)
