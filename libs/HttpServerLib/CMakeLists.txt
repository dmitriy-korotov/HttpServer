cmake_minimum_required(VERSION 3.26 FATAL_ERROR)



set(PROJECT_NAME HttpServerLib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIRECTORIES include)


set(Boost_USE_DEBUG_LIBS     	OFF)
set(Boost_USE_RELEAS_LIBS    	ON)
set(Boost_USE_MULTITHREADED  	ON)
set(Boost_USE_STATIC_RUNTIME 	OFF)
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external/boost_1_82_0)



project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)



link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/boost_1_82_0/bin/x64/lib)



file(GLOB HEADERS include/http/*.hpp include/system/*.hpp include/util/*.hpp)
file(GLOB SOURCES impl/server/http/*.cpp impl/system/*.cpp impl/util/*.cpp)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})



find_package(Boost 1.82.0 REQUIRED) 

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS} ${INCLUDE_DIRECTORIES})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})	
else()
    message(STATUS "Boost version: ${Boost_VERSION}")
	message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
    message(FATAL_ERROR, "CAN'T FIND BOOST LIBRARIES")
endif()



target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:>${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS}
	$<INSTALL_INTERFACE:include>
)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)



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
