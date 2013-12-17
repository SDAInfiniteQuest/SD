#ifndef __GENETIC_H
#define __GENETIC_H

#include <stdio.h>
#include <stdlib.h>
#include "adn.h"
#include "grid.h"
#include "quicksort.h"

void growth(adn_t a);
void growth_population(population_t pop);
adn_t crossing_over(adn_t A,adn_t B);
void evaluation(adn_t ind,matrix_t m);
void selection(population_t old,population_t new,matrix_t m);
void mutate_adn(adn_t ind);
bool test_displacement(displacement_t d,matrix_t m);
int test_ADN(adn_t ind,matrix_t m);
void genetic(matrix_t m,population_t old,population_t new );
bool adn_outside(adn_t ind);
bool displacement_outside(displacement_t d);

#endif
