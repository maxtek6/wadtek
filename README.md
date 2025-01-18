# Wadtek

C++ framework for reading DOOM data files in WAD format.

## Requirements

This project has the following build requirements:
+ C++14
+ CMake

## Usage

This project is designed to provide a portable interface for reading
lumps from WAD files. The parsing and management of game resources is
not currently in the scope of this project. A lump parsing interface
could be layered on top of this framework with minimal effort by using
its binary reader, but this was not included due to the differences in
lumps across different versions of DOOM.