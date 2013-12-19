#include "include.h"
#include "xdr_struct.h"
#include "display.h"
void* affiche_jeu(matrix_t* m){

  SDL_Surface *screen;
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode((*m)->nb_columns,(*m)->nb_rows,32,SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);

	displayWorld(screen, *m);
	SDL_Flip(screen);
	pause();
  
  return NULL;
}

void* affiche_adn(adn_t* ind){
  
  SDL_Surface *screen;
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode(GRID_SIZE,GRID_SIZE,32,SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);

	displayDna(screen, *ind);
	SDL_Flip(screen);
	pause();

  return NULL;
}

void* affiche_population(population_t* pop){
  int i;
  SDL_Surface *screen;
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode(GRID_SIZE,GRID_SIZE,32,SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);
  for (i = 0; i < (*pop)->nb_adn; i++) {
	  displayDna(screen, (*pop)->a[i]);
  }
	SDL_Flip(screen);
	pause();
  return NULL;
}


void dispatch(struct svc_req* req,SVCXPRT* svc){
  matrix_t* m;
  adn_t* a;
  population_t* pop;

  switch(req->rq_proc){
    case PROCNUM_DISPLAY_GAME:
      if (!svc_getargs(svc,(xdrproc_t) xdr_matrix,(caddr_t) &m)) {
        svcerr_decode(svc);
        break;
      }
      affiche_jeu(m);
      if (!svc_sendreply(svc,(xdrproc_t) xdr_void,(caddr_t) 0)) printf("Erreur traitement call RPC\n");
      break;
    case PROCNUM_DISPLAY_ADN:
      if (!svc_getargs(svc,(xdrproc_t) xdr_adn,(caddr_t) &a)) {
        svcerr_decode(svc);
        break;
      }
      affiche_adn(a);
      if (!svc_sendreply(svc,(xdrproc_t) xdr_void,(caddr_t) 0)) printf("Erreur traitement call RPC\n");
      break;
    case PROCNUM_DISPLAY_POPULATION:
      if (!svc_getargs(svc,(xdrproc_t) xdr_population,(caddr_t) &pop)) {
        svcerr_decode(svc);
        break;
      }
      affiche_population(pop);
      if (!svc_sendreply(svc,(xdrproc_t) xdr_void,(caddr_t) 0)) printf("Erreur traitement call RPC\n");
      break;
    default:
      svcerr_noproc(svc);
      break;
  }
  return;
}

int main (void) {
  bool_t stat;
  int sock=RPC_ANYSOCK;
  unsigned int max_size=sizeof(struct str_adn)*POPULATION_SIZE*sizeof(struct str_displacement)*(NB_DISPLACEMENT+1)+sizeof(struct str_population);
  unsigned int calm=1000000;

  SVCXPRT *serv=NULL;
  if((serv=svctcp_create(sock,calm,calm))==NULL)
    printf("Error creation serveur\n");


//pmap_unset(PROGNUM,VERSNUM);
stat = svc_register(serv,
     /* prognum */ PROGNUM,
     /* versnum */ VERSNUM,
     /* pointeur sur dispatch */  dispatch,
     /* Protocol */ IPPROTO_TCP);
  
  if (stat != 0) {
    fprintf(stderr,"Echec de l'enregistrement du dispatcher\n");
    exit(1);
  }

  svc_run(); /* le serveur est en attente de clients eventuels */
  return(0); /* on y passe jamais ! */
}


