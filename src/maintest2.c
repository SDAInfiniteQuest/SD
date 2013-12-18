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

  matrix_t mat=init_matrix(GRID_SIZE,GRID_SIZE);
  srand(time(NULL));

  create_world(mat,circle);

  init_population(old);
  init_population(new);
  
  if(SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if((screen=SDL_SetVideoMode(mat->nb_columns,mat->nb_rows,32,SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
    fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_WM_SetCaption("World and best path", NULL);

  for (i = 0; i < 200; i++) {
    growth_population(old);
    growth_population(new);
  }
   // test_dessine(screen);
  displayWorld(screen, mat);
  for (i = 0; i < 10000; i++) {
    genetic(mat,old,new);
    //displayDna(screen, old->a[0]);
    SDL_Flip(screen);
  }
    displayDna(screen, old->a[0]);

  printf("collision %d note %f\n",test_ADN(old->a[0],mat),old->a[0]->note); 

//  printf("x:%d y:%d\n",old->a[0]->d[50]->end.x,old->a[0]->d[50]->end.y );

  SDL_Flip(screen);
  pause();

  SDL_Quit();
  return EXIT_SUCCESS;

}
