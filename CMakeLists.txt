cmake_minimum_required(VERSION 3.6)
project(CproTeach)

set(CMAKE_C_STANDARD 99)
INCLUDE_DIRECTORIES(Header)

set(SOURCE_FILES main.c Header/teach.h Header/genlib.h Header/simpio.h Header/strlib.h Header/exceptio.h Header/gcalloc.h
        source/teach.c source/genlib.c source/simpio.c source/strlib.c source/exceptio.c)
set(EXECUTABLE_OUTPUT_PATH Release)
add_executable(CproTeach ${SOURCE_FILES})