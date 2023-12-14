
#ifndef __PROG1_H__
#define __PROG1_H__

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "state.h"

using namespace std;

class prog1_state : public state {
public:
    prog1_state(SDL_Renderer *rend);
    ~prog1_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Rect screen;
    int randrgb;
    int coinflip;
    Uint8 R;
    Uint8 G;
    Uint8 B;
};

#endif  /* __PROG1_H__ */
