project(comexperiment CXX)
#add_executable(client testcom.cpp)
add_library(component MODULE
	component.def
	chello.cpp chello.h
	ihello.h
	chellofactory.cpp chellofactory.h
)
