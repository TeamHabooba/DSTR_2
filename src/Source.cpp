#include "./headers.h"


int main(char* argv, int argc){
  auto list = dstr::List<dstr::Resident>();
  auto arr = dstr::Array<dstr::Resident>();
  dstr::AppState state(std::cout, std::cin, arr, list);
  dstr::cli_start(argv, argc, state);
  return 0;
}
