cmake_minimum_required(VERSION 3.0)
project(example)
if(MSVC)
	set(PYBIND11_CPP_STANDARD /std:c++14)
else()
		set(PYBIND11_CPP_STANDARD -std=c++14)
		#add -ltbb to compile/link command line
		#set (CMAKE_CXX_FLAGS "-ltbb")
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

set(TBB_ROOT_DIR    "${CMAKE_SOURCE_DIR}/tbb")
set(TBB_INCLUDE_DIR    "${CMAKE_SOURCE_DIR}/tbb/include")
set(TBB_INCLUDE_DIRS    "/${CMAKE_SOURCE_DIR}/tbb/include")
if(MSVC)
	set(TBB_LIBRARY    "${CMAKE_SOURCE_DIR}/tbb/Release/tbb_static.lib")
	set(TBB_PROXY_LIBRARY "${CMAKE_SOURCE_DIR}/tbb/Release/tbbmalloc_proxy_static.lib")
	list(APPEND TBB_LIBRARIES  "${CMAKE_SOURCE_DIR}/tbb/Release/tbb_static.lib")
	list(APPEND TBB_LIBRARIES  "${CMAKE_SOURCE_DIR}/tbb/Release/tbbmalloc_static.lib")
	list(APPEND TBB_LIBRARIES  "${CMAKE_SOURCE_DIR}/tbb/Release/tbbmalloc_proxy_static.lib")

elseif(APPLE)
	set(TBB_LIBRARY    "${CMAKE_SOURCE_DIR}/tbb/Release/libtbb_static.a")
	set(TBB_PROXY_LIBRARY "${CMAKE_SOURCE_DIR}/tbb/Release/libtbbmalloc_proxy_static.a")
	list(APPEND TBB_LIBRARIES  "${CMAKE_SOURCE_DIR}/tbb/Release/libtbb_static.a")
	list(APPEND TBB_LIBRARIES  "${CMAKE_SOURCE_DIR}/tbb/Release/libtbbmalloc_static.a")
	list(APPEND TBB_LIBRARIES  "${CMAKE_SOURCE_DIR}/tbb/Release/libtbbmalloc_proxy_static.a")
	
endif()
link_directories("${TBB_ROOT_DIR}/Release")
add_subdirectory(pybind11)
add_subdirectory(tbb)

find_package(TBB COMPONENTS tbbmalloc )
include_directories("${CMAKE_SOURCE_DIR}/tbb/include")
include_directories("${CMAKE_SOURCE_DIR}/pybind11/")

# IF(APPLE)
#     set_target_properties(processGraph PROPERTIES PREFIX ".dylib" )
# ENDIF()

IF (MSVC)
	
	find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy)
	file(GLOB_RECURSE _HDRS "${CMAKE_SOURCE_DIR}/tbb/include")
  pybind11_add_module(example SHARED ${_HDRS}
	example.cpp
	)
ELSE()
  #find_package(TBB)

	file(GLOB_RECURSE _HDRS "${CMAKE_SOURCE_DIR}/tbb/include")


    pybind11_add_module(example SHARED ${_HDRS}  example.cpp )

ENDIF()
#target_include_directories(example PRIVATE ${TBB_INCLUDE_DIRS})
#target_compile_definitions(example  PRIVATE ${TBB_DEFINITIONS})
target_link_libraries(example PRIVATE ${TBB_LIBRARIES})


#### Additional pybind11 stuff!
 
#post build command 
	add_custom_command(TARGET example POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:example>  ${PROJECT_SOURCE_DIR}
			)

