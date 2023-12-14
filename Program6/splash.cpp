#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "splash.h"
#include "state.h"

splash_state::splash_state(SDL_Renderer *rend) : state(rend) {
    button1.x = w / 4;
    button1.y = h / 5;
    button1.w = w / 2;
    button1.h = h / 5;

    button2.x = w / 4;
    button2.y = (3 * h) / 5;
    button2.w = w / 2;
    button2.h = h / 5;
}

splash_state::~splash_state() {
}

bool splash_state::enter() {
    return true;
}

bool splash_state::leave() {
    return true;
}

bool splash_state::draw() {
    SDL_SetRenderDrawColor(rend, 0x12, 0x34, 0x56, 0xFF);
    SDL_RenderFillRect(rend, &button1);
    SDL_SetRenderDrawColor(rend, 0x65, 0x43, 0x21, 0xFF);
    SDL_RenderFillRect(rend, &button2);
    stringColor(rend , 20 , 20, "Press enter to go into game state", 0xff000000);

    return true;
}

bool splash_state::handle_event(const SDL_Event &e) {
    bool result = false;

    switch(e.type) {
    case SDL_KEYDOWN:
        switch(e.key.keysym.sym) {
        case SDLK_UP:
            std::cout << "up" << std::endl;
            result = true;
            break;
        case SDLK_RETURN:
            transition("game");
            result = true;
            break;
        default:  break;
        }
    default:  break;
    }

    return result;
}
