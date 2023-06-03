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



add_library(${PROJECT_NAME}

			include/system/Time.hpp
			impl/system/Time.cpp
			include/system/FileReader.hpp
			impl/system/FileReader.cpp
		    include/system/FileLogger.hpp
		    impl/system/FileLogger.cpp
			
			include/http/Defines.hpp
			include/http/HttpTypes.hpp

			include/http/Request.hpp
			include/http/Response.hpp
			
			include/http/QueryStringParser.hpp
			impl/server/http/QueryStringParser.cpp
			include/http/Url.hpp
			impl/server/http/Url.cpp
        	include/http/Session.hpp
		    impl/server/http/Session.cpp
		    include/http/SessionManager.hpp
        	impl/server/http/SessionManager.cpp
			include/http/ResponseTemplates.hpp
			impl/server/http/ResponseTemplates.cpp
			include/http/ResponseGenerators.hpp
			impl/server/http/ResponseGenerators.cpp

		    include/http/HttpServer.hpp
		    impl/server/http/HttpServer.cpp

)



find_package(Boost 1.82.0 REQUIRED) 

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS} ${INCLUDE_DIRECTORIES})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})	
else()
    message(STATUS "Boost version: ${Boost_VERSION}")
	message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
    message(FATA_ERROR, "CAN'T FIND BOOST LIBRARIES")
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
