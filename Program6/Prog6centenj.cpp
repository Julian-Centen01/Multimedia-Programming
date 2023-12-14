#include <iostream>
#include <map>

#include <cstdlib>

#include <SDL.h>

#include "state.h"
#include "splash.h"
#include "game.h"
#include "prog4.h"
#include "prog1.h"
//include files for desired programs.h required here

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;

map <string, state *>states;
string current_state = "";
state *current_state_ptr = nullptr;

bool transition(string s) {
    bool result = true;

    if(current_state_ptr) {
        current_state_ptr->leave();
    }

    SDL_Event e;
    while(SDL_PollEvent(&e)); // flush the event queue

    if(states.contains(s)) {
        current_state_ptr = states[s];
        current_state = s;
        current_state_ptr->enter();
    }
    else {
        cerr << "OH NO!!! " << s << " is not a valid state." << endl;
        result = false;
        exit(EXIT_FAILURE);
    }

    return result;
}


int main(int argc, char *argv[]) {

    SDL_Window *w = nullptr;
    SDL_Surface *s = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    w = SDL_CreateWindow("Our app", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *rend = SDL_CreateRenderer(w, -1, 0);

    states["splash"] = new splash_state(rend);
    states["game"] = new game_state(rend);
    states["prog4"] = new prog4_state(rend);
    states["prog1"] = new prog1_state(rend);
    //states go here

    transition("splash");

    SDL_Event e;
    bool quit = false;
    while(!quit) {
        /*
         * Let event handling update variables needed for drawing
         */
        while(SDL_PollEvent(&e)) {
            if(!current_state_ptr || !current_state_ptr->handle_event(e)) {
                switch(e.type) {
                case SDL_QUIT:  quit = true;  break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:  quit = true;  break;
                    default:  break;
                    }
                default:  break;
                }
            }
        }

        /*
         * Draw everything that matters
         */
        SDL_SetRenderDrawColor(rend, 0xDD, 0xBB, 0xFF, 0xFF);
        SDL_RenderClear(rend);

        current_state_ptr->draw();

        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(w);

    SDL_Quit();

    return EXIT_SUCCESS;

}
