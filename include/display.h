#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <SDL/SDL.h>
#include "grid.h"

void diplayGrid(matrix_t m) ;
void pause();
void putpixel(SDL_Surface* , int , int);
#endif
