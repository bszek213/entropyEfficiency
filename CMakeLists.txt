cmake_minimum_required(VERSION 3.15)
#Project name
project(Entropy)

#Set cmake std = 17
set(CMAKE_CXX_STANDARD 17)

# Add subfolder named [include] to the list directories
include_directories(include)

#find libaries for .cpp
set(MYSOURCEFILES src/helper/sampenZero.cpp)

#add the library now
add_library(helper ${MYSOURCEFILES})

#find package for OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS}) 

add_executable(Entropy src/mainSampen.cpp)

target_link_libraries(Entropy helper ${OpenCV_LIBS})

# Specify where to place build products if we also want to do a [make install]
install(TARGETS Entropy helper
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
	ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)
# Copy the headers (for people who want to use our libraries) to install path
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
	FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
