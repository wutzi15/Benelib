cmake_minimum_required(VERSION 3.0)
project(Benelib)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

#get ROOT flags for the programs not the lib
EXEC_PROGRAM(root-config ARGS --libs OUTPUT_VARIABLE ROOT_LIBS)
EXEC_PROGRAM(root-config ARGS --libdir OUTPUT_VARIABLE ROOT_LIB_DIR)
EXEC_PROGRAM(root-config ARGS --incdir OUTPUT_VARIABLE ROOT_INC)
EXEC_PROGRAM(root-config ARGS --cflags OUTPUT_VARIABLE ROOT_FLAGS)


string(REPLACE "-stdlib=libc++" " " ROOT_LIBS ${ROOT_LIBS})
string(REPLACE "-stdlib=libc++" " " ROOT_FLAGS ${ROOT_FLAGS})

set(CMAKE_CXX_FLAGS "-O2 ${ROOT_FLAGS}" )


include_directories(include)
include_directories(${ROOT_INC})

#add headers and files for the library
include_directories(include)
file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     lib/*.cpp)
file(GLOB headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     include/*.h)


#build the library
add_library(bene SHARED ${headers} ${sources})

set_target_properties(bene PROPERTIES LINK_FLAGS ${ROOT_LIBS})

install(TARGETS bene
		LIBRARY DESTINATION lib)
install(FILES ${headers} DESTINATION include)