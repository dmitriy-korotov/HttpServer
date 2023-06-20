cmake_minimum_required(VERSION 3.26)



option(WEBCPP_TESTING "Enable unit testing" ON)
option(WEBCPP_SANITIZERS "Enable sanitizers" ON)



set(WEBCPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR})



project(WebCpp VERSION 1.0 LANGUAGES CXX)



add_subdirectory(lib/http_server)



if (NOT WEBCPP_TESTING)
    message(STATUS "Testing WebCpp project turned off")
else()
    add_subdirectory(lib/http_server/tests)
endif()