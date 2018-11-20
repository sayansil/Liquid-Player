cmake_minimum_required(VERSION 2.8.12)
project(Dlib_tests)
set(cmake_cxx_flags "-std=c++14 -O3 -march=native")
include(/home/rohan/Downloads/Compressed/dlib-19.16/dlib/cmake)

find_package(OpenCV REQUIRED)

macro(add_code name)
   add_executable(${name} ${name}.cpp)
   target_link_libraries(${name} dlib::dlib )
   target_link_libraries(${name} ${OpenCV_LIBS} )
   target_link_libraries(${name} vlc)
endmacro()

add_code(test1)
add_code(test2)
add_code(test3)
