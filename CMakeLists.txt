cmake_minimum_required(VERSION 2.8)
project(itoa)
include(CheckIncludeFileCXX)
check_include_file_cxx(any HAS_ANY)
if (HAS_ANY)
    set(CXX_STANDARD  17)
else ()
    set(CXX_STANDARD  11)
endif ()
message(STATUS "Build STANDARD: c++${CXX_STANDARD}")
if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "selected to ${CMAKE_BUILD_TYPE}")
if (MSVC)
	add_compile_options(/O2 /GA /Ob2 /utf-8)
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fexec-charset=utf-8 -finput-charset=utf-8")
endif ()
#win: cmake --build ./build -- /p:Configuration=Release
#or: cmake --build ./build --config Release
include_directories(./)
if(WIN32)
  add_executable(test test.cc i2a.c)
  add_custom_command(TARGET test
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/test.exe ${PROJECT_SOURCE_DIR}/test.exe
  )
else()
  add_executable(test test.cc i2a.c)
  add_custom_command(TARGET test
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/test ${PROJECT_SOURCE_DIR}/test
  )
endif()