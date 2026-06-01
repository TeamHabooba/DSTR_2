#include "./headers.h"


int main(char* argv, int argc){

  {
    using namespace dstr;
    auto a = Array<Node<string, int>>(10);
    std::ostringstream oss;
    for (usize i = 0; i < a.capacity(); i++) {
      oss << i;
      a.push_back(Node<string, int>(oss.str()));
      oss.clear();
    }
    
    auto b = a;
    auto n = b[4];
    auto n2 = std::move(n);
  }

  dstr::AppState state(std::cout, std::cin);
  dstr::cli_start(argv, argc, state);
  return 0;
}
