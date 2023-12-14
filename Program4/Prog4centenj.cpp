#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;

const int FCNT = 7; 

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    SDL_Window *w = nullptr;
    SDL_Surface *s = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    FPSmanager fps;
    SDL_initFramerate(&fps);

    w = SDL_CreateWindow("Prog 4: centenj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *rend = SDL_CreateRenderer(w, -1, 0);
    s = SDL_GetWindowSurface(w);

    /*
     * Load a BMP into a surface... we'll need to turn that
     * into a texture, though, to use the hardware renderer.
     */
    SDL_Surface *ball_s = SDL_LoadBMP("titus.bmp");
    int BW = ball_s->w;
    int BH = ball_s->h;

    SDL_Surface *stand_s = SDL_LoadBMP("standing.bmp");
    int SW = stand_s->w / FCNT; // Standing sprite Width for one frame
    int SH = stand_s->h; // Standing sprite Height for one frame

    SDL_Surface *run_s = SDL_LoadBMP("running.bmp");
    int RW = run_s->w / FCNT;
    int RH = run_s->h / 2;

    SDL_Texture *run = SDL_CreateTextureFromSurface(rend, run_s);
    SDL_Texture *stand = SDL_CreateTextureFromSurface(rend, stand_s);
    SDL_Texture *tball = SDL_CreateTextureFromSurface(rend, ball_s);
    SDL_FreeSurface(ball_s);  // no need now that we have a texture
    SDL_FreeSurface(stand_s);
    SDL_FreeSurface(run_s);

    SDL_Rect stand_h [FCNT];
    for(int i = 0; i < FCNT; i++)
    {
        stand_h [i].x = i * SW;
        stand_h [i].y = 0;
        stand_h [i].w = SW;
        stand_h [i].h = SH;
    }
    SDL_Rect run_h [FCNT][2];
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
    SDL_Rect gTrack;
    gTrack.x = 0;
    gTrack.y = s->h - SH;
    gTrack.w = SW;
    gTrack.h = SH;
        
    int frame = 0;
    /*
     * These are the ball's X,Y and its velocity in each dimension
     */
    float bx = (WIDTH - BW) / 2;
    float by = 0;
    float vy = 0;
    float vx = 0;

    SDL_Event e;
    bool quit = false;
    int score = 0;
    bool mouseup = true;
    while(!quit) {
        /*
         * Clear background with DataBase Fabulous lavender
         */
        SDL_SetRenderDrawColor(rend, 0xdd, 0xbb, 0xff, 0xff);
        SDL_RenderClear(rend);

        /*
         * get the current mouse X,Y to print SDL_CreateRenderer
         */
        int mx;
        int my;
        int centerBallx , centerBally;
        int centerPlayerx , centerPlayery;
        int ballFromPlayerx, ballFromPlayery;
        SDL_GetMouseState(&mx, &my);

        while(SDL_PollEvent(&e)) {
            switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) 
                {
                case SDLK_ESCAPE:  quit = true;  break;
                /*
                 * Bump the ball up the start
                 */
                case SDLK_SPACE:  vy -= 20; score = 0;  break;
                }
                break;
                                case SDL_MOUSEBUTTONDOWN: 
                {
                    if (mouseup)
                    {
                        mouseup = false;
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
                }
                case SDL_MOUSEBUTTONUP: mouseup = true; break;
            default:
                break;
            }
        }

        /*
         * gravity increases velocity.  falling down to our eyes is actually
         * increasing the Y position (NOT making it smaller)
         */
        vy++;
        by += vy;

        /*
         * Dampen the sideways velocity all the time, but just a bit...
         * give the feel of air drag
         */
        vx *= 0.98;
        bx += vx;

        /*
         * Bounce off the bottom of the screen, but also let the floor
         * "absorb" some energy by losing 30% of Y velocity.  Also, constrain
         * the ball so it's not off the bottom of the screen ever.
         */
        if(by + BH > HEIGHT - 1) {
            score = 0;
            vy = -(vy * 0.7);
            by = HEIGHT - 1 - BH;
            /*
             * This drops the sideways velocity when the ball is
             * on the ground and not bouncing up high... in other words
             * a rolling ball should slow to a halt quickly because
             * of drag on the ground
             */
            if(fabs(vy) < 2) {
                vx *= 0.9;
            }
        }

        /*
         * Don't go off the right of the screen.  Bounces absorb energy
         */
        if(bx + BW > WIDTH - 1) {
            vx = -(vx * 0.6);
            bx = WIDTH - 1 - BW;
        }

        /*
         * Don't go off the left of the screen.  Bounces absorb energy
         */
        if(bx <= 0) {
            vx = -(vx * 0.6);
            bx = 0;
        }

        //RENDERING FOR PLAYER FIGURE
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

        /* RenderCopy-ing is the GPU renderer equivalent of blitting */

        //SDL_Rect rect = {(WIDTH - BW) / 2, (HEIGHT - BH) / 2, BW, BH};
        //SDL_Rect rect = {mx - BW / 2, my - BH / 2, BW, BH};
        SDL_Rect rect = {(int)round(bx), (int)round(by), BW, BH};
        //SDL_RenderCopy(rend, tball, nullptr, &rect);
        //SDL_RenderCopyEx(rend, tball, nullptr, &rect, (int)round(bx*1.5) % 360, nullptr, SDL_FLIP_NONE);
        SDL_RenderCopyEx(rend, tball, nullptr, &rect, bx*1.5, nullptr, SDL_FLIP_NONE);

/*        for(int y = 0; y < HEIGHT/100; y++) {
            for(int x = 0; x < WIDTH/100; x++) {
                SDL_SetRenderDrawColor(rend, rand(), rand(), rand(), 0xff);
                for(int i = 0; i < 10000; i++)
                    SDL_RenderDrawPoint(rend, rand() % WIDTH, rand() % HEIGHT);
            }
        }
*/

        /* Write info on the screen */
        stringColor(rend, 20, 20, "Press Space to get started", 0xff000000);
        string s = "Score: " + to_string(score);
        stringColor(rend, 20, 30, s.c_str(), 0xff000000);

        /*
         * This actually "renders" what's been drawn from GPU RAM to the
         * actual SDL_CreateRenderer
         */
        SDL_RenderPresent(rend);

        /*
         * don't do frames faster than 35 ms
         */
        frame++;
        int stop = SDL_GetTicks64() + 35;
        while(SDL_GetTicks64() < stop);
    }

    SDL_DestroyTexture(tball);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return EXIT_SUCCESS;
}
