#include "./headers.h"


int main(char* argv, int argc){
  dstr::AppState state(std::cout, std::cin);
  dstr::cli_start(argv, argc, state);
  return 0;
}
