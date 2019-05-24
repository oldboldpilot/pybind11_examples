cmake_minimum_required(VERSION 2.8.12)
project(example)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)

IF(APPLE)
    set_target_properties(processGraph PROPERTIES PREFIX ".dylib" )
ENDIF()

IF (MSVC)
    pybind11_add_module(processGraph SHARED
		ProcessGraph.cpp
	)
ELSE()
  find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy)
	find_package(PythonLibs)
	file(GLOB_RECURSE _HDRS "${CMAKE_SOURCE_DIR}/tbb/include")


    #pybind11_add_module(processGraph SHARED
		#${_HDRS}
		#${TBB_LIBRARIES}
		# ProcessGraph.cpp
	  # )

ENDIF()

#### Additional pybind11 stuff!
 
#post build command 
	add_custom_command(TARGET processGraph POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:processGraph>  ${PROJECT_SOURCE_DIR}
			)

