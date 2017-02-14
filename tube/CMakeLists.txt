
add_library(libtube STATIC
	base.cpp
	container_iterator.cpp
	event.cpp
	eventlist.cpp
	filter_iterator.cpp
	object.cpp
	simple_continuous.cpp
	simple_discrete.cpp
	simple_type.cpp
	tube.cpp
	unordered_map.cpp
)

set_property(TARGET libtube PROPERTY CXX_STANDARD 11)

add_subdirectory(test)
