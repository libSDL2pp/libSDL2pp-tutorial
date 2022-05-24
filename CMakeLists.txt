# SDL2pp tutorial
#
# Written in 2015 by Dmitry Marakasiv <amdmi3@amdmi3.ru>
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(SDL2pp-tutorial LANGUAGES CXX)

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(SDL2pp)

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

# define targets
add_executable(lesson00 lesson00.cc)
target_link_libraries(lesson00 PUBLIC SDL2pp)

add_executable(lesson01 lesson01.cc)
target_link_libraries(lesson01 PUBLIC SDL2pp)

add_executable(lesson02 lesson02.cc)
target_link_libraries(lesson02 PUBLIC SDL2pp)

add_executable(lesson03 lesson03.cc)
target_link_libraries(lesson03 PUBLIC SDL2pp)

add_executable(lesson04 lesson04.cc)
target_link_libraries(lesson04 PUBLIC SDL2pp)

add_executable(lesson05 lesson05.cc)
target_link_libraries(lesson05 PUBLIC SDL2pp)

add_executable(lesson06 lesson06.cc)
target_link_libraries(lesson06 PUBLIC SDL2pp)

add_executable(lesson07 lesson07.cc)
target_link_libraries(lesson07 PUBLIC SDL2pp)
