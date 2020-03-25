cmake_minimum_required(VERSION 3.3)

project(lunasvg VERSION 0.1.0 LANGUAGES CXX)

option(LUNA_SVG_ENABLE_CAIRO "Enable Cairo 2D Graphics"  ON)
option(BUILD_SHARED_LIBS "Builds shared libraries" ON)
option(LUNA_SVG_BUILD_EXAMPLES "Builds examples" ON)

add_library(lunasvg)

set_target_properties(lunasvg PROPERTIES VERSION 0.1.0 SONAME 0)

target_link_libraries(lunasvg cairo)

if (LUNA_SVG_ENABLE_CAIRO)
    add_definitions(-DLUNA_SVG_ENABLE_CAIRO)
    add_subdirectory(source/graphics/cairo)
endif ()

if (LUNA_SVG_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()

target_compile_options(lunasvg
PRIVATE
    -fPIC -fno-rtti -fno-exceptions -Wall
)

add_subdirectory(include)
add_subdirectory(source)

set(LUNA_SVG_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(LUNA_SVG_INCDIR ${CMAKE_INSTALL_PREFIX}/include/lunasvg)

install(FILES
    include/svgdocument.h
    include/svgelement.h
    include/svgelementiter.h
    DESTINATION ${LUNA_SVG_INCDIR}
)

install(TARGETS lunasvg
    LIBRARY     DESTINATION    ${LUNA_SVG_LIBDIR}
    ARCHIVE     DESTINATION    ${LUNA_SVG_LIBDIR}
    INCLUDES    DESTINATION    ${LUNA_SVG_INCDIR}
)
