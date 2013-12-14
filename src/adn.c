#include "adn.h"
displacement_t create_displacement(point start,char dir,int length){
  displacement_t d=malloc(sizeof(struct str_displacement));
  d->start=(point)start;
  d->dir=dir;
  d->length=length;

  compute_displacement(d,dir,length);

  return d;
}

void compute_displacement(displacement_t dis,char dir,int length){
  point start=dis->start;
  point* end=&dis->end;

  if(dir==0){
    end->x=start.x;
    end->y=start.y+length;
    return;
  }
  else if(dir==1){
    end->x=start.x+length;
    end->y=start.y+length;
    return;
  }
  else if(dir==2){
    end->x=start.x+length;
    end->y=start.y;
    return;
  }
  else if(dir==3){
    end->x=start.x+length;
    end->y=start.y-length;
    return;
  }
  else if(dir==4){
    end->x=start.x;
    end->y=start.y-length;
    return;
  }
  else if(dir==5){
    end->x=start.x-length;
    end->y=start.y-length;
    return;
  }
  else if(dir==6){
    end->x=start.x-length;
    end->y=start.y;
    return;
  }
  else if(dir==7){
    end->x=start.x-length;
    end->y=start.y+length;
    return;
  }
}

//recalcul les debut et fin de deplacement depuis un certai index
void recompute_adn_from_index(adn_t ind,int index){
  int size_adn=ind->nb_displacement;
  int i;
  
  for (i = index; i < size_adn; i++) {
    ind->d[index]->start=ind->d[index-1]->end;
    compute_displacement(ind->d[index],ind->d[index]->dir,ind->d[index]->length);
  }
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
  start.y=0;
  new->d[0]=create_displacement(start,0,0);

  new->size=100;
  new->nb_displacement=1;
  return new;
}
//On ne peut pas avoir un deplacement qui sort du jeu
bool add_displacement(adn_t ind,char dir,int length){
  displacement_t new=create_displacement(ind->d[ind->nb_displacement-1]->end,dir,length);
  int size=ind->size;
  int nb_displacement=ind->nb_displacement;
  
  if(new->end.x<0 ||new->end.y<0)
    return FALSE;

  if(size-nb_displacement>0){
    ind->d[nb_displacement]=new;
    ind->nb_displacement++;
    return TRUE;
  }
  else{
    ind->d=realloc(ind->d,(size+50)*(sizeof(struct str_displacement)));
    ind->d[nb_displacement]=new;
    ind->nb_displacement++;
    ind->size+=50;
    return TRUE;
  }
}
void change_displacement(adn_t ind,int index){
  point starting_point=ind->d[index]->start;
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
