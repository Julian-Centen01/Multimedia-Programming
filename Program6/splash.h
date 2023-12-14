#ifndef __SPLASH_H__
#define __SPLASH_H__

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "state.h"

class splash_state : public state {
public:
    splash_state(SDL_Renderer *rend);
    ~splash_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Rect button1;
    SDL_Rect button2;
};

#endif  /* __SPLASH_H__ */
