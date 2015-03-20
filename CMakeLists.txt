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

PROJECT(SDL2pp-tutorial)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# set up SDL2pp library
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
ADD_SUBDIRECTORY(SDL2pp)

# add compilation flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ADD_DEFINITIONS(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
INCLUDE_DIRECTORIES(${SDL2PP_INCLUDE_DIRS})

# define targets
ADD_EXECUTABLE(lesson00 lesson00.cc)
TARGET_LINK_LIBRARIES(lesson00 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson01 lesson01.cc)
TARGET_LINK_LIBRARIES(lesson01 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson02 lesson02.cc)
TARGET_LINK_LIBRARIES(lesson02 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson03 lesson03.cc)
TARGET_LINK_LIBRARIES(lesson03 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson04 lesson04.cc)
TARGET_LINK_LIBRARIES(lesson04 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson05 lesson05.cc)
TARGET_LINK_LIBRARIES(lesson05 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson06 lesson06.cc)
TARGET_LINK_LIBRARIES(lesson06 ${SDL2PP_LIBRARIES})

ADD_EXECUTABLE(lesson07 lesson07.cc)
TARGET_LINK_LIBRARIES(lesson07 ${SDL2PP_LIBRARIES})
