//#include "./headers.h"
#include <common/memory/pool_allocator.h>
#include <cli/app_state.h>
#include <cli/cli.h>

int main(char* argv, int argc){
  dstr::AppState state(std::cout, std::cin);
  dstr::cli_start(argv, argc, state);
  return 0;
}
