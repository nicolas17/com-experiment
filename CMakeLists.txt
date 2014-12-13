cmake_minimum_required(VERSION 2.6)
project(comexperiment)

add_custom_command(OUTPUT hello.h hello_i.c hello_p.c dlldata.c hello.tlb
    COMMAND midl ${CMAKE_CURRENT_SOURCE_DIR}/hello.idl
    MAIN_DEPENDENCY hello.idl
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(component MODULE
    component.def
    chello.cpp chello.h
    chellofactory.cpp chellofactory.h

    # generated from the IDL
    hello_i.c
)
add_executable(client
    client.cpp
    hello_i.c
)
