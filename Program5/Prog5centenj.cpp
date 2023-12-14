#include <iostream>
#include <thread>
#include <cstdlib>
#include <atomic>
#include <ctime>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>
#include <SDL_mixer.h>

//some things to note before getting into this program
//I am very aware that a lot of features are missing, but I am running short on time
//and don't want to waste any more on the previous assignments
//As far as im aware, there is no presense of the following:
//A track
//SDL sound effects

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;


void race(atomic <int> *winner, int racer , double *percent , int style , double *progress){

    if(*winner == -1){
        if(*percent >= 1.0)
            *winner = racer;
        else{
            switch (style)
            {
            case 1:
                *percent = 1.0 - cos((*progress * M_PI) / 2.0);
                break;
            case 2:
                *percent = sin((*progress * M_PI) / 2.0);
                break;
            case 3:
                *percent = -1.0 * (cos(M_PI * *progress) - 1.0) / 2.0;
                break;
            case 4:
                *percent = *progress * *progress;
                break;
            case 5:
                *percent = *progress < 0.5 ? 2.0 * *progress * *progress : 1.0 - pow(-2.0 * *progress + 2.0, 2.0) / 2.0;
                break;
            case 6:
                *percent = *progress * *progress * *progress;
                break;
            case 7:
                *percent = 1.0 - (1.0 - *progress) * (1.0 - *progress);
                break;
            default:
                *percent = *progress;
                break;
            }
        }
                
    }

    return;
}
Uint32 myrand() {
	Uint32 result = rand();
	Uint32 A = rand() << 15;
	Uint32 B = rand() << 30;

	result = result ^ A ^ B;

	return result;
}

int main(int argc , char *argv[]){
    srand(time(nullptr));
	SDL_Window *w = nullptr;
	SDL_Surface *s = nullptr;

     if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    FPSmanager fps;
    SDL_initFramerate(&fps);

    w = SDL_CreateWindow("Prog 5: centenj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *rend = SDL_CreateRenderer(w, -1, 0);
    s = SDL_GetWindowSurface(w);

    SDL_Surface *titus_s = SDL_LoadBMP("titus.bmp");
    int TW = titus_s->w;
    int TH = titus_s->h;

    SDL_Surface *frossus_s = SDL_LoadBMP("frossus.bmp");
    int FW = frossus_s->w;
    int FH = frossus_s->h;

    SDL_Surface *prophus_s = SDL_LoadBMP("prophus.bmp");
    int PW = prophus_s->w;
    int PH = prophus_s->h;

    SDL_Texture *titus = SDL_CreateTextureFromSurface(rend , titus_s);
    SDL_Texture *frossus = SDL_CreateTextureFromSurface(rend , frossus_s);
    SDL_Texture *prophus = SDL_CreateTextureFromSurface(rend , prophus_s);

    SDL_FreeSurface(titus_s);
    SDL_FreeSurface(frossus_s);
    SDL_FreeSurface(prophus_s);

    int frame = 0;
    int r1_style = rand() % 8;
    int r2_style = rand() % 8;
    int r3_style = rand() % 8;
    double r1_percent = 0.0;
    double r2_percent = 0.0;
    double r3_percent = 0.0;
    atomic <int> winner = -1;
    double progress = 0.0;

    float tx = 0;
    float ty = 0;
    float fx = 0;
    float fy = 100;
    float px = 0;
    float py = 200;
    
    SDL_Event e;
    bool quit = false;

    while(!quit){
       

         while(SDL_PollEvent(&e)) {
            switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) 
                {
                case SDLK_ESCAPE:  quit = true;  break;
                }
            }
         }

        SDL_SetRenderDrawColor(rend , 0xdd , 0xbb , 0xff , 0xff);
        SDL_RenderClear(rend);

        
        if(winner == -1){
            thread racer1(race , &winner , 1 , &r1_percent , r1_style , &progress);
            thread racer2(race , &winner , 2 , &r2_percent , r2_style , &progress);
            thread racer3(race , &winner , 3 , &r3_percent , r3_style , &progress);

            progress = progress + 0.01;

            racer1.join();
            racer2.join();
            racer3.join();

            tx = (WIDTH - TW) * r1_percent;
            fx = (WIDTH - FW) * r2_percent;
            px = (WIDTH - PW) * r3_percent;
        }
        else{
            string s = "Racer " + to_string(winner) + " wins!";
            stringColor(rend, 20, 20, s.c_str(), 0xff000000);
        }
            SDL_Rect titus_r = {(int)round(tx), (int)round(ty) , TW , TH};
            SDL_Rect frossus_r = {(int)round(fx), (int)round(fy) , FW , FH};
            SDL_Rect prophus_r = {(int)round(px), (int)round(py) , PW , PH};

            SDL_RenderCopy(rend , titus , nullptr , &titus_r);
            SDL_RenderCopy(rend , frossus , nullptr , &frossus_r);
            SDL_RenderCopy(rend , prophus , nullptr , &prophus_r);
        
        

        SDL_RenderPresent(rend);
        frame++;
        int stop = SDL_GetTicks64() + 35;
        while(SDL_GetTicks64() < stop);
    }
    SDL_DestroyTexture(titus);
    SDL_DestroyTexture(frossus);
    SDL_DestroyTexture(prophus);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return EXIT_SUCCESS;
}