#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "game.h"
#include "state.h"

game_state::game_state(SDL_Renderer *rend) : state(rend) {
    square.x = w / 3;
    square.y = h / 3;
    square.w = w / 3;
    square.h = h / 3;
}

game_state::~game_state() {
}

bool game_state::enter() {
    return true;
}

bool game_state::leave() {
    return true;
}

bool game_state::draw() {
    states["splash"]->draw();
    SDL_SetRenderDrawColor(rend, 0x55, 0x55, 0x55, 0x88);
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rend, nullptr);
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(rend, 0xFD, 0xCA, 0x86, 0xFF);
    SDL_RenderFillRect(rend, &square);
    stringColor(rend , 20 , 30 , "Press b to enter ball game" , 0xff000000);
    stringColor(rend , 20 , 40 , "Press c to enter color screen", 0xff000000);

    return true;
}

bool game_state::handle_event(const SDL_Event &e) {
    bool result = false;

    switch(e.type) {
    case SDL_KEYDOWN:
        switch(e.key.keysym.sym) {
        case SDLK_UP:
            std::cout << "game" << std::endl;
            result = true;
            break;
        case SDLK_s:
            transition("splash");
            result = true;
            break;
        case SDLK_b:
            transition("prog4");
            result = true;
            break;
        case SDLK_c:
            transition("prog1");
            result = true;
            break;
        default:  break;
        }
    default:  break;
    }

    return result;
}
