#ifndef __GENETIC_H
#define __GENETIC_H

#include <stdio.h>
#include <stdlib.h>
#include "adn.h"
#include "grid.h"

void growth(adn_t a );
void crossing_over(adn_t A,adn_t B);
double evaluation(adn_t ind);
void selection(population_t old,population_t new);
void mutate_adn(adn_t ind);


#endif
