#include "include.h"
#include "xdr_struct.h"
#include "display.h"
#include <omp.h>
#include <pthread.h>

int NB_THREADS;
matrix_t mat;
population_t* old;
population_t* new;
population_t elite_local;   //les 100 meilleurs de chaque sous-population 
population_t elite_remote;  //les 100 meilleurs des autre serveurs confondu

void set_nb_threads(int nb_threads){
  NB_THREADS=nb_threads;
  old=malloc(sizeof(population_t)*nb_threads);
  new=malloc(sizeof(population_t)*nb_threads);
  elite_local=create_population(100);
  elite_remote=NULL;
}



//initialise une population
void set_genetic(int index){
  int i;
  old[index]=create_population(POPULATION_SIZE);
  new[index]=create_population(POPULATION_SIZE);

  init_population(old[index]);
  init_population(new[index]);

  for (i = 0; i < NB_DISPLACEMENT; i++) {
    growth_population(old[index]);
    growth_population(new[index]);
  }
}

//recupere la matrix du client et initialise toute les population
void* get_matrix(matrix_t m){
  int i;
  mat=m;
  
  for (i = 0; i < NB_THREADS; i++) {
    set_genetic(i);
  }
  return NULL;
}

population_t* genetic_wrapper(){
  int i,j;

  for (i = 0; i < elite_local->nb_adn; i++) {
    freeDna(elite_local->a[i]);
  }
  flush_population(elite_local);

  #pragma omp parallel for schedule(dynamic,1) private(j)
  for (i = 0; i < NB_THREADS; i++) {
    printf("%d\n",omp_get_thread_num());
    for (j = 0; j < NB_GENERATION; j++) {
      genetic(mat,old[i],new[i]);
    }
  }
  
    quicksort_mult_population(elite_local,old,NB_THREADS,POPULATION_SIZE);
    if(NB_THREADS>1){
      for (i = 0; i < NB_THREADS; i++) {
        add_population_to_tail(old[i],elite_local);
      }
    }
    
  return &elite_local;
}


void dispatch(struct svc_req* req,SVCXPRT* svc){

  switch(req->rq_proc){
    int i;

    case PROCNUM_GET_MATRIX:
      printf("Reception de la matrice et initialisation\n");
      if (!svc_getargs(svc,(xdrproc_t) xdr_matrix,(caddr_t) &mat)) {
        svcerr_decode(svc);
        break;
      }
      get_matrix(mat);
      if (!svc_sendreply(svc,(xdrproc_t) xdr_void,(caddr_t) 0)) printf("Erreur traitement call RPC\n");
      break;
    case PROCNUM_GENETIC:
      genetic_wrapper();
      printf("fin calcul\n");
      if (!svc_sendreply(svc,(xdrproc_t) xdr_population,(caddr_t) &elite_local)) printf("Erreur traitement call RPC\n");
      break;
    case PROCNUM_GET_OTHER:
      if(elite_remote!=NULL){
        freePopulation(elite_remote);
      }

      if (!svc_getargs(svc,(xdrproc_t) xdr_population,(caddr_t) &elite_remote)) {
        svcerr_decode(svc);
        break;
      }
      
      #pragma omp parallel for
      for (i = 0; i < NB_THREADS; i++) {
        add_population_to_tail(new[i],elite_remote);
      }

      if (!svc_sendreply(svc,(xdrproc_t) xdr_void,(caddr_t) 0)) printf("Erreur traitement call RPC\n");
    default:
      svcerr_noproc(svc);
      break;
  }
  return;
}

int main (int argc,char** argv) {
  bool_t stat;
  unsigned int calm=1000000;
  set_nb_threads(4);
  srand(time(NULL));
  unsigned int prognum=strtoul(argv[1],NULL,0);
  unsigned int versnum=strtoul(argv[2],NULL,0);
  SVCXPRT *serv=NULL;

  if((serv=svctcp_create(RPC_ANYSOCK,calm,calm))==NULL)
    printf("Error creation serveur\n");
  printf("versnum%u\n",versnum);
  prognum+=0x20050000;
  printf("prognum %u\n",prognum);
  pmap_unset(prognum,versnum);
  stat = svc_register(serv,
     /* prognum */ prognum,
     /* versnum */ versnum,
     /* pointeur sur dispatch */  dispatch,
     /* Protocol */ IPPROTO_TCP);
  
  if (stat != 1) {
    fprintf(stderr,"Echec de l'enregistrement du dispatcher\n");
    exit(1);
  }

  svc_run(); /* le serveur est en attente de clients eventuels */
  return(0); /* on y passe jamais ! */
}


