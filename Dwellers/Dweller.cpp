#include "Dweller.hpp"
#include "Game.hpp"
#include <iostream>
#include <SDL2_image/SDL_image.h>

Dweller::Dweller(SDL_Renderer *renderer) {
    
    SDL_Texture *characters = loadTexture(renderer);
    
    // Set the dweller to middle of screen:
    _x = (800/2)-(32/2);
    _y = (600/2)-(32/2);
    
    // The part of the image we want to extract:
    SDL_Rect tilePartRect;
    tilePartRect.x = 48;
    tilePartRect.y = 0;
    tilePartRect.w = 16;
    tilePartRect.h = 16;
    
    // Create a texture that will be the cut-out of the original image.
    SDL_Texture* result = SDL_CreateTexture(renderer, NULL, SDL_TEXTUREACCESS_TARGET, 16, 16);
    // Set the renderer to the resulting texture.
    SDL_SetRenderTarget(renderer, result);
    // Render the characters to the resulting target, with the correct rect.
    SDL_RenderCopy(renderer, characters, &tilePartRect, NULL);
    // Reset the render target to the screen.
    SDL_SetRenderTarget(renderer, NULL);
    // Set the dweller's texture.
    texture = result;
}

SDL_Texture* Dweller::loadTexture(SDL_Renderer *renderer) {
    
    SDL_Texture *result = nullptr;
    int flags = IMG_INIT_PNG;
    
    if(IMG_Init(flags) != flags) {
        std::cout << "Image lib failed to load: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Loading texture " << "characters.png" << std::endl;
        SDL_Surface *textureSurface = IMG_Load("characters.png");
        if(textureSurface == NULL) {
            std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
        }
        result = SDL_CreateTextureFromSurface(renderer, textureSurface);
        SDL_FreeSurface(textureSurface);
    }
    
    return result;
}

void Dweller::pollEvents(SDL_Event &event) {
    
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    if(_x < (800-32)) {_x += 1;}
                    break;
                case SDLK_LEFT:
                    if(_x > 0) {_x -= 1;}
                    break;
                case SDLK_UP:
                    if(_y > 0) {_y -= 1;}
                    break;
                case SDLK_DOWN:
                    if(_y < (600-32)) {_y += 1;}
                    break;
                default:
                    break;
            }
        default:
            break;
    }
    
}

void Dweller::draw(SDL_Renderer *renderer) {
    
    SDL_Rect texture_rect;
    texture_rect.x = _x;
    texture_rect.y = _y;
    texture_rect.w = 32;
    texture_rect.h = 32;
    
    SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
}
