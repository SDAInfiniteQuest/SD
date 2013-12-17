/**
 * @file adn.h
 * @author Pallamidessi Joseph
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
**/	

#ifndef __ADN_H
#define __ADN_H

#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#include "grid.h"

#define POPULATION_SIZE 100

#define SOUTH 			0
#define SOUTH_EAST 	1
#define EAST 				2
#define NORTH_EAST 	3
#define NORTH 			4
#define NORTH_WEST 	5
#define WEST 				6
#define SOUTH_WEST 	7

typedef struct str_displacement {
	point start;
	point end;
	char dir;
	int length;
} displacement,*displacement_t;

typedef struct str_adn {
	displacement_t* d;
	int nb_displacement;
	int size;//nombre de place restante en memoire
	double path_lenght; //longueur du chemin parcouru 
	double note; //note apres evalutaion
}adn,*adn_t;

typedef struct str_population{
	adn_t* a;
	int nb_adn;
	int size;
}population,*population_t;

displacement_t create_displacement(point start,char dir,int length);
void compute_displacement(displacement_t dis,char dir,int length);
void recompute_adn_from_index(adn_t ind,int index);
void recompute_adn(adn_t t);
bool add_displacement(adn_t ind,char dir,int lenght);
void change_displacement(adn_t ind,int index);
population_t create_population(int size);
bool population_add(adn_t ind,population_t pop);
adn_t create_ADN();
void init_population(population_t pop);


void freeDna(adn_t a); 
void freeDisplacement(displacement_t d);
void freePopulation(population_t p);

#endif
