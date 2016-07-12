#include "client.h"
client::client(){
  screenW=640;
  screenH=480;

  IPaddress ip;
  
  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDLNet_Init();
  
  window = SDL_CreateWindow("mPong Client", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    screenW, screenH, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  SDLNet_ResolveHost(&ip,"localhost",9999);
  
  while(tcpsock == 0 && running){
    tcpsock=SDLNet_TCP_Open(&ip);
  }
  while(running){
    render();
    loop();
  }
}
void client::receive()
{
  int buffSize = 4;
  char buffer[buffSize];
  memset(buffer, 0, buffSize);
  SDLNet_TCP_Recv(tcpsock, buffer, buffSize);
  buffSize = 1;
  char buffer2[buffSize]; 
  memset(buffer2, 0, buffSize);
  SDLNet_TCP_Recv(tcpsock, buffer2, buffSize);
  char buffer3[buffer2[0]];
  buffSize = buffer2[0];
  memset(buffer3, 0, buffSize);
  SDLNet_TCP_Recv(tcpsock, buffer3, buffSize);
  if(string(buffer) == "POS1"){
    std::cout << "POS1 RECEIVED! SIZE: " << buffer2 << "VALUE! : " << buffer3 << std::endl;
  }
  else{
    std::cout << "Nope, too bad :(" << std::endl;
  }
}
void client::input(SDL_Event event){
    while (SDL_PollEvent(&event)) {
    if(event.type==SDL_QUIT){
      running=false;
    }
    else if(event.type==SDL_KEYDOWN){
      if(event.key.keysym.sym==SDLK_ESCAPE){
	running=false;
      }
    }
  }
}
void client::render(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}
void client::loop(){
  SDL_Event event;
  receive();
  input(event);
}