
void growth(adn_t a ){
}

//Enjambement a 70%
void crossing_over(adn_t A,adn_t B){
  int size_A=A->nb_displacement;
}

double evaluation(adn_t ind){
}

void selection(population_t old,population_t new){
}

//mutation aleatoire de l'ordre de 1%
void mutate_adn(adn_t ind){
  int size_adn=ind->size;
  double mut_chance;
  
  //#pragma omp parallel for
  for (i = 0; i < size_adn; i++) {
    mut_chance=rand()%100;
    if (mut_chance<1) {
      change_displacement(ind,i);
    }
  }
}
