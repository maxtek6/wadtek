cmake_minimum_required(VERSION 3.15)

project(wadtek)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
    mio
    GIT_REPOSITORY https://github.com/maxtek6/mio.git
    GIT_TAG master
)
FetchContent_MakeAvailable(mio)

add_library(wadtek STATIC
    wadtek.cpp
)

target_include_directories(wadtek 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(wadtek 
    PUBLIC
    mio
)