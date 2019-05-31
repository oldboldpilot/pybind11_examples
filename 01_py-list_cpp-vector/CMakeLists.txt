cmake_minimum_required(VERSION 3.0)
project(example)

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
	find_package(PythonLibs)
	file(GLOB_RECURSE _HDRS "${CMAKE_SOURCE_DIR}/tbb/include")
  pybind11_add_module(example SHARED
	${_HDRS}
	${TBB_LIBRARIES}
	example.cpp
	)
ELSE()
  find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy)
	find_package(PythonLibs)
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

