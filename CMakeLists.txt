cmake_minimum_required(VERSION 3.0)
project(toxic_comments_classification)

file(GLOB_RECURSE tcc_src src/*.cpp src/*.h)

add_executable(toxic_comments_classification ${tcc_src})
target_compile_options(toxic_comments_classification PUBLIC -std=c++11 -W4)