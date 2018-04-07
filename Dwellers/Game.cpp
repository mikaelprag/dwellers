#include <iostream>
#include "Game.hpp"

Game::Game(){}
Game::~Game(){}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized." << std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) {
            std::cout << "Window created." << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            std::cout << "Renderer created." << std::endl;
        }
        
        isRunning = true;
    } else {
        isRunning = false;
    }
}

SDL_Renderer *Game::getRenderer() {
    return renderer;
}

void Game::handleEvents(SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void Game::update() {
    
}

void Game::render() {
    
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}
