cmake_minimum_required(VERSION 2.8)
project( demos )

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#PROJECT_SOURCE_DIR 变量为含project名的CMakeLists.txt文件所在的目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Default to release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_executable( alg-sort alg-sort.cpp )
add_executable( basecpp basecpp.cpp )
add_executable( farey-list farey-list.cpp )

# Interview Bible for coder
add_executable( linklist ./interviewbible/linklist.cpp )
add_executable( dualinklist ./interviewbible/dualinklist.cpp )
add_executable( queue ./interviewbible/queue.cpp )
add_executable( stack ./interviewbible/stack.cpp )
add_executable( tree ./interviewbible/tree.cpp )
add_executable( graph ./interviewbible/graph.cpp )


# Art code
add_executable( test ./artofcode/test.cpp )

