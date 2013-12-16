#include "quicksort.h"

//quicksort les element de old+new dans selected 
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

