#include "genetic.h"

void growth(adn_t a){
	while(!add_displacement(a,rand()%8,1+rand()%20)){}
}

void growth_population(population_t pop){
	int i;
	for (i = 0; i < pop->nb_adn; i++) {
		growth(pop->a[i]);
	}
}
bool displacement_outside(displacement_t d){
	if(d->end.x<0 || d->end.y<0||d->start.x>GRID_SIZE||d->start.y>GRID_SIZE)
		return FALSE;

	return TRUE;
}

bool adn_outside(adn_t ind){
	int i;
	for (i = 0; i < ind->nb_displacement; i++) {
		if(!displacement_outside(ind->d[i]))
			return TRUE;
	}
	return FALSE;
}

// une jolie SEG_FAULT :)
// ca doit etre du a un appel impossible sur getPoint (out of bound
// blablabla)
bool test_displacement(displacement_t d,matrix_t m){
	bool retVal=TRUE;
	printf("test_displacment entree\n");
	int startX=d->start.x;
	int startY=d->start.y;
	int length=d->length;
	int dir=d->dir;
	//bool tricky_case=FALSE;
	int i;


	if(d->start.x<0 || d->start.y<0)
		return FALSE;
	if(d->end.x>GRID_SIZE || d->end.y>GRID_SIZE)
		return FALSE;

	switch(dir) {
		case SOUTH:
			for(i=0;i<=length+1 && retVal==TRUE;i++)
				if((outOfBound(startX,startY+i)==TRUE) || 
					getPoint(m,startX,startY+i)==1)
						retVal = FALSE;
			break;
		case SOUTH_EAST:
			if(getPoint(m,startX-1,startY-1+1)==1 &&
				getPoint(m,startX-1+1,startY-1)==1)
					retVal=FALSE;
			else 
				for(i=0;i<=length+1 && retVal==TRUE;i++) 
					if((outOfBound(startX+i,startY+i)==TRUE)<0 ||  
						getPoint(m,startX+i,startY+i)==1 || 
						(getPoint(m,startX+i,startY+i+1)==1 && 
						 getPoint(m,startX+i+1,startY+i)==1))
						retVal=FALSE;
			break;
		case EAST:
			for(i=0;i<=length+1 && retVal==TRUE;i++)
				if(outOfBound(startX+i,startY)==TRUE || 
					(getPoint(m,startX+i,startY)==1))
						retVal=FALSE;
			break;
		case NORTH_EAST:
			if(getPoint(m,startX-1,startY+1-1)==1 &&
				getPoint(m,startX-1+1,startY+1)==1)
					retVal=FALSE;
			else 	
				for(i=0;i<=length+1 && retVal==TRUE;i++)
					if(outOfBound(startX+i,startY-i)==TRUE || 
						(getPoint(m,startX+i,startY-i)==1) ||
						(getPoint(m,startX+i,startY-i-1)==1 &&
						getPoint(m,startX+i+1,startY-i)==1))
							retVal=FALSE;
			break;
		case NORTH:
			for(i=0;i<=length+1 && retVal==TRUE;i++)
				if(outOfBound(startX,startY-i)==TRUE ||
					(getPoint(m,startX,startY-i)==1))
						retVal==FALSE;
			break;
		case NORTH_WEST:
			for(i=0;i<=length+1 && retVal==TRUE;i++)
				if(outOfBound(startX-i,startY-i)==TRUE ||
					(getPoint(m,startX-i,startY-i)==1) ||
					(getPoint(m,startX-i-1,startY-i)==1 &&
					getPoint(m,startX-i,startY-i-1)==1))
						retVal=FALSE;
			break;
		case WEST:
			for(i=0;i<=length+1 && retVal==TRUE;i++)
				if(outOfBound(startX-i,startY)==TRUE ||
					(getPoint(m,startX-i,startY)==1))
						retVal=FALSE;
			break;
		case SOUTH_WEST:
			for(i=0;i<=length+1 && retVal==TRUE;i++) 
				if(outOfBound(startX-i,startY+i)==TRUE ||
					(getPoint(m,startX-i,startY+i+1)==1 &&
					getPoint(m,startX-i-1,startY+i)==1))
						retVal=FALSE;
			break;
	}
		
	/*if(dir==0){
		for(i=0;i<=length+1;i++){
			if(startX<0 || startY+i<0)
				return FALSE;
			if(startX>GRID_SIZE || startY+i>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX,startY+i)==1)
				return FALSE;
		}
	}
	else if(dir==1){
		if(getPoint(m,startX-1,startY-1+1)==1 &&
				getPoint(m,startX-1+1,startY-1)==1){
			return FALSE;
		}
		for(i=0;i<=length+1;i++){
			if(startX+i<0 || startY+i<0)
				return FALSE;
			if(startX+i>GRID_SIZE || startY+i>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX+i,startY+i)==1)
				return FALSE;

			if(getPoint(m,startX+i,startY+i+1)==1 &&
					getPoint(m,startX+i+1,startY+i)==1){
				return FALSE;
			}
		}
	}
	else if(dir==2){
		for(i=0;i<=length+1;i++){
			if(startX+i<0 || startY<0)
				return FALSE;
			if(startX+i>GRID_SIZE || startY>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX+i,startY)==1)
				return FALSE;
		}
	}
	else if(dir==3){
		if(getPoint(m,startX-1,startY+1-1)==1 &&
				getPoint(m,startX-1+1,startY+1)==1){
			return FALSE;
		}
		for(i=0;i<=length+1;i++){
			if(startX+i<0 || startY-i<0)
				return FALSE;
			if(startX+i>GRID_SIZE || startY-i>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX+i,startY-i)==1)
				return FALSE;

			if(getPoint(m,startX+i,startY-i-1)==1 &&
					getPoint(m,startX+i+1,startY-i)==1){
				return FALSE;
			}

		}
	}
	else if(dir==4){
		for(i=0;i<=length+1;i++){
			if(startX<0 || startY-i<0)
				return FALSE;
			if(startX>GRID_SIZE || startY-i>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX,startY-i)==1)
				return FALSE;
		}
	}
	else if(dir==5){
		for(i=0;i<=length+1;i++){
			if(startX-i<0 || startY-i<0)
				return FALSE;
			if(startX-i>GRID_SIZE || startY-i>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX-i,startY-i)==1)
				return FALSE;


			if(getPoint(m,startX-i-1,startY-i)==1 &&
					getPoint(m,startX-i,startY-i-1)==1){
				return FALSE;
			}

		}
	}
	else if(dir==6){
		for(i=0;i<=length+1;i++){
			if(startX-i<0 || startY<0)
				return FALSE;
			if(startX-i>GRID_SIZE || startY>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX-i,startY)==1)
				return FALSE;
		}
	}
	else if(dir==7){
		for(i=0;i<=length+1;i++){
			if(startX-i<0 || startY+i<0)
				return FALSE;
			if(startX-i>GRID_SIZE || startY+i>GRID_SIZE)
				return FALSE;
			if(getPoint(m,startX-i,startY+i)==1)
				return FALSE;

			if(getPoint(m,startX-i,startY+i+1)==1 &&
					getPoint(m,startX-i-1,startY+i)==1){
				return FALSE;
			}
		}
	}*/
	printf("test_displacment sortie\n");
	return retVal;
}

