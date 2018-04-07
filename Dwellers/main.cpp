#include <iostream>
#include "Game.hpp"
#include "Dweller.hpp"

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    game = new Game();
    game->init("Dweller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    SDL_Renderer *renderer = game->getRenderer();
    Dweller *dweller = new Dweller(renderer);
    
    while(game->running()) {
        
        SDL_Event event;
        SDL_PollEvent(&event);
        game->handleEvents(event);
        dweller->pollEvents(event);
        
        SDL_RenderClear(renderer);
        dweller->draw(renderer);
        SDL_RenderPresent(renderer);
    }
    
    game->clean();
    
    return EXIT_SUCCESS;
    
}
