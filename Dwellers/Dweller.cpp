#include "Dweller.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>
#include <SDL2_image/SDL_image.h>

Dweller::Dweller(SDL_Renderer *renderer) {
    loadTextures(renderer);
    
    // Set the dweller to middle of screen:
    _x = (Game::WIDTH/2)-(size/2);
    _y = (Game::HEIGHT/2)-(size/2);
}

Dweller::~Dweller() {
    int elements = sizeof(textures)/sizeof(textures[0]);
    for(int i = 0; i < elements; i++) {
        SDL_DestroyTexture(textures[i]);
    }
}

void Dweller::loadTextures(SDL_Renderer *renderer) {
    
    // The part of the image we want to extract:
    SDL_Rect tilePartRect;
    tilePartRect.x = 48;
    tilePartRect.y = 0;
    tilePartRect.w = 16;
    tilePartRect.h = 16;
    
    for(int i = 0; i < 4; i++) {
        
        std::string fileName = std::to_string(i).append(".png");
        
        SDL_Surface *charactersSurface = IMG_Load(fileName.c_str());
        if(charactersSurface == NULL) {
            std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
        }
        textures[i] = SDL_CreateTextureFromSurface(renderer, charactersSurface);
        SDL_FreeSurface(charactersSurface);
    }
    
    // Reset the render target to the screen.
    SDL_SetRenderTarget(renderer, NULL);
}

void Dweller::pollEvents(SDL_Event &event) {
    
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    if(state[SDL_SCANCODE_UP]) {
        if(_y > 0) {
            _y -= stepIncrement;
            direction = UP;
        }
    }
    if(state[SDL_SCANCODE_DOWN]) {
        if(_y < (Game::HEIGHT-size)) {
            _y += stepIncrement;
            direction = DOWN;
        }
    }
    if(state[SDL_SCANCODE_LEFT]) {
        if(_x > 0) {
            _x -= stepIncrement;
            direction = LEFT;
        }
    }
    if(state[SDL_SCANCODE_RIGHT]) {
        if(_x < (Game::WIDTH-size)) {
            _x += stepIncrement;
            direction = RIGHT;
        }
    }
    
}

void Dweller::draw(SDL_Renderer *renderer) {
    
    SDL_Rect texture_rect;
    texture_rect.x = _x;
    texture_rect.y = _y;
    texture_rect.w = size;
    texture_rect.h = size;
    
    SDL_RenderCopy(renderer, textures[direction], NULL, &texture_rect);
}
