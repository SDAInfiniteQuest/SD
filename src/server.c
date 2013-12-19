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
int main (void) {
  bool_t stat;

stat = registerrpc(/* prognum */ PROGNUM,
     /* versnum */ VERSNUM,
     /* procnum */ PROCNUM_DISPLAY_GAME,
     /* pointeur sur fonction */  affiche_jeu,
     /* decodage arguments */ (xdrproc_t)xdr_matrix,
     /* encodage retour de fonction */ (xdrproc_t)xdr_void);
  
  if (stat != 0) {
    fprintf(stderr,"Echec de l'enregistrement\n");
    exit(1);
  }
 stat = registerrpc(/* prognum */ PROGNUM,
     /* versnum */ VERSNUM,
     /* procnum */ PROCNUM_DISPLAY_ADN,
     /* pointeur sur fonction */  affiche_adn,
     /* decodage arguments */ (xdrproc_t)xdr_adn,
     /* encodage retour de fonction */ (xdrproc_t)xdr_void);
  
  if (stat != 0) {
    fprintf(stderr,"Echec de l'enregistrement\n");
    exit(1);
  }
 stat = registerrpc(/* prognum */ PROGNUM,
     /* versnum */ VERSNUM,
     /* procnum */ PROCNUM_DISPLAY_POPULATION,
     /* pointeur sur fonction */  affiche_population,
     /* decodage arguments */ (xdrproc_t)xdr_population,
     /* encodage retour de fonction */ (xdrproc_t)xdr_void);
  if (stat != 0) {
    fprintf(stderr,"Echec de l'enregistrement\n");
    exit(1);
  }

  svc_run(); /* le serveur est en attente de clients eventuels */
  return(0); /* on y passe jamais ! */
}


