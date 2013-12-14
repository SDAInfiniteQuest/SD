#include "genetic.h"

void growth(adn_t a){
  while(!add_displacement(a,rand()%8,rand()%30)){}
}

void growth_population(population_t pop){
  int i;
  for (i = 0; i < pop->nb_adn; i++) {
    growth(pop->a[i]);
  }

}
bool test_displacement(displacement_t d,matrix_t m){
	int startX=d->start.x;
	int startY=d->start.y;
	int length=d->length;
  int dir=d->dir;
  int i;

	if(dir==0){
		for(i=0;i<length;i++){
			if(getPoint(m,startX,startY+i)==1)
				return FALSE;
		}
	}
	else if(dir==1){
		for(i=0;i<length;i++){
			if(getPoint(m,startX+i,startY+i)==1)
				return FALSE;
		}
	}
	else if(dir==2){
		for(i=0;i<length;i++){
			if(getPoint(m,startX+i,startY)==1)
				return FALSE;
		}
	}
	else if(dir==3){
		for(i=0;i<length;i++){
			if(getPoint(m,startX+i,startY-i)==1)
				return FALSE;
		}
	}
	else if(dir==4){
		for(i=0;i<length;i++){
			if(getPoint(m,startX,startY-i)==1)
				return FALSE;
		}
	}
	else if(dir==5){
		for(i=0;i<length;i++){
			if(getPoint(m,startX-i,startY-i)==1)
				return FALSE;
		}
	}
	else if(dir==6){
		for(i=0;i<length;i++){
			if(getPoint(m,startX-i,startY)==1)
				return FALSE;
		}
	}
	else if(dir==7){
		for(i=0;i<length;i++){
			if(getPoint(m,startX-i,startY+i)==1)
				return FALSE;
		}
	}
	return TRUE;
}

bool test_ADN(adn_t ind,matrix_t m){
	int i;
  for (i = 0; i < ind->nb_displacement; i++) {
		if(!test_displacement(ind->d[i],m))
			return FALSE;
	}
	return TRUE;
}

//Enjambement a 70%
adn_t crossing_over(adn_t A,adn_t B){
  int size_A=A->nb_displacement;
  int size_B=B->nb_displacement;
  int chance_cross=0;
  int i;
  adn_t C;

  C=create_ADN();
  
  if(min(size_A,size_B)==size_A){
    for (i = 0; i < size_A; i++) {
      chance_cross=rand()%101;
      add_displacement(C,B->d[i]->dir,B->d[i]->length);
      if(chance_cross<=70)
        add_displacement(C,A->d[i]->dir,A->d[i]->length);
    }
    for(;i<size_B;i++){
      add_displacement(C,B->d[i]->dir,B->d[i]->length);
    }
  }
  else{ 
    for (i = 0; i < size_B; i++) {
      chance_cross=rand()%101;
      add_displacement(C,A->d[i]->dir,A->d[i]->length);
      if(chance_cross<=70)
        add_displacement(C,B->d[i]->dir,B->d[i]->length);
    }
    for(;i<size_A;i++){
      add_displacement(C,A->d[i]->dir,A->d[i]->length);
    }
  }
 return C;
}
//choisi aleatoirement les individu de old (les bon de la generation precedante) et les
//cross entre eux et les place dans new, old est trie par la selection 
void crossing_from_population(population_t old,population_t new){
  bool cont=TRUE;
  int index_random1;
  int index_random2;
  int i;
  for (i = 0; i < POPULATION_SIZE; i++) {
    population_add(crossing_over(old->a[i],old->a[(POPULATION_SIZE-1)-i]),new);
  }

  while(cont){
    index_random1=rand()%POPULATION_SIZE;
    index_random2=rand()%POPULATION_SIZE;

    if(!population_add(crossing_over(old->a[index_random1],old->a[index_random2]),new)){
      cont=FALSE;
    }
  }
}

void evaluation(adn_t ind,matrix_t m){
  point last_position=ind->d[ind->nb_displacement-1]->end;
  point end=m->end;
  double eval=0;
  //Ne rencontre pas d'obstacle 
  if(test_ADN(ind,m))
    eval+=100;
  else
    eval-=100;

  //distance par rapport a l'arrivee
  if(last_position.x==m->end.x && last_position.y==m->end.y)
    eval+=100;
  else
    eval+=100-sqrt((end.x-last_position.x)*(end.x-last_position.x)+(end.y-last_position.y)*(end.y-last_position.y));
  //pas de gestion de la longueur du chemin pour l'instant
  ind->note=eval;
}
void evaluate_population(population_t pop,matrix_t m){
  int i;
  for (i = 0; i < pop->nb_adn; i++) {
    evaluation(pop->a[i],m);
  }
}

void selection(population_t old,population_t new,matrix_t m){
  static population_t selected;
  int i; 
  if(selected==NULL)
    selected=create_population(POPULATION_SIZE*2);
  /*
  // #pragma omp parallel for 
  for(i=0;i<POPULATION_SIZE;i++){
    evaluation(old->a[i]);
    evaluation(old->b[i]);
  }
  */
  quicksort_population(old,new,selected);
  
  //old contient maintenant tout les bon individu
  for(i=0;i<POPULATION_SIZE;i++)
    old->a[i]=selected->a[(POPULATION_SIZE*2-1)-i];

  //free tout les individu "mauvais", la moitie restante de selected
  /*
  for (i = 1; i <= POPULATION_SIZE; i++) {
    free_adn(selected->a[POPULATION_SIZE-i]);
  }
  */
}

//mutation aleatoire de l'ordre de 1%
void mutate_adn(adn_t ind){
  int nb_displacement=ind->nb_displacement;
  double mut_chance;
  int i; 
  //#pragma omp parallel for
  for (i = 1; i < nb_displacement; i++) {
    mut_chance=rand()%100;
    if (mut_chance<1) {
      change_displacement(ind,i);
    }
  }
}

void mutate_population(population_t p){
  int i;
  for (i = 0; i < p->nb_adn; i++) {
    mutate_adn(p->a[i]);
  }
}

void genetic(matrix_t m,population_t old,population_t new ){

  evaluate_population(old,m);
  evaluate_population(new,m);
  
  selection(old,new,m);
  crossing_from_population(old,new);
  
  mutate_population(new);  

}
