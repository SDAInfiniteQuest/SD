#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <SDL/SDL.h>
#include "grid.h"

void diplayGrid(matrix_t m) ;
void pause();
//void putpixel(SDL_Surface* , int , int);

void putpixel(SDL_Surface * surface, Uint16 x, Uint16 y, Uint32 color);
#endif:w

