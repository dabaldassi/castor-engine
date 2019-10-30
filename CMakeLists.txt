cmake_minimum_required(VERSION 3.0)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

option(INCLUDE_TESTS off)
option(INCLUDE_EXAMPLES off)

# find_package(Box2D REQUIRED)

add_subdirectory(external/SANDAL2)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -O3")
endif()

include_directories(src src/castor-engine external/SANDAL2/headers)

file(GLOB_RECURSE common_sources src/common/*.cpp)
file(GLOB_RECURSE common_headers src/common/*.hpp)
message(STATUS "${common_sources} ${common_headers}")
add_library(castor_common ${common_sources} ${common_headers})
set_target_properties(castor_common PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_sources src/castor-engine/*.cpp)
add_library(castor-engine ${${PROJECT_NAME}_sources})
target_link_libraries(castor-engine
  SANDAL2
  castor_common
  )

if(INCLUDE_EXAMPLES)

file(GLOB_RECURSE example_sources src/example/*.cpp)
add_executable(example ${example_sources})
target_link_libraries(example castor-engine)

endif()

if(INCLUDE_TESTS)

  include(CTest)
  add_subdirectory(src/testing)

endif()
