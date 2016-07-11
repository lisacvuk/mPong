#include "game.h"

int main(int argc, char **argv) {
  string empty = "";
  if(argc > 1){
    Game game(argv[1]);
  }
  else{
    Game game(empty);
  }
  return 0;
}