#include "NetConnection.hpp"
#include <iostream>

NetConnection::NetConnection() {
    _active = false;
}

NetConnection::~NetConnection() {
    SDLNet_Quit();
}

void NetConnection::init() {
    if(SDLNet_Init() < 0) {
        std::cout << "SDL Net init failed: " << SDLNet_GetError() << std::endl;
        return;
    }
    
    IPaddress ip;
    SDLNet_ResolveHost(&ip, "127.0.0.1", 6000);
    TCPsocket client = SDLNet_TCP_Open(&ip);
    
    if(client) {
        char text[100];
        SDLNet_TCP_Recv(client, text, 100);
        std::cout << "Response: " << text << std::endl;
    }
    
    SDLNet_TCP_Close(client);
    
    _active = true;
}
