add_executable(example1 "example1.cpp")

target_link_libraries(example1 lunasvg)

target_include_directories(example1
PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/"
)
