#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "state.h"

class game_state : public state {
public:
    game_state(SDL_Renderer *rend);
    ~game_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Rect square;
};

#endif  /* __GAME_H__ */
