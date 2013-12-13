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
displacement_t create_displacement(point start,char dir,int length);
void compute_displacement(displacement_t dis,char dir,int length);
adn_t create_ADN();

bool add_displacement(adn_t ind,char dir,int lenght,matrix_t m){
typedef struct str_displacement {
	point start;
	point end;
	char dir;
	int length;
} displacement,displacement_t*;

typedef struct str_adn {
	displacement* d;
	int nb_displacement;
	int size;//nombre de place restante en memoire
	double path_lenght; //longueur du chemin parcouru 
	double note; //note apres evalutaion
}adn, adn_t*;

typedef struct str_population{
	adn_t* a;
	int nb_adn;
	int size;
}population,population_t*;
#endif
