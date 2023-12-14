
#ifndef __PROG4_H__
#define __PROG4_H__

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>

#include "state.h"

using namespace std;

class prog4_state : public state {
public:
    prog4_state(SDL_Renderer *rend);
    ~prog4_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    //rectangles, textures, and other variables go here
    SDL_Surface *ball_s;
    SDL_Surface *stand_s;
    SDL_Surface *run_s;
    SDL_Rect stand_h[7];
    SDL_Rect run_h[7][2];
    SDL_Rect gTrack;
    SDL_Texture *run;
    SDL_Texture *stand;
    SDL_Texture *tball;
    int FCNT;
    int BW , BH , SW , SH , RW , RH;
    int frame;
    float bx;
    float by;
    float vy;
    float vx;
    bool mouseup;
    int score;
    int mx;
    int my;
    int centerBallx , centerBally;
    int centerPlayerx , centerPlayery;
    int ballFromPlayerx, ballFromPlayery;

};

#endif  /* __PROG4_H__ */
