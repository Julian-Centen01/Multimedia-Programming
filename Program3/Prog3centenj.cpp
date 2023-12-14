//This Program requires a .bmp file as an argument
//The purpose of this program is to display the mist effect
//And reveal a section of the image relative to the cursor

#include <iostream>

#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SDL.h>

#include "open-simplex-noise.h"

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;

Uint32 myrand() {
	Uint32 result = rand();
	Uint32 A = rand() << 15;
	Uint32 B = rand() << 30;

	result = result ^ A ^ B;

	return result;
}


int main(int argc, char* args[]) {
	srand(time(nullptr));
	SDL_Window *w = nullptr;
	SDL_Surface *s = nullptr;

		if (argc != 2)
	{
		cout<<"Please provide a .bmp file"<<endl;
		
		return EXIT_FAILURE;
	}




	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SDL_Surface *img = SDL_LoadBMP(args[1]);
	w = SDL_CreateWindow("Prog3: centenj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, img->w, img->h, SDL_WINDOW_SHOWN);
	s = SDL_GetWindowSurface(w);

	SDL_BlitSurface(img, nullptr, s, nullptr);

	Uint8 R[img->w * img->h];
	Uint8 G[img->w * img->h];
	Uint8 B[img->w * img->h];
	for (int i = 0; i < s->w * s->h; i++)
	{
		SDL_GetRGB(((Uint32 *)s->pixels)[i],s->format,&R[i],&G[i],&B[i]);
	}
	

	Uint32 gray[256];
	for(int i = 0; i < 256; i++) {
		gray[i] = SDL_MapRGB(s->format, i,i,i);
	}


	osn_context *noise;
	osn_context *noise1;
	osn_context *noise2;
	osn_context *noise3;
	open_simplex_noise(rand(), &noise);
	open_simplex_noise(rand(), &noise1);
	open_simplex_noise(rand(), &noise2);
	open_simplex_noise(rand(), &noise3);

	double SIZE = 64;
	long cnt = 0;
	SDL_Event e;
	Uint32 *p = (Uint32 *)s->pixels;
	while(SDL_PollEvent(&e) == 0 || e.type != SDL_QUIT) {
		int mx, my;
		SDL_GetMouseState(&mx, &my);
		SIZE = (mx / 4.0) + 1;
		SIZE = 8;
		for(int y = 0; y < s->h; y++) {
			for(int x = 0; x < s->w; x++) {
				double v = open_simplex_noise3(noise, (double)x / SIZE / 1.0, (double)y / SIZE /1.0, (double)cnt/8);
				double v1 = open_simplex_noise3(noise1, (double)x / SIZE / 2.0, (double)y / SIZE /2.0, (double)cnt/16);
				double v2 = open_simplex_noise3(noise2, (double)x / SIZE / 4.0, (double)y / SIZE /4.0, (double)cnt/32);
				double v3 = open_simplex_noise3(noise3, (double)x / SIZE / 8.0, (double)y / SIZE /8.0, (double)cnt/64);

				v = v * 1.0 / 15.0  +
					v1 * 2.0 / 15.0 +
					v2 * 4.0 / 15.0 +
					v3 * 8.0 / 15.0;

				Uint8 g = 256.0 * fabs(v);

				p[y * s->w + x] = gray[g];
			}
		}
		for(int x = mx - 50; x < mx + 50; x++)
		{
			for (int y = my - 50; y < my + 50; y++)
			{
				if((mx/s->w) + x >= s->w)
				{
					
				}
				else if ((mx/s->w) + x < 0)
				{
					
				}
				else if (((my/s->h) * s->w) + (y * s->w) >= s->w * s->h)
				{
					
				}
				else if (((my/s->h) * s->w) + (y * s->w) < 0)
				{
				
				}
				else
				{
					((Uint32 *)s->pixels)[((mx/s->w) +((my/s->h) * s->w)) + x + (y*s->w)] = SDL_MapRGB(s->format , R[((mx/s->w) + ((my/s->h) * s->w)) + x + (y*s->w)],G[((mx/s->w) + ((my/s->h) * s->w)) + x + (y*s->w)],B[((mx/s->w) + ((my/s->h) * s->w)) + x + (y*s->w)]);
				}
			}
			
		}
		cnt++;
		SDL_UpdateWindowSurface(w);
	}

	open_simplex_noise_free(noise);
	SDL_DestroyWindow(w);
	SDL_Quit();

	return EXIT_SUCCESS;
}
