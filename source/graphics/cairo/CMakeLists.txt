target_sources(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/surfaceimpl.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/graphicscontextimpl.cpp"
)

target_include_directories(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
)
