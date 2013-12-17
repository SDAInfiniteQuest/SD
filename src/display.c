#include "display.h"

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


void putpixel(SDL_Surface * surface, Uint16 x, Uint16 y, Uint32 color){
	//printf("entree putpixel\n");
	// Nombre de bits par pixels de la surface d'écran 
	Uint8 bpp = surface->format->BytesPerPixel;
	// Pointeur vers le pixel à remplacer (pitch correspond à la
	//  taille 
	//        d'une ligne d'écran, c'est à dire (longueur *
	//        bitsParPixel) 
	//               pour la plupart des cas) 
	Uint8 * p = ((Uint8 *)surface->pixels) + y * surface->pitch + x * bpp;
	switch(bpp)	{
		case 1:
			*p = (Uint8) color;
			break;
		case 2:
			*(Uint16 *)p = (Uint16) color;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				*(Uint16 *)p = ((color >> 8) & 0xff00) | ((color >> 8) & 0xff);
				*(p + 2) = color & 0xff;
			}
			else {
				*(Uint16 *)p = color & 0xffff;
				*(p + 2) = ((color >> 16) & 0xff) ;
			}
			break;
		case 4:
			*(Uint32 *)p = color;
			break;
	}
	//printf("sortie putpixel\n");
}

void displayWorld (SDL_Surface *screen, matrix_t m) {
	Uint16 i,j;
	for (i = 0; i < m->nb_rows; i++)
		for (j = 0; j < m->nb_columns; j++) 
			if(m->m[i*m->nb_columns+j]==0) putpixel(screen, i, j, 0xffffff);
}

void displayDisplacement (SDL_Surface *screen, displacement_t d) {
	static Uint32 color=0x0033ff;

	int i;
	char mv=d->dir;
	int abs=d->start.x;
	int ord=d->start.y;
	for (i = 0; i < d->length; i++) {
				printf("(%d,%d,%d,%d)\n",abs,ord,i,mv);
		switch(mv) {
			case SOUTH:
				putpixel(screen, abs, ord+i, color);
				break;
			case SOUTH_EAST:
				putpixel(screen, abs+i, ord+i, color);
				break;
			case EAST:
				putpixel(screen, abs+i, ord, color);
				break;
			case NORTH_EAST:
				putpixel(screen, abs+i, ord-i, color);
				break;
			case NORTH:
				putpixel(screen, abs, ord-i, color);
				break;
			case NORTH_WEST:
				putpixel(screen, abs-i, ord-i, color);
				break;
			case WEST:
				putpixel(screen, abs-i, ord, color);
				break;
			case SOUTH_WEST:
				putpixel(screen, abs-i, ord+i, color);
				break;
		}
	}
	if(color>0x0) color-=10;
	//printf("%d\n",color);
}

void displayDna (SDL_Surface *screen, adn_t a) {
	int i;
	for (i = 0; i < a->nb_displacement; i++) {
		displayDisplacement(screen,a->d[i]);
	}
}
