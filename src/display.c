#include "display.h"

void diplayGrid(matrix_t m) {
	SDL_SetVideoMode(m->nb_columns,m->nb_rows,8,SDL_DOUBLEBUF | SDL_HWSURFACE);	
}

void pause() {
	int stop = 1;
	SDL_Event event;

	while (stop)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				stop = 0;
		}
	}
}

void putpixel(SDL_Surface* screen, int x, int y)
{
	Uint32 *pixel = (Uint32*)screen->pixels;
	Uint32 *p = pixel + y*screen->pitch/4 + x;
	*p = SDL_MapRGB(screen->format, 0x99, 0x99,0x99);
}



