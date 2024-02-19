cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project ( calc )

add_library( maths SHARED adder.cpp ) 

set_target_properties(maths PROPERTIES IMPORT_SUFFIX ".lib")

add_executable( calc calc.cpp )
target_link_libraries( calc maths ) 