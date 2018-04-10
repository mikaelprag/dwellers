#include <iostream>
#include "Game.hpp"

Game::Game(){}
Game::~Game(){
    SDL_DestroyTexture(grass);
}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized." << std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, NULL);
        if(window) {
            std::cout << "Window Created" << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0);
            std::cout << "Renderer Created" << std::endl;
        }
        
        if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            std::cout << "Image lib failed to load: " << SDL_GetError() << std::endl;
        }
        
        loadBackground();
        
        isRunning = true;
    } else {
        isRunning = false;
    }
    
}

void Game::loadBackground() {
    // Load the grass.
    
    SDL_Texture *environmentTexture = nullptr;
    SDL_Surface *environmentSurface = nullptr;
    
    environmentSurface = IMG_Load("tiles.png");
    if(environmentSurface == NULL) {
        std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
    }
    environmentTexture = SDL_CreateTextureFromSurface(renderer, environmentSurface);
    
    // The part of the image we want to extract:
    SDL_Rect tilePartRect;
    tilePartRect.x = 0;
    tilePartRect.y = 128;
    tilePartRect.w = 16;
    tilePartRect.h = 16;
    
    // Create a texture that will be the cut-out of the original image.
    SDL_Texture* result = SDL_CreateTexture(renderer, NULL, SDL_TEXTUREACCESS_TARGET, 16, 16);
    SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);
    
    // Set the renderer to the resulting texture.
    SDL_SetRenderTarget(renderer, result);
    // Render the characters to the resulting target, with the correct rect.
    SDL_RenderCopy(renderer, environmentTexture, &tilePartRect, NULL);
    // Reset the render target to the screen.
    SDL_SetRenderTarget(renderer, NULL);
    // Set the dweller's texture.
    grass = result;
    
    SDL_FreeSurface(environmentSurface);
    SDL_DestroyTexture(environmentTexture);
}

SDL_Renderer *Game::getRenderer() {
    return renderer;
}

void Game::handleEvents(SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::draw(SDL_Renderer *renderer) {
    
    SDL_Rect texture_rect;
    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = 800;
    texture_rect.h = 600;
    
    SDL_RenderCopy(renderer, grass, NULL, &texture_rect);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "SDL Cleaned." << std::endl;
}
