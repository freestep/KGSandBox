set(OUT_NAME KGShell)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/KGShell)

SET(PROJECT_INCLUDE ${CMAKE_SOURCE_DIR}/include/KGShell)
SET(PROJECT_SRC ${CMAKE_SOURCE_DIR}/src/KGShell)

set(H_CPP 
	${PROJECT_INCLUDE}/Export.h
#	${PROJECT_INCLUDE}/SystemService.h
	${PROJECT_INCLUDE}/CommandMgr.h
	${PROJECT_INCLUDE}/Exception.h
#	${PROJECT_INCLUDE}/Listener.h
	${PROJECT_INCLUDE}/Props.h

#	${PROJECT_SRC}/SystemService.cpp
	${PROJECT_SRC}/CommandMgr.cpp
	${PROJECT_SRC}/Exception.cpp
	#${PROJECT_SRC}/Listener.cpp
	${PROJECT_SRC}/Props.cpp
)
           
if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
    	${OUT_NAME} SHARED 
    		${H_CPP}
			)
    ADD_DEFINITIONS(-DSHELL_LIBRARY)
else()
    add_library(
    	${OUT_NAME} STATIC 
    		${H_CPP}
			)
    ADD_DEFINITIONS(-DSHELL_LIBRARY_STATIC)
endif()
											
target_link_libraries(
    ${OUT_NAME} 
	KGUtils
    )

set(HEADER
	${PROJECT_INCLUDE}/Export.h
#	${PROJECT_INCLUDE}/SystemService.h
	${PROJECT_INCLUDE}/CommandMgr.h
	${PROJECT_INCLUDE}/Exception.h
	${PROJECT_INCLUDE}/Listener.h
	${PROJECT_INCLUDE}/Props.h
)

INSTALL(TARGETS ${OUT_NAME}  DESTINATION lib)
INSTALL(TARGETS ${OUT_NAME}  DESTINATION bin)

INSTALL(FILES ${HEADER} DESTINATION include/KGShell)

