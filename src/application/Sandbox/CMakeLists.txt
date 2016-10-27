SET(OUT_NAME KGSandbox)
include_directories(${CMAKE_SOURCE_DIR}/application/Sandbox/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
SET(FREE_VIEWER_INCLUDE ${CMAKE_SOURCE_DIR}/application/Sandbox/include)
SET(FREE_VIEWER_SRC ${CMAKE_SOURCE_DIR}/application/Sandbox/src)

#设置调试库的后缀
set(CMAKE_DEBUG_POSTFIX "d")

###########################################################################
#                                                                         #
#                       VIEWER_H_CPP	                          #
#                                                                         #
###########################################################################
set(VIEWER_H_CPP
	${FREE_VIEWER_SRC}/main.cpp
#	${FREE_VIEWER_SRC}/DepthBasics.cpp
#	${FREE_VIEWER_INCLUDE}/DepthBasics.h
	)

add_executable(
	${OUT_NAME} 
    ${VIEWER_H_CPP}
  )
	target_link_libraries(
		${OUT_NAME}
        ${QT_LIBRARIES}
        KGUtils
		KGShell
		KGGraphs
		KGRender
	)  

	SET_TARGET_PROPERTIES(${OUT_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${OUT_NAME}${CMAKE_DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${OUT_NAME} PROPERTIES RELEASE_OUTPUT_NAME "${OUT_NAME}${CMAKE_RELEASE_POSTFIX}")
		       
	INSTALL(TARGETS ${OUT_NAME}  DESTINATION bin)
