#ifndef __QUICKSORT_H
#define __QUICKSORT_H
#include "adn.h"

void quicksort_population(population_t old,population_t new,population_t selected);
void echanger(population_t tab,int i,int j);
void quicksort(population_t tab,int debut,int fin);
void quicksort_mult_population(population_t elite,population_t* pop,int nb_pop);
#endif
