#ifndef NetConnection_hpp
#define NetConnection_hpp

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>

class NetConnection {
    
public:
    NetConnection();
    ~NetConnection();
    
    void init();
    
    bool isActive() { return _active; }
    
private:
    bool _active;
};

#endif
