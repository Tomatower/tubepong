project (tubepong)


cmake_minimum_required(VERSION 3.7)

add_subdirectory (tube)

link_libraries (libtube)
add_executable (tubepong
	main.cpp
	physics.cpp
	gui.cpp
	)

set_property(TARGET tubepong PROPERTY CXX_STANDARD 11)


