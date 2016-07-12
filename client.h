#include "game.h"
class client{
public:
  client();
private:
  void loop();
  void input(SDL_Event event);
  void send();
  void receive();
  
  void render();
  
  TCPsocket tcpsock = 0;
  bool running = 1;
  
  int screenW, screenH;
  
  SDL_Window* window;
  SDL_Renderer* renderer;
};