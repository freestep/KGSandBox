set(OUT_NAME KGUtils)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/KGUtils)

SET(KG_UTILS_INCLUDE ${CMAKE_SOURCE_DIR}/include/KGUtils)
SET(KG_UTILS_SRC ${CMAKE_SOURCE_DIR}/src/KGUtils)

set(GLOBAL_H_CPP
		${KG_UTILS_INCLUDE}/Common.h
		${KG_UTILS_SRC}/Common.cpp
		
		${KG_UTILS_INCLUDE}/Export.h

		${KG_UTILS_INCLUDE}/CoordConverter.h
		${KG_UTILS_SRC}/CoordConverter.cpp)
		

if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
	${OUT_NAME} SHARED 
	${GLOBAL_H_CPP} 
	)
    ADD_DEFINITIONS(-DFEUTILS_LIBRARY)
else()
    add_library(
	${OUT_NAME} STATIC 
	${GLOBAL_H_CPP} 
	)
    ADD_DEFINITIONS(-DFEUTILS_LIBRARY_STATIC)
endif()


target_link_libraries(
    ${OUT_NAME} 
    ${OPENSCENEGRAPH_LIBRARIES} 
    ${mplib}
 )
INSTALL(TARGETS ${OUT_NAME}  DESTINATION lib)
INSTALL(TARGETS ${OUT_NAME}  DESTINATION bin)

set(HEADER
		${KG_UTILS_INCLUDE}/Common.h
		${KG_UTILS_INCLUDE}/Export.h
		${KG_UTILS_INCLUDE}/CoordConverter.h	
)

INSTALL(FILES ${HEADER} DESTINATION include/KGUtils)