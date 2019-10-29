
file(GLOB_RECURSE has_method_sources has_method.cpp main_catch.cpp ../common/has_method.hpp)

add_executable(has_method_test ${has_method_sources})
target_link_libraries(has_method_test castor_common)

add_test(NAME has_method_test COMMAND has_method_test)
