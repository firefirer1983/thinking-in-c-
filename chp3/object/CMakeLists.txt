set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
        object.cpp
)

add_executable(object
	${SOURCE}
)

target_link_libraries(
		object
	gtest
)

