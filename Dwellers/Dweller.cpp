#include "Dweller.hpp"
#include "Game.hpp"
#include <iostream>
#include <SDL2_image/SDL_image.h>

Dweller::Dweller(SDL_Renderer *renderer) {
    
    loadTexture(renderer);
    
}

Dweller::~Dweller() {
    SDL_DestroyTexture(texture);
}

void Dweller::loadTexture(SDL_Renderer *renderer) {
    
    SDL_Texture *charactersTexture = nullptr;
    SDL_Surface *charactersSurface = nullptr;
    int flags = IMG_INIT_PNG;
    
    if(IMG_Init(flags) != flags) {
        std::cout << "Image lib failed to load: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Loading texture " << "characters.png" << std::endl;
        charactersSurface = IMG_Load("characters.png");
        if(charactersSurface == NULL) {
            std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
        }
        charactersTexture = SDL_CreateTextureFromSurface(renderer, charactersSurface);
    }
    
    // Set the dweller to middle of screen:
    _x = (Game::WIDTH/2)-(size/2);
    _y = (Game::HEIGHT/2)-(size/2);
    
    // The part of the image we want to extract:
    SDL_Rect tilePartRect;
    tilePartRect.x = 48;
    tilePartRect.y = 0;
    tilePartRect.w = size;
    tilePartRect.h = size;
    
    // Create a texture that will be the cut-out of the original image.
    SDL_Texture* result = SDL_CreateTexture(renderer, NULL, SDL_TEXTUREACCESS_TARGET, size, size);
    SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);
    
    // Set the renderer to the resulting texture.
    SDL_SetRenderTarget(renderer, result);
    // Render the characters to the resulting target, with the correct rect.
    SDL_RenderCopy(renderer, charactersTexture, &tilePartRect, NULL);
    // Reset the render target to the screen.
    SDL_SetRenderTarget(renderer, NULL);
    // Set the dweller's texture.
    texture = result;
    
    SDL_FreeSurface(charactersSurface);
}

void Dweller::pollEvents(SDL_Event &event) {
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    std::cout << "Key: " << state << std::endl;
    if(state[SDL_SCANCODE_UP]) {
        if(_y > 0) {_y -= 1;}
    }
    if(state[SDL_SCANCODE_DOWN]) {
        if(_y < (Game::HEIGHT-size)) {_y += 1;}
    }
    if(state[SDL_SCANCODE_LEFT]) {
        if(_x > 0) {_x -= 1;}
    }
    if(state[SDL_SCANCODE_RIGHT]) {
        if(_x < (Game::WIDTH-size)) {_x += 1;}
    }
    
}

void Dweller::draw(SDL_Renderer *renderer) {
    
    SDL_Rect texture_rect;
    texture_rect.x = _x;
    texture_rect.y = _y;
    texture_rect.w = size;
    texture_rect.h = size;
    
    SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
}
