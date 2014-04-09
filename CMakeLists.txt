project(comexperiment CXX)
add_executable(client testcom.cpp)
add_library(component MODULE chello.cpp chello.h ihello.h)
