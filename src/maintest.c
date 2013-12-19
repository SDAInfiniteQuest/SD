#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adn.h"
#include "genetic.h"
#include <time.h>
#include "display.h"


int main(int argc, char* argv[]){
	srand(time(NULL));
	int i;
	circle_t cir=NULL;
	adn_t a=create_ADN();
	matrix_t m=init_matrix(GRID_SIZE,GRID_SIZE);
	create_world(m,cir);
	SDL_Surface *screen;

	for (i = 1; i < 100;) 
		if(add_displacement(a,(char)(rand()%8), rand()%100)==TRUE) i++;

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode(m->nb_columns,m->nb_rows,32,SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);

	displayWorld(screen, m);
	displayDna(screen, a);
	
	SDL_Flip(screen);
	action();

	SDL_Quit();
  return EXIT_SUCCESS;
  
}
