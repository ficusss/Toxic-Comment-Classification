cmake_minimum_required(VERSION 3.0)
project(toxic_comments_classification)

file(GLOB_RECURSE tcc_src includes/*.hpp src/*.cpp src/*.h src/*.hpp)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(toxic_comments_classification PUBLIC -std=c++11 -W4)
endif()

add_executable(toxic_comments_classification ${tcc_src})
