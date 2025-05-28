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

set(BUILD_TESTS False)

set( SRC_FILES
		"src/cpu/cpu.h"
		"src/cpu/cpu.c"
		"src/vector/vector.h"
		"src/vector/vector.c"
)

if(NOT BUILD_TESTS)
	add_executable(${PROJECT_NAME} ${SRC_FILES} "src/main.c")
else()
	add_executable("${PROJECT_NAME}Tests" ${SRC_FILES} "src/test/test.c")
endif()