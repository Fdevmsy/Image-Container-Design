cmake_minimum_required(VERSION 2.8)
project( AppleAssignment )

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Release)
ENDIF()

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	 add_definitions(-DCOMPILEDWITHC11)
	 message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
	 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	 add_definitions(-DCOMPILEDWITHC0X)
	 message(STATUS "Using flag -std=c++0x.")
else()
	 message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(OpenCV 3.0 QUIET)
if(NOT OpenCV_FOUND)
	 find_package(OpenCV 2.4.3 QUIET)
	 if(NOT OpenCV_FOUND)
			message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
	 endif()
endif()

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
${OpenCV_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} SHARED
src/ImgMat.cpp include/ImgMat.h
src/Utility.cpp include/Utility.h main.cpp src/ImgProc.cpp include/ImgProc.h)

target_link_libraries(${PROJECT_NAME}
${OpenCV_LIBS}
)

add_executable( ImgLibrary main.cpp )
target_link_libraries( ImgLibrary ${PROJECT_NAME} )
