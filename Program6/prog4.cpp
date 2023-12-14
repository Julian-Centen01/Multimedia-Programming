
#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>

#include "prog4.h"
#include "state.h"

using namespace std;



prog4_state::prog4_state(SDL_Renderer *rend) : state(rend) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
    FCNT = 7;
    FPSmanager fps;
    SDL_initFramerate(&fps);

    ball_s = SDL_LoadBMP("ball.bmp");
    BW = ball_s->w;
    BH = ball_s->h;

    stand_s = SDL_LoadBMP("standing.bmp");
    SW = stand_s->w / FCNT; // Standing sprite Width for one frame
    SH = stand_s->h; // Standing sprite Height for one frame

    run_s = SDL_LoadBMP("running.bmp");
    RW = run_s->w / FCNT;
    RH = run_s->h / 2;

    run = SDL_CreateTextureFromSurface(rend, run_s);
    stand = SDL_CreateTextureFromSurface(rend, stand_s);
    tball = SDL_CreateTextureFromSurface(rend, ball_s);
    SDL_FreeSurface(ball_s);  // no need now that we have a texture
    SDL_FreeSurface(stand_s);
    SDL_FreeSurface(run_s);


    for(int i = 0; i < FCNT; i++){
        stand_h [i].x = i * SW;
        stand_h [i].y = 0;
        stand_h [i].w = SW;
        stand_h [i].h = SH;
    }

    for (int i = 0; i < FCNT; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            run_h[i][j].x = i * RW;
            run_h[i][j].y = j * RH;
            run_h[i][j].w = RW;
            run_h[i][j].h = RH;
        }
        
    }
    gTrack.x = 0;
    gTrack.y = h - SH;
    gTrack.w = SW;
    gTrack.h = SH;

    bx = (w - BW) / 2;
    by = 0;
    vx = 0;
    vy = 0;
    mouseup = true;
    score = 0;
    frame = 0;
    mx = 0;
    my = 0;
    centerBallx = 0;
    centerBally = 0;
    centerPlayerx = 0;
    centerPlayery = 0;
    ballFromPlayerx = 0;
    ballFromPlayery = 0;


}

prog4_state::~prog4_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
}

bool prog4_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool prog4_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool prog4_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    states["splash"]->draw();
    SDL_SetRenderDrawColor(rend, 0xdd, 0xbb, 0xff, 0xff);
    SDL_RenderClear(rend);
    SDL_GetMouseState(&mx, &my);

        vy++;
        by += vy;

        vx *= 0.98;
        bx += vx;

        if(by + BH > h - 1) {
            score = 0;
            vy = -(vy * 0.7);
            by = h - 1 - BH;
            
            if(fabs(vy) < 2) {
                vx *= 0.9;
            }
        }

        if(bx + BW > h - 1) {
            vx = -(vx * 0.6);
            bx = w - 1 - BW;
        }

        if(bx <= 0) {
            vx = -(vx * 0.6);
            bx = 0;
        }

        double movePercent = .1;
        int displaceFromPlayer = (mx - (gTrack.x + gTrack.w / 2));
        int distBetweenPlayer = abs(displaceFromPlayer);

        gTrack.x += displaceFromPlayer * movePercent;
        if(distBetweenPlayer <= 10)
        SDL_RenderCopy(rend, stand, &stand_h[frame % FCNT], &gTrack);
        else if (distBetweenPlayer <= 100)
        {
            SDL_RenderCopy(rend, run, &run_h[(frame % (FCNT - 2)) + 1][(displaceFromPlayer < 0)], &gTrack);
        }
        else
        {
            SDL_RenderCopy(rend, run, &run_h[frame % FCNT][(displaceFromPlayer < 0)], &gTrack);
        }

        SDL_Rect rect = {(int)round(bx), (int)round(by), BW, BH};

        SDL_RenderCopyEx(rend, tball, nullptr, &rect, bx*1.5, nullptr, SDL_FLIP_NONE);

        stringColor(rend, 20, 20, "Press Space to get started", 0xff000000);
        string s = "Score: " + to_string(score);
        stringColor(rend, 20, 30, s.c_str(), 0xff000000);
        stringColor(rend, 20, 40, "Press enter to exit to menu" , 0xff000000);

        frame++;
        int stop = SDL_GetTicks64() + 35;
        while(SDL_GetTicks64() < stop);

    return true;
}

bool prog4_state::handle_event(const SDL_Event &e) {
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
            case SDLK_SPACE:
                vy -= 20; score = 0; result = true;
                break;
            case SDLK_RETURN:
                transition("game");
                result = true;
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(mouseup){
                mouseup = false;
                result = true;
                if (bx + BW < gTrack.x)
                    {

                    }
                    else if (by + BH < gTrack.y)
                    {

                    }
                    else if (bx > gTrack.x + SW)
                    {

                    }
                    else
                    {
                        centerBallx = (bx + (BW / 2));
                        centerBally = (by + (BH / 2));
                        centerPlayerx = (gTrack.x + (SW / 2));
                        centerPlayery = (gTrack.y + (SH / 2));

                        ballFromPlayerx = -1 * (centerPlayerx - centerBallx);
                        ballFromPlayery = -1 * abs(centerPlayery - centerBally);

                        vx = vx + ballFromPlayerx * .5;
                        vy = vy + ballFromPlayery * .6;
                        score++;

                    }
                }
                break;
                case SDL_MOUSEBUTTONUP:
                result = true; 
                mouseup = true;
                break;  
    default:  break;
    }

    return result;
}
