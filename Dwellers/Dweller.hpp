#ifndef Dweller_hpp
#define Dweller_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.hpp"

class Dweller {
    
public:
    Dweller(SDL_Renderer *renderer);
    ~Dweller();
    
    const int size = 32;
    enum directions {
        DOWN = 0,
        LEFT = 1,
        RIGHT = 2,
        UP = 3
    };
    int direction = DOWN;
    
    void loadTextures(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer);
    void pollEvents(SDL_Event &event);
    
private:
    int _w, _h;
    double _x, _y;
    double stepIncrement = 0.25;
    
    SDL_Texture *textures[4];
};

#endif
