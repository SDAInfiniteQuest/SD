#ifndef __XDR_STRUCT_H
#define  __XDR_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#include "grid.h"
#include "adn.h"
#include "genetic.h"


bool_t xdr_matrix(XDR *xdrs,matrix_t* e);
bool_t xdr_point(XDR* xdrs,point* p);
bool_t xdr_displacement(XDR *xdrs, displacement_t* d);
bool_t xdr_adn(XDR *xdrs,adn_t* ind);
bool_t xdr_population(XDR *xdrs,population_t* pop);
#endif
