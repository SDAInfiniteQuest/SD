#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <SDL/SDL.h>
#include "grid.h"
#include <adn.h>

void action();
//void putpixel(SDL_Surface* , int , int);

void putpixel(SDL_Surface * surface, Uint16 x, Uint16 y, Uint32 color);
void displayWorld(SDL_Surface *surface, matrix_t m);
void displayDisplacement (SDL_Surface *screen, displacement_t d);
void displayDna(SDL_Surface *surface, adn_t a);
void test_dessine(SDL_Surface* screen);
#endif

