link_libraries(libtube)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")

add_executable (test_container
	test_container.cpp
)

add_executable (test_tube_types
	test_tube_types.cpp
)

add_executable (test_serialization
	test_serialization.cpp
)

