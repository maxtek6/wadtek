# Copyright (c) 2025 Maxtek Consulting

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.15)

project(wadtek)

option(WADTEK_BUILD_DUMPWAD "Build dumpwad" OFF)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
    mio
    GIT_REPOSITORY https://github.com/maxtek6/mio.git
    GIT_TAG master
)
FetchContent_MakeAvailable(mio)

add_library(wadtek_a STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bytes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wadtek.cpp
)

target_include_directories(wadtek_a 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(wadtek_a 
    PUBLIC
    mio::mio
)

if(WADTEK_BUILD_DUMPWAD)
    add_executable(dumpwad ${CMAKE_CURRENT_SOURCE_DIR}/dumpwad/main.cpp)
    target_link_libraries(dumpwad 
        PRIVATE
        wadtek_a
)
endif()