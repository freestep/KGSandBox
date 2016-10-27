set(OUT_NAME KGGraphs)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/KGGraphs)

SET(PROJECT_INCLUDE ${CMAKE_SOURCE_DIR}/include/KGGraphs)
SET(PROJECT_SRC ${CMAKE_SOURCE_DIR}/src/KGGraphs)

set(GRAPH_H_CPP 
	${PROJECT_INCLUDE}/Export.h
	${PROJECT_INCLUDE}/Graph.h
	${PROJECT_SRC}/Graph.cpp
	${PROJECT_INCLUDE}/Line.h
	${PROJECT_SRC}/Line.cpp
	${PROJECT_INCLUDE}/GraphsMgr.h
	${PROJECT_SRC}/GraphsMgr.cpp
)
  
if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
    	${OUT_NAME} SHARED 
    		${GRAPH_H_CPP}
			)
    ADD_DEFINITIONS(-DEARTH_LIBRARY)
else()
    add_library(
    	${OUT_NAME} STATIC 
    		${GRAPH_H_CPP}
			)
    ADD_DEFINITIONS(-DEARTH_LIBRARY_STATIC)
endif()
											
target_link_libraries(
    ${OUT_NAME} 
    ${OPENSCENEGRAPH_LIBRARIES} 
	KGUtils	
	KGShell 
    )

set(KG_HEADER
	${PROJECT_INCLUDE}/Export.h
	${PROJECT_INCLUDE}/Graph.h
	${PROJECT_INCLUDE}/GraphsMgr.h
)
INSTALL(TARGETS ${OUT_NAME}  DESTINATION lib)
INSTALL(TARGETS ${OUT_NAME}  DESTINATION bin)

INSTALL(FILES ${KG_HEADER} DESTINATION include/KGGraphs)

