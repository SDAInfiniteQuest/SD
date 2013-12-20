#include "quicksort.h"

//quicksort les element de old+new dans selected 
void quicksort_mult_population(population_t elite,population_t* pop,int nb_pop,int population_size){
  static population_t selected=NULL;
  int i,j;
  int current;

  if (selected==NULL) {
    selected=create_population(nb_pop*population_size);
  }
  flush_population(selected);

  for (i = 0; i < nb_pop; i++) {
    for (j = 0; j < population_size; j++) {
      population_add(pop[i]->a[j],selected);
    }
  }
  
  quicksort(selected,0,nb_pop*population_size-1);
  
  for (i = 0; i < elite->size; i++) {
    current=(population_size*nb_pop)-1-i;
    population_add(copy_adn(selected->a[current]),elite);
  }
}

void quicksort_population(population_t old,population_t new,population_t selected){
  int i;

  //#pragma omp parallel for
  for (i = 0; i < POPULATION_SIZE; i++) {
    //selected->a[i]=old->a[i];
    //selected->a[i+POPULATION_SIZE]=new->a[i];
    population_add(old->a[i],selected);
  }
  for (i = 0; i < POPULATION_SIZE; i++) {
    //selected->a[i]=old->a[i];
    //selected->a[i+POPULATION_SIZE]=new->a[i];
    population_add(new->a[i],selected);
  }

  quicksort(selected,0,POPULATION_SIZE*2-1);

}

void echanger(population_t tab,int i,int j){
  adn_t tmp=tab->a[j];
  
  tab->a[j]=tab->a[i];
  tab->a[i]=tmp;
}


void quicksort(population_t tab,int debut,int fin){
  int i;

  if(debut<fin){
    float pivot=tab->a[fin]->note;
    int elementAechanger=debut;

    for(i=debut;i<fin;i++){
      if(tab->a[i]->note<pivot){
        echanger(tab,i,elementAechanger);
        elementAechanger++;
      }
    }
    echanger(tab,elementAechanger,fin);
    quicksort(tab,debut,elementAechanger-1);
    quicksort(tab,elementAechanger+1,fin);
  }
}

