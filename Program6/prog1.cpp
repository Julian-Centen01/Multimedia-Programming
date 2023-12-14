
#include <iostream>
#include <ctime>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "prog1.h"
#include "state.h"

using namespace std;

prog1_state::prog1_state(SDL_Renderer *rend) : state(rend) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
    srand(time(nullptr));

    screen.x = 0;
    screen.y = 0;
    screen.w = w;
    screen.h = h;

    
    R = 0;
    G = 0;
    B = 0;
    randrgb = 0;
    coinflip = 0;
}

prog1_state::~prog1_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
}

bool prog1_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool prog1_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool prog1_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    states["game"]->draw();
    SDL_SetRenderDrawColor(rend, R , G , B , 0xFF);
    SDL_RenderFillRect(rend, &screen);
    randrgb = rand() % 3;
    coinflip = (rand() % 2) - 1;
    if(randrgb == 0){
        if((coinflip == 0 && R == 255) || (coinflip == -1 && R == 0)){

        }
        else{
            R += coinflip;
            if (coinflip == 0)
            R++;
        }
    }
    else if(randrgb == 1){
        if((coinflip == 0 && G == 255) || (coinflip == -1 && G == 0)){

        }
        else{
            G += coinflip;
            if (coinflip == 0)
            G++;
        }
    }
    else{
        if((coinflip == 0 && G == 255) || (coinflip == -1 && G == 0)){

        }
        else{
            G += coinflip;
            if (coinflip == 0)
            G++;
        }
    }

    stringColor(rend , 20 , 20 , "Press enter to return to menu" , 0xffffffff);

    return true;
}

bool prog1_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                std::cout << "colors" << std::endl;
                result = true;
                break;
            case SDLK_RETURN:
                transition("game");
                result = true;
            break;
            
            default:
                break;
            }
        break;

    default:  break;
    }

    return result;
}
