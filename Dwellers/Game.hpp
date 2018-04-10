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
    
    static const int WIDTH = 800;
    static const int HEIGHT = 600;
    
    void init(const char* title, int xpos, int ypos, int width, int height);
    void loadBackground();
    void handleEvents(SDL_Event &event);
    void draw(SDL_Renderer *renderer);
    void clean();
    
    SDL_Texture *grass;
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
