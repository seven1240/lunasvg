target_sources(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/cssproperty.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgcolor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgenumeration.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svglength.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svglengthlist.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgnumber.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgnumberlist.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgpath.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgpoint.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgpointlist.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgpreserveaspectratio.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgproperty.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgpropertyutils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgrect.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgstring.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgstringlist.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgtransform.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/svgtransformlist.cpp"
)

target_include_directories(lunasvg
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
)
