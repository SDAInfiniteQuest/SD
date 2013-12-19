#include "adn.h"
displacement_t create_displacement(point start,char dir,int length){
  displacement_t d=malloc(sizeof(struct str_displacement));
  d->start=(point)start;
  d->dir=dir;
  d->length=length;

  compute_displacement(d,dir,length);

  return d;
}

adn_t alloc_adn(int nb_displacement,int size,double path_length,double note){
  adn_t new=create_ADN();
  new->d=realloc(new->d,(size)*(sizeof(struct str_displacement)));
  new->nb_displacement=nb_displacement;
  new->path_length=path_length;
  new->note=note;
  
  return new;
}

void compute_displacement(displacement_t dis,char dir,int length){
  point start=dis->start;
  point* end=&dis->end;

	switch(dir) {
		case SOUTH:
	    end->x=start.x;
	    end->y=start.y+length;
			break;
		case SOUTH_EAST:
	    end->x=start.x+length;
  	  end->y=start.y+length;
			break;
		case EAST:
		  end->x=start.x+length;
  	  end->y=start.y;
			break;
		case NORTH_EAST:
	    end->x=start.x+length;
  	  end->y=start.y-length;
			break;
		case NORTH:
    	end->x=start.x;
    	end->y=start.y-length;
			break;
		case NORTH_WEST:
    	end->x=start.x-length;
    	end->y=start.y-length;
			break;
		case WEST:
    	end->x=start.x-length;
    	end->y=start.y;
			break;
		case SOUTH_WEST:
    	end->x=start.x-length;
    	end->y=start.y+length;
			break;
	}
}

//recalcul les debut et fin de deplacement depuis un certai index
void recompute_adn_from_index(adn_t ind,int index){
  int size_adn=ind->nb_displacement;
  int i;
  
  for (i = index; i < size_adn; i++) {
    ind->d[i]->start=ind->d[i-1]->end;
    compute_displacement(ind->d[i],ind->d[i]->dir,ind->d[i]->length);
  }
}

void flush_population(population_t pop){
  pop->nb_adn=0;
}

//recalcul tout les deplacement d'un adn
void recompute_adn(adn_t ind){
  //int size_adn=ind->nb_displacement;
  //int i;
  
  //skip le debut
  recompute_adn_from_index(ind,1);
}

adn_t create_ADN(){
  adn_t new=malloc(sizeof(struct str_adn));
  new->d=malloc(sizeof(displacement_t)*100);
  point start;
  start.x=0;
  start.y=GRID_SIZE/2;
  new->d[0]=create_displacement(start,0,0);
  new->path_length=0;
  new->size=100;
  new->nb_displacement=1;
  new->note=0;
  return new;
}

//On ne peut pas avoir un deplacement qui sort du jeu
//Renvoit TRUE si déplacement correct et FALSE sinon
bool add_displacement(adn_t ind,char dir,int length){
  displacement_t new=create_displacement(ind->d[ind->nb_displacement-1]->end,dir,length);
  int size=ind->size;
  int nb_displacement=ind->nb_displacement;
  
  //if(new->end.x<0 ||new->end.y<0)
  //  return FALSE;
  if(dir!=1 || dir!=3 || dir!=5 || dir!=7) 
    ind->path_length+=length;
  else 
    ind->path_length+=distance(&new->start,&new->end);

  if(size-nb_displacement>0){
    ind->d[nb_displacement]=new;
    ind->nb_displacement++;
    return TRUE;
  }
  else{
    ind->d=realloc(ind->d,(size*2)*(sizeof(struct str_displacement)));
    ind->d[nb_displacement]=new;
    ind->nb_displacement++;
    ind->size*=2;
    return TRUE;
  }
}

void change_displacement(adn_t ind,int index){
  point starting_point=ind->d[index-1]->end;
  free(ind->d[index]);
  displacement_t new=create_displacement(starting_point,rand()%8,rand()%30);
  ind->d[index]=new;
  recompute_adn_from_index(ind,index);
}


population_t create_population(int size){
  population_t new=malloc(sizeof(struct str_population));
  new->a=malloc(sizeof(adn_t)*size);
  new->nb_adn=0;
  new->size=size;
  
  return new;
}

bool population_add(adn_t ind,population_t pop){
  int nb_adn=pop->nb_adn;
  int size=pop->size;

  if(nb_adn<size){
    pop->a[nb_adn]=ind;
    pop->nb_adn++;
    return TRUE;
  }
  return FALSE;
}

void init_population(population_t pop){
  int i;

  for (i = 0; i < POPULATION_SIZE; i++) {
    population_add(create_ADN(),pop);
  }
}

void freeDisplacement(displacement_t d) {
	free(d);
}

void freeDna(adn_t a) {
	int i;
	for (i = 0; i < a->nb_displacement; i++) {
		freeDisplacement(a->d[i]);
	}
	free(a->d);
	free(a);
}

void freePopulation(population_t p) {
	int i;
	for (i = 0; i < p->nb_adn; i++) {
		freeDna(p->a[i]);
	}
	free(p->a);
	free(p);
}
