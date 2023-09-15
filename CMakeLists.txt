cmake_minimum_required(VERSION 3.20.0)
add_executable(bincp)
project(bincp)

target_include_directories(bincp PRIVATE
    src
)

target_sources(bincp PRIVATE
    src/main.c
)
