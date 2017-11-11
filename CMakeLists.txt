cmake_minimum_required (VERSION 2.7)
project (VTD-Converter)

include_directories (include)

file (GLOB SOURCES *.c)
add_executable (vtd-converter ${SOURCES})

target_link_libraries (vtd-converter m)
