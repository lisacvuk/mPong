#include "game.h"

Game::Game(string parameters)
{
  isServer = 0;
  if(parameters == ""){
    std::cout << parameters << std::endl;
  }
  else if(parameters == "--server"){
    std::cout << "Server Mode." << std::endl;
    isServer = 1;
  }
  int screenW, screenH;
  screenW = 640;
  screenH = 480;
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    running = true;
  } else {
    running = false;
    std::cout << "ERROR: Unable to intialize SDL. SDL_GetError() returns " <<
      SDL_GetError() << std::endl;
  }
  SDLNet_Init();
if (running && !isServer) {
    window =
      SDL_CreateWindow("mPong", SDL_WINDOWPOS_UNDEFINED,
		      SDL_WINDOWPOS_UNDEFINED, screenW, screenH,
		      SDL_WINDOW_SHOWN);
    if (!window) {
      running = false;
      std::cout <<
	"ERROR: Unable to intialize the main window. SDL_GetError() returns "
	<< SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      running = false;
      std::cout <<
	"ERROR: Unable to intialize the main renderer. SDL_GetError() returns "
	<< SDL_GetError() << std::endl;
    }
  }
if(isServer){
  SDLNet_ResolveHost(&ip,NULL,9999);
  while(tcpsock == 0 && running){
    tcpsock=SDLNet_TCP_Open(&ip);
    /*SDL_Event event;
    input(event);*/
  }
  while(tcp_newsock == NULL && running){
    tcp_newsock=SDLNet_TCP_Accept(tcpsock);
    /*SDL_Event event;
    input(event);*/
  }
  while(tcp_newsock2 == NULL && running){
    tcp_newsock2=SDLNet_TCP_Accept(tcpsock);
    /*SDL_Event event;
    input(event);*/
  }

  if(tcp_newsock == NULL || tcp_newsock2 == NULL){
    running=false;
    std::cout << "Error! " << SDLNet_GetError() << std::endl;
  }
}
else{
  SDLNet_ResolveHost(&ip,"localhost",9999);
  while(tcpsock == 0 && running){
    tcpsock=SDLNet_TCP_Open(&ip);
    /*SDL_Event event;
    SDL_Delay(500);
    input(event);*/
  }
  /*client_sendCommand(screenH);
  client_sendCommand(screenW);*/
}
  p1x = 0;
  p2x = 0;
  p1.w = screenW / 8;
  p1.h = screenH / 20;
  p1.x = screenW / 2 - (p1.w / 2);
  p1.y = 0;
  while (running && !isServer) {
    render();
  }
  while (running && isServer){
    serverLoop();
  }
}
void Game::client_sendCommand(std::string command){
  const char* charPtr = command.c_str();
  void* messageData =  const_cast< char* > ( charPtr );
  int messageSize = command.length();
  int sent = -1;
  sent = SDLNet_TCP_Send( tcpsock,  messageData,  messageSize);
  if(sent < 0){
    std::cout << SDLNet_GetError() << std::endl;
    running = false;
  }
}
void Game::server_sendCommand(std::string command){
  const char* charPtr = command.c_str();
  void* messageData =  const_cast< char* > ( charPtr );
  int messageSize = command.length();
  int sent = -1;
  sent = SDLNet_TCP_Send( tcp_newsock,  messageData,  messageSize);
  if(sent < 0){
    std::cout << SDLNet_GetError() << std::endl;
    running = false;
  }
}
void Game::server_sendCommand2(std::string command){
  const char* charPtr = command.c_str();
  void* messageData =  const_cast< char* > ( charPtr );
  int messageSize = command.length();
  int sent = -1;
  sent = SDLNet_TCP_Send( tcp_newsock2,  messageData,  messageSize);
  if(sent < 0){
    std::cout << SDLNet_GetError() << std::endl;
    running = false;
  }
}
std::string Game::client_receiveCommand(){
  int bufferSize = 3;
  char buffer[bufferSize];
  memset(buffer, 0, bufferSize);
  int byteCount = 0;
  byteCount = SDLNet_TCP_Recv(tcpsock, buffer, bufferSize);
  std::string temp;
  temp = buffer;
  return temp;
}
std::string Game::server_receiveCommand(){
  int bufferSize = 5;
  char buffer[bufferSize];
  memset(buffer, 0, bufferSize);
  int byteCount = 0;
  if(isServer){
    byteCount = SDLNet_TCP_Recv(tcp_newsock, buffer, bufferSize);
  }
  std::string temp;
  temp = buffer;
  return temp;
}
std::string Game::server_receiveCommand2(){
  int bufferSize = 5;
  char buffer[bufferSize];
  memset(buffer, 0, bufferSize);
  int byteCount = 0;
  if(isServer){
    byteCount = SDLNet_TCP_Recv(tcp_newsock2, buffer, bufferSize);
  }
  std::string temp;
  temp = buffer;
  return temp;
}
void Game::input(SDL_Event event)
{
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) {
	running = false; 
      }
      if (event.key.keysym.sym == SDLK_LEFT) {
	std::cout << "Left!" << std::endl;
      }
    } else if (event.type == SDL_MOUSEMOTION) {
	/*while (event.motion.x - p1.x > 0) {
	}*/
	/*while (event.motion.x - p1.x < 0) {
	  sendCommand("RGHT");*/
	}
      }
  }
void Game::serverInput(SDL_Event event)
{
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) {
	running = false; 
      }
    }
  }
}
void Game::render()
{
  p1.x = p1x;
  p2.x = p2x;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &p1);
  SDL_Event event;
  input(event);
  SDL_RenderPresent(renderer);
}
void Game::serverLoop(){
  SDL_Event event;
  serverInput(event);
}