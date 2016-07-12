#include "server.h"

server::server(){
  std::cout << "Initializing server application." << std::endl;
  SDL_Init(SDL_INIT_TIMER|SDL_INIT_EVENTS);
  
  SDLNet_Init();
  
  IPaddress ip;
  
  running=true;
  
  SDLNet_ResolveHost(&ip,NULL,9999);
  while(tcpsock == 0 && running){
    tcpsock=SDLNet_TCP_Open(&ip);
    initInput();
  }
  std::cout << "Waiting for client 1..." << std::endl;
  while(client1 == NULL && running){
    client1=SDLNet_TCP_Accept(tcpsock);
    initInput();
  }
  std::cout << "Client 1 connected!" << std::endl;
  std::cout << "Waiting for client 2..." << std::endl;
  while(client2 == NULL && running){
    client2=SDLNet_TCP_Accept(tcpsock);
    initInput();
  }
  std::cout << "Client 2 connected!" << std::endl;
  if(client1 == NULL || client2 == NULL){
    running=false;
    std::cout << SDLNet_GetError() << std::endl;
  }
  const char name[5] = "POS1";
  const int size(2);
  char data[size+1] = "TS";
  send(name, size, data, 1);
  while(running){
    loop();
  }
}
void server::send(const char* name, const int size, const char* data, const int client){
  vector<char> temp;
  for(int i=0; i < 4; i++){
    temp.push_back(name[i]);
  }
  temp.push_back(size);
  for(int i=0; i < size; i++){
    temp.push_back(data[i]);
  }
  
  const char* charPtr = temp.data();
  std::cout << temp.data() << std::endl;
  void* messageData =  const_cast< char* > ( charPtr );
  int messageSize = temp.size();
  int sent = -1;
  if(client == 1){
    sent = SDLNet_TCP_Send( client1,  messageData,  messageSize);
  }
  else{
    sent = SDLNet_TCP_Send( client2,  messageData,  messageSize);
  }
  if(sent < 0){
    std::cout << SDLNet_GetError() << std::endl;
    running = false;
  }
}
void server::initInput(){
  SDL_Event event;
  input(event);
}
void server::input(SDL_Event event){
  while (SDL_PollEvent(&event)) {
    if(event.type==SDL_QUIT){
      running=false;
    }
    else if(event.type==SDL_KEYDOWN){
      if(event.key.keysym.sym==SDLK_ESCAPE){
	running=false;
      }
      else if(event.key.keysym.sym==SDLK_q){
	running=false;
      }
    }
  }
}
void server::loop(){
  SDL_Event event;
  input(event);
}