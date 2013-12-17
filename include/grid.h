#ifndef __GRID_H
#define __GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bool.h"

#define GRID_SIZE 840

typedef struct str_point {
	int x;
	int y;
} point,*point_t;

typedef struct str_circle{
	int radius;
	point center;
}circle,*circle_t;

typedef struct str_matrix{
	char* m;
	point start;
	point end;
	int nb_rows;
	int nb_columns;
}matrix,*matrix_t;



matrix_t init_matrix(int height,int length);
int min(int a,int b);
double distance(point_t p1,point_t p2);
matrix_t setPoint(matrix_t m,int x,int y);
int getPoint(matrix_t m,int x,int y);
matrix_t circle_in_matrix(matrix_t m, circle_t c);
void create_world(matrix_t m,circle_t circleToDraw);
void printMat(matrix_t);
#endif
