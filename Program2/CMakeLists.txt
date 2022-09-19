cmake_minimum_required(VERSION 3.16)
project(Program2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program2 main.cpp Tcp.cpp Tcp.h DataHelper.cpp DataHelper.h DateInfo.cpp DateInfo.h SimpleLogger.cpp SimpleLogger.h)
