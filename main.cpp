#include "server.h"
#include "client.h"

int main(int argc, char **argv) {
  if(argc > 1){
    if(string(argv[1]) == "--server"){
      server game;
    }
    std::cout << argv[1] << std::endl;
  }
  else{
    client game;
  }
  return 0;
}