add_subdirectory(Sandbox)
SET_PROPERTY(TARGET KGSandbox PROPERTY FOLDER "Examples")
add_dependencies(KGSandbox KGShell KGUtils KGGraphs KGRender)