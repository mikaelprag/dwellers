#ifndef Dweller_hpp
#define Dweller_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.hpp"

class Dweller {
    
public:
    Dweller(SDL_Renderer *renderer);
    ~Dweller();
    
    const int size = 16;
    
    void loadTexture(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer);
    void pollEvents(SDL_Event &event);
    
private:
    int _w, _h;
    int _x, _y;
    
    SDL_Texture *texture;
};

#endif /* Dweller_hpp */
