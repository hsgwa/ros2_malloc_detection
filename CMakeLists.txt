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

include(CTest) # creates BUILD_TESTING option to enable test

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  find_package(osrf_testing_tools_cpp REQUIRED)
  osrf_testing_tools_cpp_require_googletest(VERSION_GTE 1.8)


  get_target_property(memory_tools_available
    osrf_testing_tools_cpp::memory_tools LIBRARY_PRELOAD_ENVIRONMENT_IS_AVAILABLE)

  if(memory_tools_available)
    set(GOOGLE_TEST google_test)

    add_executable(${GOOGLE_TEST} src/add_gtest.cpp)
    target_link_libraries(${GOOGLE_TEST}
      gtest_main
      osrf_testing_tools_cpp::memory_tools
      )

    # ctestに追加する
    get_target_property(extra_env_vars
      osrf_testing_tools_cpp::memory_tools LIBRARY_PRELOAD_ENVIRONMENT_VARIABLE)
    osrf_testing_tools_cpp_add_test(google_test_tools
      COMMAND "$<TARGET_FILE:google_test>"
      ENV ${extra_env_vars}
      )
   endif()

  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
