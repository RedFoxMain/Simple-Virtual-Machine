# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SimpleVirtualMachine")

set( SRC_FILES
	"src/main.c"
	"src/cpu/cpu.h"
	"src/cpu/cpu.c"
	#"src/display/display.h"
	#"src/display/display.c"

	"src/vector/vector.h"
	"src/vector/vector.c"
)

set(SDL_DIR "${CMAKE_SOURCE_DIR}/external/SDL/cmake")
include_directories("${CMAKE_SOURCE_DIR}/external/SDL/include")

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Automatically adds SDL3.dll to exe folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/external/SDL/lib/x64/SDL3.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Link SDL
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/external/SDL/lib/x64/SDL3.lib")