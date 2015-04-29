cmake_minimum_required(VERSION 3.0)
project(Benelib)

set(CMAKE_CXX_COMPILER g++)

#check the compiler version to enable c++11 if possible 
if(CMAKE_COMPILER_IS_GNUCXX)
  exec_program(${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE _compiler_output)
  string(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" gcc_compiler_version ${_compiler_output})
  message(STATUS "C++ compiler version: ${gcc_compiler_version} [${CMAKE_CXX_COMPILER}]")
endif(CMAKE_COMPILER_IS_GNUCXX)

#enable c++11 if possible
if(gcc_compiler_version VERSION_GREATER "4.7.0")
	set(CMAKE_CXX_FLAGS "-std=c++11 -O2 " )
else()
	set(CMAKE_CXX_FLAGS "-O2 " )
endif()

#get ROOT flags for the programs not the lib
EXEC_PROGRAM(root-config ARGS --libs OUTPUT_VARIABLE ROOT_LIBS)
EXEC_PROGRAM(root-config ARGS --libdir OUTPUT_VARIABLE ROOT_LIB_DIR)
EXEC_PROGRAM(root-config ARGS --cflags OUTPUT_VARIABLE ROOT_FLAGS)

include_directories(include)

#add headers and files for the library
include_directories(include)
file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     lib/*.cpp)
file(GLOB headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     include/*.h)

#build the library
add_library(bene SHARED ${headers} ${sources})

install(TARGETS bene
		LIBRARY DESTINATION lib)
install(FILES ${headers} DESTINATION include)