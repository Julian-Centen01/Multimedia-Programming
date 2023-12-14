#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

using namespace std;

const int WIDTH = 300;
const int HEIGHT = 300;

Uint32 myrand() {
	Uint32 result = rand();
	Uint32 A = rand() << 15;
	Uint32 B = rand() << 30;

	result = result ^ A ^ B;

	return result;
}

int main(int argc, char* args[]) {
 srand(time(nullptr));
 int randrgb;
 int coinflip;
 Uint8 R = 0;
 Uint8 G = 0;
 Uint8 B = 0;

 SDL_Window *w = nullptr;
 SDL_Surface *s = nullptr;
 if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
  cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
  exit(EXIT_FAILURE);
 }
 w = SDL_CreateWindow("Prog 1:centenj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
 s = SDL_GetWindowSurface(w);
 SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, R, G, B));
// for(int i = 0; i < WIDTH * HEIGHT; i++) {
//  ((Uint32 *)(s->pixels))[i] = myrand();
// }
 
 SDL_UpdateWindowSurface(w);
 SDL_Event e;
 while(SDL_PollEvent(&e) == 0 || e.type != SDL_QUIT){
    randrgb = rand() % 3;
    if (randrgb == 0)
    {
        coinflip = rand() % 2;
        if ((coinflip == 0 && R != 255) || (coinflip == 1 && R == 0))
        {
            SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, (R + 1), G, B));
            R = R + 1;
        }
        else
        {
            SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, (R - 1), G, B));
            R = R - 1;
        }
        
    }
    else if (randrgb == 1)
    {
        coinflip = rand() % 2;
        if ((coinflip == 0 && G != 255) || (coinflip == 1 && G == 0))
        {
            SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, R, G, B));
            G = G + 1;
        }
        else
        {
            SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, R, (G - 1), B));
            G = G - 1;
        }
    }
    else
    {
        coinflip = rand() % 2;
        if ((coinflip == 0 && B != 255) || (coinflip == 1 && B == 0))
        {
            SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, R, G, B + 1));
            B = B + 1;
        }
        else
        {
            SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, R, G, (B - 1)));
            B = B - 1;
        }
    }
    SDL_UpdateWindowSurface(w);
    
 }
 SDL_DestroyWindow(w);
 SDL_Quit();
 return EXIT_SUCCESS;
}