#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>


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

	
	w = SDL_CreateWindow("Prog 2: Centenj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, img->w, img->h, SDL_WINDOW_SHOWN);

	s = SDL_GetWindowSurface(w);

	
	SDL_BlitSurface(img, nullptr, s, nullptr);


	SDL_UpdateWindowSurface(w);
	SDL_Event e;


	while(SDL_PollEvent(&e) == 0 || e.type != SDL_QUIT)
	{
		int x , y , replace;
		int boundx = img->w;
		int boundy = img->h;
		Uint8 R1, R2, G1, G2, B1, B2;

			for (int i = 0; i < boundx * boundy; i++)
			{
			int j = myrand() % (boundx * boundy);
			x = rand() % 3 - 1;
			y = rand() % 3 - 1;

			if(j % boundx + x >= boundx)
			{
				x = 0;
			}
			if(j % boundx + x < 0)
			{
				x = 0;
			}	
			if(j + (y * boundx) > boundy * boundx)
			{
				y = 0;
			}	
			if(j + (y * boundx) < 0)
			{
				y = 0;
			}
				
			
			replace = j + x + (y * boundx);
			if(replace < 0)
				replace = 0;
			else if (replace > boundx * boundy)
				replace = boundx * boundy;

				SDL_GetRGB(((Uint32 *)s->pixels)[j], s->format, &R1, &G1, &B1);
				SDL_GetRGB(((Uint32 *)s->pixels)[replace], s->format, &R2, &G2, &B2);
				((Uint32 *)s->pixels)[replace] = SDL_MapRGB(s->format,R1,G1,B1);
				((Uint32 *)s->pixels)[j] = SDL_MapRGB(s->format,R2,G2,B2);
			
			
			

			
			}
			
		

		SDL_UpdateWindowSurface(w);

	}

	SDL_DestroyWindow(w);
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
