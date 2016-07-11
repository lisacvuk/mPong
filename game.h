#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

using std::string;

class Game{
public:
  Game(string parameters);
private:
  enum Net_Commands{
    one,
    two,
    three
  };
  void render();
  void serverLoop();
  void input(SDL_Event event);
  void serverInput(SDL_Event event);
  
  void server_sendCommand(std::string command);
  void server_sendCommand2(std::string command);
  
  void client_sendCommand(std::string command);
  
  std::string server_receiveCommand();
  std::string server_receiveCommand2();
  
  std::string client_receiveCommand();
  
  SDL_Rect p1;
  SDL_Rect p2;
  
  IPaddress ip;
  TCPsocket tcpsock = 0;
  
  TCPsocket tcp_newsock = NULL;
  TCPsocket tcp_newsock2 = NULL;
  
  int tempMovInt = 0;
  
  float p1x;
  float p2x;
  
  float serverPos1 = 0;
  float serverPos2 = 0;
  
  float timeStep;
  float lastTimeStep;
  
  bool isServer;
  bool running;
  SDL_Window* window;
  SDL_Renderer* renderer;
};