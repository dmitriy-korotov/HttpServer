cmake_minimum_required(VERSION 3.26 FATAL_ERROR)



set(PROJECT_NAME HttpServer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIRECTORIES include)


set(Boost_USE_DEBUG_LIBS     	OFF)
set(Boost_USE_RELEAS_LIBS    	ON)
set(Boost_USE_MULTITHREADED  	ON)
set(Boost_USE_STATIC_RUNTIME 	OFF)




project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)



link_directories(external/boost_1_82_0/bin/x64/lib)


file(GLOB INCLUDE_FILES "include/*.hpp")
file(GLOB SOURCE_FILES "src/Server/*.cpp")


#add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES})
add_executable(${PROJECT_NAME} 

                src/main.cpp

		        include/Defines.hpp
			include/ResponseTypes.hpp
		
			include/FileReader.hpp
			src/Server/FileReader.cpp
		        include/FileLogger.hpp
		        src/Server/FileLogger.cpp

        		include/Session.hpp
		        src/Server/Session.cpp
		        include/SessionManager.hpp
        		src/Server/SessionManager.cpp

			include/RequestHandle.hpp
			src/Server/RequestHandle.cpp
			include/ResponseGenerators.hpp
			src/Server/ResponseGenerators.cpp

		        include/HttpServer.hpp
		        src/Server/HttpServer.cpp

)


find_package(Boost 1.82.0 COMPONENTS system)

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS} ${INCLUDE_DIRECTORIES})
        target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})	
else()
        message(STATUS "Boost version: ${Boost_VERSION}")
	    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
        message(FATA_ERROR, "CAN'T FIND BOOST LIBRARIES")
endif()



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
