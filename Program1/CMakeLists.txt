cmake_minimum_required(VERSION 3.16)
project(Program1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program1 main.cpp SharedBuffer.cpp SharedBuffer.h DataHelper.cpp DataHelper.h Tcp.cpp Tcp.h SimpleLogger.cpp SimpleLogger.h DateInfo.cpp DateInfo.h)
target_link_libraries(${PROJECT_NAME} -lpthread)