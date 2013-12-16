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

/*void putpixel(SDL_Surface* screen, Uint16 x, Uint16 y)
{
	Uint32 *pixel = (Uint32*)screen->pixels;
	Uint32 *p = pixel + y*screen->pitch + x;
	*p = SDL_MapRGB(screen->format, 0x99, 0x99,0x99);
}*/


void putpixel(SDL_Surface * surface, Uint16 x, Uint16 y, Uint32 color)
{
	// Nombre de bits par pixels de la surface d'écran 
	Uint8 bpp = surface->format->BytesPerPixel;
	// Pointeur vers le pixel à remplacer (pitch correspond à la
	//  taille 
	//        d'une ligne d'écran, c'est à dire (longueur *
	//        bitsParPixel) 
	//               pour la plupart des cas) 
	Uint8 * p = ((Uint8 *)surface->pixels) + y * surface->pitch + x * bpp;
	switch(bpp)
	{
		case 1:
			*p = (Uint8) color;
			break;
		case 2:
			*(Uint16 *)p = (Uint16) color;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				*(Uint16 *)p = ((color >> 8) & 0xff00) | ((color >> 8) & 0xff);
				*(p + 2) = color & 0xff;
			}
			else
			{
				*(Uint16 *)p = color & 0xffff;
				*(p + 2) = ((color >> 16) & 0xff) ;
			}
			break;
		case 4:
			*(Uint32 *)p = color;
			break;
	}
}


