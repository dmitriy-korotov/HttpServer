cmake_minimum_required(VERSION 3.26)



if (NOT DEFINED WEBCPP_SOURCE_DIR)
    message(FATAL_ERROR "Pass your path to WebCpp library source dir: -DWEBCPP_SORCE_DIR=...")
endif()

set(Boost_INCLUDE_DIR "${WEBCPP_SOURCE_DIR}/external/lib/boost_1_82_0")
set(Boost_LIBRARY_DIR "${WEBCPP_SOURCE_DIR}/external/lib/boost_1_82_0/bin/x64/lib")

set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_DEBUG_LIBS     	OFF)
set(Boost_USE_RELEAS_LIBS    	ON)
set(Boost_USE_MULTITHREADED  	ON)
set(Boost_USE_STATIC_RUNTIME 	OFF)



set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})



project(http_server VERSION 1.0 LANGUAGES CXX)



file(GLOB HTTP_SERVER_HEADERS
	include/webcpp/http/*.hpp
	include/webcpp/system/*.hpp
	include/webcpp/util/*.hpp)

file(GLOB HTTP_SERVER_SOURCES
	impl/server/http/*.cpp
	impl/system/*.cpp
	impl/util/*.cpp)



add_library(${PROJECT_NAME} STATIC ${HTTP_SERVER_SOURCES})
add_library(WebCpp::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}

                            PROPERTIES

                            CXX_STANDARD 20
                            CXX_EXTENSIONS OFF
                            CXX_STANDARD_REQUIRED ON
)   



find_package(Boost 1.82.0 REQUIRED COMPONENTS system filesystem) 

if (Boost_FOUND)
    target_include_directories(http_server 
                                    PUBLIC
                                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                    $<INSTALL_INTERFACE:include>
    )
	target_link_libraries(${PROJECT_NAME}
					                PUBLIC
					                Boost::filesystem Boost::system
    )	
else()
    message(FATAL_ERROR, "Can't find boost libraries'")
endif()



install(DIRECTORY include DESTINATION /)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config)
install(EXPORT ${PROJECT_NAME}Config NAMESPACE WebCpp:: DESTINATION "${WEBCPP_SOURCE_DIR}/cmake")

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" DESTINATION "${WEBCPP_SOURCE_DIR}/cmake")



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



if (NOT WEBCPP_SANITIZERS)
	message(STATUS "Sanitizers OFF")
else()
	add_compile_options(-fsanitize=address -fsanitize=fuzzer)
endif()