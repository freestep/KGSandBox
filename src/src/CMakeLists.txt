add_subdirectory(KGUtils)
SET_PROPERTY(TARGET KGUtils PROPERTY FOLDER "KGCore")

add_subdirectory(KGShell)
add_dependencies(KGShell KGUtils)
SET_PROPERTY(TARGET KGShell PROPERTY FOLDER "KGCore")

add_subdirectory(KGGraphs)
add_dependencies(KGGraphs KGUtils KGShell)
SET_PROPERTY(TARGET KGGraphs PROPERTY FOLDER "KGCore")

add_subdirectory(KGRender)
add_dependencies(KGRender KGUtils KGShell KGGraphs )
SET_PROPERTY(TARGET KGRender PROPERTY FOLDER "KGRender")
