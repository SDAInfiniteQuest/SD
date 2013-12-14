#include <stdio.h>
#include <stdlib.h>
#include "adn.h"
#include "genetic.h"


int main(int argc, char* argv[]){
  int i;
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
  
  genetic(mat,old,new);
  return 0;
}
