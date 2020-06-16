#include <iostream>

#include "osrf_testing_tools_cpp/memory_tools/memory_tools.hpp"
#include "osrf_testing_tools_cpp/scope_exit.hpp"
#include <dlfcn.h>

void my_malloc() {
  auto var = std::malloc(sizeof(int));
  std::free(var);
}

int main(int argc, char * argvs[]) {
  using namespace std;

  osrf_testing_tools_cpp::memory_tools::initialize();
  OSRF_TESTING_TOOLS_CPP_SCOPE_EXIT(
      { osrf_testing_tools_cpp::memory_tools::uninitialize(); });

  osrf_testing_tools_cpp::memory_tools::enable_monitoring();

  auto on_unexpected_memory =
      [](osrf_testing_tools_cpp::memory_tools::MemoryToolsService &service) {

        service.print_backtrace();
      };

  osrf_testing_tools_cpp::memory_tools::on_unexpected_calloc(
      on_unexpected_memory);
  osrf_testing_tools_cpp::memory_tools::on_unexpected_free(
      on_unexpected_memory);
  osrf_testing_tools_cpp::memory_tools::on_unexpected_malloc(
      on_unexpected_memory);
  osrf_testing_tools_cpp::memory_tools::on_unexpected_realloc(
      on_unexpected_memory);

  osrf_testing_tools_cpp::memory_tools::expect_no_malloc_begin();
  my_malloc();
  osrf_testing_tools_cpp::memory_tools::expect_no_malloc_end();
}
