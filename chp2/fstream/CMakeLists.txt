set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		fstream.cpp
)

add_executable(fstream
	${SOURCE}
)

target_link_libraries(
		fstream
	gtest
)