int test_ADN(adn_t ind,matrix_t m){
	int i;
	int count_collision=0;

	for (i = 0; i < ind->nb_displacement; i++) {
		if(test_displacement(ind->d[i],m)==FALSE)
			count_collision++;
	}
	return count_collision;
}

//Enjambement a 30%
adn_t crossing_over(adn_t A,adn_t B){
	int size_A=A->nb_displacement;
	int size_B=B->nb_displacement;
	int chance_cross=0;
	int threshold=60;
	int i;
	adn_t C;

	C=create_ADN();
	if (A->note>B->note){
		//threshold-=A->note/3;
		for (i = 1; i < size_A; i++) {
			chance_cross=rand()%101;
			if(chance_cross<=threshold)
				add_displacement(C,A->d[i]->dir,A->d[i]->length);
			else
				add_displacement(C,B->d[i]->dir,B->d[i]->length);
		}
	}
	else{
		//threshold-=B->note/3;
		for (i = 1; i < size_B; i++) {
			chance_cross=rand()%101;
			if(chance_cross<=threshold)
				add_displacement(C,B->d[i]->dir,B->d[i]->length);
			else
				add_displacement(C,A->d[i]->dir,A->d[i]->length);
		}
	}
	/*
		 if(min(size_A,size_B)==size_A){
		 for (i = 0; i < size_A; i++) {
		 chance_cross=rand()%101;
		 if(chance_cross<=30)
		 add_displacement(C,A->d[i]->dir,A->d[i]->length);
		 else
		 add_displacement(C,B->d[i]->dir,B->d[i]->length);
		 }
		 for(;i<size_B;i++){
		 add_displacement(C,B->d[i]->dir,B->d[i]->length);
		 }
		 }
		 else{ 
		 for (i = 0; i < size_B; i++) {
		 chance_cross=rand()%101;
		 if(chance_cross<=30)
		 add_displacement(C,B->d[i]->dir,B->d[i]->length);
		 else
		 add_displacement(C,A->d[i]->dir,A->d[i]->length);
		 }
		 for(;i<size_A;i++){
		 add_displacement(C,A->d[i]->dir,A->d[i]->length);
		 }
		 }
		 */
	return C;
}
//choisi aleatoirement les individu de old (les bon de la generation precedante) et les
//cross entre eux et les place dans new, old est trie par la selection 
void crossing_from_population(population_t old,population_t new){
	bool cont=TRUE;
	int index_random1;
	int index_random2;
	int i;

	flush_population(new);
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
	int count_collision=test_ADN(ind,m);

	//Ne rencontre pas d'obstacle ou ne sort pas du jeu 
	if(count_collision==0)
		eval+=100;
	else
		eval-=count_collision*50;

	if (adn_outside(ind)) {
		eval-=10000;
	}

	//distance par rapport a l'arrivee
	if(last_position.x==m->end.x && last_position.y==m->end.y)
		eval+=100;
	else
		eval+=100-sqrt((end.x-last_position.x)*(end.x-last_position.x)+(end.y-last_position.y)*(end.y-last_position.y));
	//Gestion de la longueur du chemin
	//eval-=ind->path_length;

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

	flush_population(selected);
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
	for (i = 0; i < POPULATION_SIZE; i++) {
		freeDna(selected->a[i]);
	}

}

//mutation aleatoire de l'ordre de 1%
void mutate_adn(adn_t ind){
	int nb_displacement=ind->nb_displacement;
	double mut_chance;
	int i;
	int threshold=1;
	//Si un individu est un elite ,note de 200, alors pas de mutation
	//alors que si un individu est tres mauvais, il mutera beaucoup
	//threshold+=ind->note/200;
	//#pragma omp parallel for
	for (i = 1; i < nb_displacement; i++) {
		mut_chance=rand()%100;
		if (mut_chance<threshold) {
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

	//met tous les bon dans old 
	selection(old,new,m);
	//le resultat des crossing des adn de old vont dans new
	crossing_from_population(old,new);

	mutate_population(new);  
	//mutate_population(old);  
	//growth_population(new);

}
