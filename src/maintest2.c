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
  circle_t circle=NULL;
	SDL_Surface *screen;
  population_t old=create_population(POPULATION_SIZE);
  population_t new=create_population(POPULATION_SIZE);
  
  matrix_t mat=init_matrix(600,400);
  srand(time(NULL));

  create_world(mat,circle);
  
  init_population(old);
  init_population(new);

  for (i = 0; i < 50; i++) {
    growth_population(old);
    growth_population(new);
  }
  
  for (i = 0; i < 2000; i++) {
    genetic(mat,old,new);
  }

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
	displayDna(screen, old->a[0]);
	
	SDL_Flip(screen);
	pause();

	SDL_Quit();
  return EXIT_SUCCESS;

}
