cmake_minimum_required(VERSION 3.26 FATAL_ERROR)



set(PROJECT_NAME HttpServer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)



option(MY_LIBTESTING "Включить модульное тестирование" ON)
option(MY_COVERAGE "Включить измерение покрытия кода тестами" OFF)

if (NOT MY_LIBTESTING)
    message(STATUS "Тестирование проекта HttpServer выключено")
else()
    add_subdirectory(tests)
endif()



add_subdirectory(libs/HttpServerLib)
link_directories(libs/HttpServerLib/external/boost_1_82_0/bin/x64/lib)



add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC HttpServerLib)



add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)