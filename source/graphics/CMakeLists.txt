target_sources(lunasvg 
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/rgb.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/paint.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/surface.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/graphicscontext.cpp"
)

target_include_directories(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
)
