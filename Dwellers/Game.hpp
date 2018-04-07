#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "Dweller.hpp"

class Game {
  
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents(SDL_Event &event);
    void update();
    void render();
    void clean();
    
    SDL_Renderer *getRenderer();
    
    bool running() { return isRunning; }
    
    enum textureType {
        CHARACTERS,
        TILES,
        THINGS
    };
    
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textures[3];
};


#endif /* Game_hpp */
