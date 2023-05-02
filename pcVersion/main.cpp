#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

// sample SDL2 code

/*
int main(int argc, char** argv){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        cout << "Error: Failed to open window\nSDL Error:" << SDL_GetError();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout << "Error: Failed to create renderer\nSDL Error:" << SDL_GetError();
        return 1;
    }

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}
*/

int main(int argc, char* argv[]){

    Game* game = Game::getInstance();

    game->run();

    Game::deleteInstance();

    return 0;
}