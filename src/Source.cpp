//#include "./headers.h"
#include "./common/memory/pool_allocator.h"

int main(char* argv, int argc){
  //dstr::AppState state(std::cout, std::cin);
  //dstr::cli_start(argv, argc, state);
  using namespace dstr;
  pool_t pool;
  bool res = pool_init(&pool, 1024 * 256, 1024);
  u8* mem = reinterpret_cast<u8*>(pool_aquire(&pool));
  return 0;
}
