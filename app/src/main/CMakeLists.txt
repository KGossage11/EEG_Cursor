cmake_minimum_required(VERSION 3.22.1)

project(bcicore)

add_library(
        bcicore
        SHARED
        cpp/bcicore.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        bcicore
        ${log-lib}
)
