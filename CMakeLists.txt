cmake_minimum_required(VERSION 3.10)

project(tictactoe_remote VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES_SERVER src/board.cpp src/server.cpp src/main_server.cpp)
set(SOURCES_CLIENT src/client.cpp src/board.cpp src/main_client.cpp)

add_executable(Server ${SOURCES_SERVER})
add_executable(Client ${SOURCES_CLIENT})

# Optional: Compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Server PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(Client PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Server PRIVATE /W4)
    target_compile_options(Client PRIVATE /W4)
endif()