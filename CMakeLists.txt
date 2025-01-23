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

add_library(wadtek STATIC
    wadtek.cpp
)

target_include_directories(wadtek 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(wadtek 
    PUBLIC
    mio::mio
)

if(WADTEK_BUILD_DUMPWAD)
    add_executable(dumpwad main.cpp)
    target_link_libraries(dumpwad 
        PRIVATE
        wadtek
)
endif()