#include "./headers.h"


int main(int argc, char* argv[]) {
  dstr::AppState state(std::cout, std::cin);
  dstr::cli_start(argv, argc, state);
  return 0;
}
