cmake_minimum_required(VERSION 3.0)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Box2D REQUIRED)

add_subdirectory(external/SANDAL2)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -g ${CMAKE_CXX_FLAGS}")
endif()

include_directories(src external/SANDAL2/headers)

file(GLOB_RECURSE ${PROJECT_NAME}_sources src/${PROJECT_NAME}/*.cpp)
add_library( ${PROJECT_NAME} ${${PROJECT_NAME}_sources})
target_link_libraries(${PROJECT_NAME} SANDAL2 ${Box2D_LIBRARIES} fmod)

file(GLOB_RECURSE example_sources src/example/*.cpp)
add_executable(example ${example_sources})
target_link_libraries(example castor-engine)

file(GLOB_RECURSE testing_sources src/testing/*.cpp)

foreach(test_source ${testing_sources})
  get_filename_component(test_exec ${test_source} NAME_WE)
  add_executable(${test_exec} ${test_source})
endforeach(test_source ${testing_sources})
