project(KGSANDBOX)
cmake_minimum_required(VERSION 2.8)

execute_process(COMMAND ${CMAKE_COMMAND} "-Wno-dev")

#设置生成动态库和静态库
if (WIN32)
    set(BUILD_SHARED_LIBS "On")
else(UNIX)
    set(BUILD_SHARED_LIBS "On")
endif()

#设置编译发布版本选项，发布新的版本需要开启此语句
#add_definitions(-DRELEASE_ON)

#设置调试库的后缀
set(CMAKE_DEBUG_POSTFIX "d")

#设置库和可执行文件的输出文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

IF(WIN32 AND NOT ANDROID)
	SET(LOG4_CPP_DIR ${3RD_PARTY_DIR})
	SET(GDAL_DIR ${3rdparty})
	SET(3RD_PARTY_DIR "" CACHE PATH "Set to base lib install path")
	SET(OSG_DIR "" CACHE PATH "Set to base OpenSceneGraph install path")

    include(find_hg_osg)
	include(find_hg_log4cpp)
	include(find_hg_gdal)
	
	include_directories("${3RD_PARTY_DIR}/include")
	include_directories("${OSG_DIR}/include")
	
	link_directories("${3RD_PARTY_DIR}/lib")
	link_directories("${OSG_DIR}/lib")
	

ENDIF()

find_package(OpenGL)

find_package(OpenSceneGraph 3.2.1 REQUIRED 
	osg 
	osgGA 
	osgDB 
	osgViewer 
	osgUtil 
	osgText 
	osgQt 
	osgVolume 
	osgTerrain 
	osgSim 
	osgFX 
	osgAnimation 
	osgManipulator
	osgParticle)
    
if (WIN32)
    if (OPENSCENEGRAPH_FOUND)
        include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
    else()
        MESSAGE("=========== Need Set OSG_DIR environment=============")
        MESSAGE("=========== Need Set OSG_DIR environment=============")
        MESSAGE("=========== Need Set OSG_DIR environment=============")
    endif()
endif()

if(UNIX)
	find_library(log4Cpp_DEBUG_LIBRARIES liblog4cpp.so ENV log4Cpp_LIBRARY_DIR)
	find_library(log4Cpp_RELEASE_LIBRARIES liblog4cpp.so ENV log4Cpp_LIBRARY_DIR)
endif()


#添加子项目
add_subdirectory(src)
add_subdirectory(application)

