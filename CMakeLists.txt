cmake_minimum_required(VERSION 3.16)
project(mod-twow-ptr)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")
TW_ADD_SCRIPTS("${CMAKE_CURRENT_SOURCE_DIR}/src")
