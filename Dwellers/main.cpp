#include <iostream>
#include "Game.hpp"
#include "Dweller.hpp"
#include "NetConnection.hpp"

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    game = new Game();
    game->init("Dweller",
               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
               Game::WIDTH, Game::HEIGHT);
    
    NetConnection *netConn = new NetConnection();
    netConn->init();
    
    if(game->running() && netConn->isActive()) {
        SDL_Renderer *renderer = game->getRenderer();
        Dweller *dweller = new Dweller(renderer);
        
        while(game->running()) {
            
            SDL_Event event;
            SDL_PollEvent(&event);
            game->handleEvents(event);
            dweller->pollEvents(event);
            
            
            
            SDL_RenderClear(renderer);
            game->draw(renderer);
            dweller->draw(renderer);
            SDL_RenderPresent(renderer);
        }
        
        game->clean();
        delete netConn;
        delete dweller;
    }
    
    delete game;
    return EXIT_SUCCESS;
}
