set(OUT_NAME KGRender)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/KGRender)

SET(PROJECT_INCLUDE ${CMAKE_SOURCE_DIR}/include/KGRender)
SET(PROJECT_SRC ${CMAKE_SOURCE_DIR}/src/KGRender)

set(ALL_H_CPP
	${PROJECT_INCLUDE}/Export.h
)

set(RENDER_H_CPP
	${PROJECT_INCLUDE}/KGSurfaceRenderer.h
	${PROJECT_SRC}/KGSurfaceRenderer.cpp
)
SOURCE_GROUP( renderer FILES ${RENDER_H_CPP})

if(${BUILD_SHARED_LIBS} STREQUAL "On")
	add_library(
		${OUT_NAME} SHARED
		${ALL_H_CPP}
		${RENDER_H_CPP}
	)
	ADD_DEFINITIONS(-DRENDER_LIBRARY)
else()
	add_library(
	${OUT_NAME} STATIC
	${ALL_H_CPP}
	${RENDER_H_CPP}
	)
	ADD_DEFINITIONS(-DRENDER_LIBRARY_STATIC)
endif()

target_link_libraries(
	${OUT_NAME}
	KGUtils
	KGShell
	KGGraphs
)

set(KG_HEADER
	${PROJECT_INCLUDE}/Export.h
	${PROJECT_INCLUDE}/KGRenderer.h
)

INSTALL(TARGETS ${OUT_NAME} DESTINATION lib)
INSTALL(TARGETS ${OUT_NAME} DESTINATION bin)
INSTALL(TARGETS ${OUT_NAME} DESTINATION include/KGRender)