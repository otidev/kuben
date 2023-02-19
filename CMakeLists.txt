cmake_minimum_required(VERSION 3.7)

project(Kuben)


# Windows specific

set(SDL2_DIR CACHE STRING "SDL2 source directory (in here you should find lib, include, bin)")
set(SDL2_TTF_DIR CACHE STRING "SDL2_TTF source directory (in here you should find lib, include, bin)")
set(SDL2_IMAGE_DIR CACHE STRING "SDL2_image source directory (in here you should find lib, include, bin)")

set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include/SDL2")
set(SDL2_LIBRARIES "${SDL2_DIR}/lib/libSDL2.dll.a;${SDL2_DIR}/lib/libSDL2main.a")
set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_DIR}/include/SDL2")
set(SDL2_TTF_LIBRARIES "${SDL2_TTF_DIR}/lib/libSDL2_ttf.dll.a")
set(SDL2_IMAGE_INCLUDE_DIRS "${SDL2_IMAGE_DIR}/include/SDL2")
set(SDL2_IMAGE_LIBRARIES "${SDL2_IMAGE_DIR}/lib/libSDL2_image.dll.a")

include_directories("${SDL2_INCLUDE_DIRS}" "${SDL2_TTF_INCLUDE_DIRS}" "${SDL2_IMAGE_INCLUDE_DIRS}" "src/include")

add_executable(
	Kuben
	src/Text.c
	src/UserInput.c
	src/Selection.c
	src/Resources.c
	src/Program.c
	src/Disk.c
	src/Sprite.c
	src/Window.c
	src/UI.c
)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
target_compile_options(Kuben PRIVATE -Wall -std=c99)
target_link_libraries(Kuben ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} -lwinmm -lws2_32 ${SDL2_TTF_LIBRARIES})

add_custom_command(TARGET Kuben POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_TTF_DIR}/bin/SDL2_ttf.dll"
	$<TARGET_FILE_DIR:Kuben>)

add_custom_command(TARGET Kuben POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_DIR}/bin/SDL2.dll"
	$<TARGET_FILE_DIR:Kuben>)

add_custom_command(TARGET Kuben POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_IMAGE_DIR}/bin/SDL2_image.dll"
	$<TARGET_FILE_DIR:Kuben>)
