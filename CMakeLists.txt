cmake_minimum_required(VERSION 2.8)
project(Benelib)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_INSTALL_PREFIX /usr)
#get ROOT flags for the programs not the lib
EXEC_PROGRAM(root-config ARGS --libs OUTPUT_VARIABLE ROOT_LIBS)
EXEC_PROGRAM(root-config ARGS --libdir OUTPUT_VARIABLE ROOT_LIB_DIR)
EXEC_PROGRAM(root-config ARGS --incdir OUTPUT_VARIABLE ROOT_INC)
EXEC_PROGRAM(root-config ARGS --cflags OUTPUT_VARIABLE ROOT_FLAGS)


string(REPLACE "-stdlib=libc++" " " ROOT_LIBS ${ROOT_LIBS})
string(REPLACE "-stdlib=libc++" " " ROOT_FLAGS ${ROOT_FLAGS})

set(CMAKE_CXX_FLAGS "-O2 ${ROOT_FLAGS} -std=c++1y" )


include_directories(include)
include_directories(${ROOT_INC})

#add headers and files for the library
include_directories(include)
file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     lib/*.cpp)
file(GLOB headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     include/*.h)
file(GLOB test_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	src/*.cpp)


#build the library
add_library(bene SHARED ${headers} ${sources})

set_target_properties(bene PROPERTIES LINK_FLAGS "${ROOT_LIBS} -lboost_system -lboost_filesystem")

install(TARGETS bene
		LIBRARY DESTINATION lib)
install(FILES ${headers} DESTINATION include)

option(TESTS "Build Test program " OFF)
option(BOOST_SINGLETON "Use BOOST to build the singleton" OFF)
option(PARALLEL_OMP "Build OMP version" OFF)

if(PARALLEL_OMP)
	set(CMAKE_CXX_FLAGS "-DBENE_OMP -fopenmp ${CMAKE_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "-fopenmp -lpthread ${CMAKE_EXE_LINKER_FLAGS}")
endif()

if(TESTS) 
	include_directories(include)
	add_executable(test_bene ${test_src})
	link_directories(${CMAKE_CURRENT_SOURCE_DIR})
	if(BOOST_SINGLETON)
		add_definitions(-DBENE_BOOST_SINGLETON)
		target_link_libraries(test_bene bene boost_system boost_thread ${ROOT_LIBS})
	else()
		target_link_libraries(test_bene bene ${ROOT_LIBS})
	endif()
endif()