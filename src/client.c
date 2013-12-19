#include "include.h"
#include "xdr_struct.h"
#include "display.h"
int main (int argc, char **argv) {
  char *host = argv[1];
  enum clnt_stat stat;
  int i;
  void* res;
  char choix;
  srand(time(NULL));
  circle_t circle=NULL;
  if (argc!=2) {
    printf("Usage :%s [IP serveur]\n",argv[0]);
  }
  
  static struct timeval TIMEOUT={10000,0};
  population_t old=create_population(POPULATION_SIZE);
  population_t new=create_population(POPULATION_SIZE);

  matrix_t mat=init_matrix(GRID_SIZE,GRID_SIZE);
  srand(time(NULL));

  create_world(mat,circle);

  init_population(old);
  init_population(new);
  
  for (i = 0; i < 50; i++) {
    growth_population(old);
    growth_population(new);
  }
  
  SDL_Surface *screen;
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "impossible de lancer la sdl: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if((screen=SDL_SetVideoMode(mat->nb_columns,mat->nb_rows,32,SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_HWSURFACE))==NULL) {
		fprintf(stderr, "erreur SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  SDL_WM_SetCaption("World and best path", NULL);

	displayWorld(screen,mat);
	SDL_Flip(screen);

  scanf("%c",&choix);
  CLIENT* serv=clnt_create(argv[1],PROGNUM,VERSNUM,"tcp");

  if(choix=='1'){
    stat = clnt_call(/* host */ serv,
        /* procnum */ PROCNUM_DISPLAY_GAME,
        /* encodage argument */ (xdrproc_t) xdr_matrix,
        /* argument */ (caddr_t)&mat,
        /* decodage retour */ (xdrproc_t)xdr_void,
        /* retour de la fonction distante */(caddr_t)&res,
        /*timeout*/TIMEOUT);
    displayWorld(screen,mat);
  }
  else if(choix=='2'){
    stat = clnt_call(/* host */ host,
        /* procnum */ PROCNUM_DISPLAY_ADN,
        /* encodage argument */ (xdrproc_t) xdr_adn,
        /* argument */ (caddr_t)&old->a[0],
        /* decodage retour */ (xdrproc_t)xdr_void,
        /* retour de la fonction distante */(caddr_t)&res,
        /*timeout*/TIMEOUT);
    displayDna(screen,old->a[0]);
  }  
  else if(choix=='3'){
    stat = clnt_call(/* host */ host,
        /* procnum */ PROCNUM_DISPLAY_POPULATION,
        /* encodage argument */ (xdrproc_t) xdr_population,
        /* argument */ (caddr_t)&old,
        /* decodage retour */ (xdrproc_t)xdr_void,
        /* retour de la fonction distante */(caddr_t)&res,
        /*timeout*/TIMEOUT);
    for (i = 0; i < 50; i++) {
      displayDna(screen,old->a[i]);
    }
  }
  
  if (stat != RPC_SUCCESS) { 
    fprintf(stderr, "Echec de l'appel distant\n");
    clnt_perrno(stat);      fprintf(stderr, "\n");
  }
	else{
    SDL_Flip(screen);
    pause();
  }

  return(0);
}
