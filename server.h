#include "game.h"
class server{
public:
  server();
private:
  void loop();
  void input(SDL_Event event);
  void send(const char* name, const int size, const char* data, const int client);
  void receive();
  
  void initInput();
  
  TCPsocket tcpsock = 0;
  
  TCPsocket client1 = 0;
  TCPsocket client2 = 0;
  
  bool running;
};