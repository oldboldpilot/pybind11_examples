cmake_minimum_required(VERSION 3.0)
project(example)
if(MSVC)
	set(PYBIND11_CPP_STANDARD /std:c++17)
else()
  	set(PYBIND11_CPP_STANDARD -std=c++1z)
endif()
if(APPLE)
	set(PYTHON_INCLUDE_DIR "/anaconda3/include/python3.6m")
	set(PYTHON_LIBRARIES "/anaconda3/lib")
	set(PYTHON_LIBRARY "/anaconda3/lib/libpython3.6m.dylib")
endif()

set(CMAKE_BUILD_TYPE "RELEASE")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})
add_subdirectory(pybind11)
add_subdirectory(tbb)
#pybind11_add_module(example example.cpp)
#include_directories("${CMAKE_SOURCE_DIR}/tbb/include")
#include_directories("${CMAKE_SOURCE_DIR}/pybind11/")

# IF(APPLE)
#     set_target_properties(processGraph PROPERTIES PREFIX ".dylib" )
# ENDIF()

IF (MSVC)
	find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy)
	file(GLOB_RECURSE _HDRS "${CMAKE_SOURCE_DIR}/tbb/include")
  pybind11_add_module(example ${_HDRS}
	${TBB_LIBRARIES}
	example.cpp
	)
ELSE()
  find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy)

	file(GLOB_RECURSE _HDRS "${CMAKE_SOURCE_DIR}/tbb/include")


    pybind11_add_module(example SHARED
		${_HDRS}
		${TBB_LIBRARIES}
		example.cpp
	  )

ENDIF()

#### Additional pybind11 stuff!
 
#post build command 
	add_custom_command(TARGET example POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:example>  ${PROJECT_SOURCE_DIR}
			)

