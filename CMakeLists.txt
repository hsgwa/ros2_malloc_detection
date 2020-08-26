cmake_minimum_required(VERSION 3.5)
project(gtest_sample)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(osrf_testing_tools_cpp REQUIRED)

add_compile_options(-O0 -rdynamic)

set (CMAKE_CXX_FLAGS "-rdynamic")

set(MALLOC_TEST malloc_test)
add_executable(${MALLOC_TEST} src/main.cpp)
target_link_libraries(${MALLOC_TEST}
  osrf_testing_tools_cpp::memory_tools
  )

include(CTest) # creates BUILD_TESTING option to enable test

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
