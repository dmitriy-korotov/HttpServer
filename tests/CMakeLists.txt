cmake_minimum_required(VERSION 3.26 FATAL_ERROR)



set(PROJECT_NAME UnitTests)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)



link_directories(../libs/HttpServerLib/external/boost_1_82_0/bin/x64/lib)



file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC HttpServerLib)
