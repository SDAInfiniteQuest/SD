#include <stdio.h>
#include <stdlib.h>
#include "adn.h"
#include "genetic.h"
#include "display.h"


int main(int argc, char* argv[]){
	int i=50;
	int j=50;
	circle_t cir;
	matrix_t m=init_matrix(1000,600);
	create_world(m,cir);
	SDL_Surface *screen;

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode(m->nb_rows,m->nb_columns,8,SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);

	for(i=0;i<m->nb_rows;i++)  
		for(j=0;j<m->nb_columns;j++)  
			if(getPoint(m,i,j)==1) putpixel(screen,i,j);  

	//printMat(m);

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
