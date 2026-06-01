#include "./headers.h"


int main(char* argv, int argc){

  {
    using namespace dstr;
    auto a = Array<Node<string, int>>(10);
    for (usize i = 0; i < a.capacity(); i++) {
      a.push_back(Node<string, int>());
    }
  }

  dstr::AppState state(std::cout, std::cin);
  dstr::cli_start(argv, argc, state);
  return 0;
}
