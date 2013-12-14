#ifndef __GENETIC_H
#define __GENETIC_H

#include <stdio.h>
#include <stdlib.h>
#include "adn.h"
#include "grid.h"

void growth(adn_t a);
adn_t crossing_over(adn_t A,adn_t B);
void evaluation(adn_t ind,matrix_t m);
void selection(population_t old,population_t new,matrix_t m);
void mutate_adn(adn_t ind);


#endif
