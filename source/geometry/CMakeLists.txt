target_sources(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/affinetransform.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/flattenpathiterator.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/path.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/pathutils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/pathiterator.cpp"
)

target_include_directories(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
)
