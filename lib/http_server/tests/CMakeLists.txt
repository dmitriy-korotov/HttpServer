cmake_minimum_required(VERSION 3.26)



if (NOT DEFINED WEBCPP_SOURCE_DIR)
    message(FATAL_ERROR "Pass your path to WebCpp library source dir: -DWEBCPP_SORCE_DIR=...")
endif()

set(Boost_LIBRARY_DIR ${WEBCPP_SOURCE_DIR}/external/lib/boost_1_82_0/bin/x64/lib)
set(Boost_INCLUDE_DIR ${WEBCPP_SOURCE_DIR}/external/lib/boost_1_82_0)



project(http_server_unit_tests VERSION 1.0 LANGUAGES CXX)



file(GLOB UNIT_TESTS_HTTP_SERVER_SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${UNIT_TESTS_HTTP_SERVER_SOURCES})



find_package(http_server 1.0 REQUIRED)
if (http_server_FOUND)
	set_target_properties(${PROJECT_NAME}

							PROPERTIES

							CXX_STANDARD 20
							CXX_EXTENSIONS OFF
							CXX_STANDARD_REQUIRED ON
	)   
	target_link_libraries(${PROJECT_NAME} PRIVATE WebCpp::http_server)
else()
	message(FATAL_ERROR "Http_server library not found.")
endif()



find_package(Boost 1.82.0 REQUIRED COMPONENTS unit_test_framework filesystem system)
if (Boost_FOUND)
	target_link_libraries(${PROJECT_NAME} PRIVATE Boost::unit_test_framework)
else()
	message(FATAL_ERROR "Boost library not found.")
endif()



if (NOT WEBCPP_SANITIZERS)
	message(STATUS "Sanitizers OFF")
else()
	add_compile_options(-fsanitize=address -fsanitize=fuzzer)
endif()