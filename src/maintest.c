#include <stdio.h>
#include <stdlib.h>
#include "adn.h"
#include "genetic.h"
#include "display.h"


int main(int argc, char* argv[]){
	int i=50;
	int j=50;
	circle_t cir;
	matrix_t m=init_matrix(600,1000);
	create_world(m,cir);
	SDL_Surface *screen;

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode(m->nb_columns,m->nb_rows,8,SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);

	while(i<m->nb_columns) { 
		while(j<m->nb_rows) { if(getPoint(m,i,j)!=0) putpixel(screen,i,j); j++; } 
		i++; 
	}

	SDL_Flip(screen);
	pause();

	//action();

	SDL_Quit();
  return EXIT_SUCCESS;
/*  int i;
  circle_t circle=NULL;
  population_t old=create_population(POPULATION_SIZE);
  population_t new=create_population(POPULATION_SIZE);
  population_t selected=create_population(POPULATION_SIZE*2);
  matrix_t mat=init_matrix(600,400);
  
  create_world(mat,circle);
  
  init_population(old);
  init_population(new);

  for (i = 0; i < 10; i++) {
    growth_population(old);
    growth_population(new);
  }
  
  genetic(mat,old,new);*/
}
