#include "include.h"
#include "xdr_struct.h"
#include "display.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main (int argc, char **argv) {
  char *host = argv[1];
  enum clnt_stat stat;
  int i;
  void* res;
  char choix;
  void* pNULL=NULL;
  population_t population;

  srand(time(NULL));
  circle_t circle=NULL;
  if (argc!=2) {
    printf("Usage :%s [IP serveur]\n",argv[0]);
  }

  static struct timeval TIMEOUT={10000,0};

  matrix_t mat=init_matrix(GRID_SIZE,GRID_SIZE);
  srand(time(NULL));

  create_world(mat,circle);


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

  int codeError=0;
  int sock=RPC_ANYSOCK;
  struct addrinfo *infoAddr= NULL;
  struct addrinfo *toFree= NULL;
  struct addrinfo hints;
  struct sockaddr_in server_addr;
  CLIENT* serv;

  memset((void *)&hints,0,sizeof(struct addrinfo));
  hints.ai_family=AF_INET;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_protocol=0;
  hints.ai_flags=AI_V4MAPPED | AI_ADDRCONFIG;

  if((codeError=getaddrinfo(host,NULL,&hints,&infoAddr)))
  {
    fprintf(stderr,"%s\n",gai_strerror(codeError));
    exit(EXIT_FAILURE);
  }

  toFree=infoAddr;
  while((infoAddr!=NULL)&&(infoAddr->ai_family!=AF_INET))
    infoAddr=infoAddr->ai_next;//Tant qu'on a pas trouvé d'adresse en IPv4,on prend la prochaine
  if(infoAddr == NULL)
  {
    fprintf(stderr,"Addresse non correcte, host non trouve\n");
    exit(EXIT_FAILURE);
  }


  //on crée un connexion client vers le serveur en TCP
  server_addr.sin_addr=((struct sockaddr_in *)infoAddr->ai_addr)->sin_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = 0;
  if ((serv = clnttcp_create(&server_addr,PROGNUM, VERSNUM,&sock,10000,10000)) == NULL)
  {
    clnt_pcreateerror("clnttcp_create");
    exit(-1);
  }
  freeaddrinfo(toFree);


  if(serv==NULL){
    printf("Error create client\n");
    exit(0);
  }

  stat = clnt_call(/* host */ serv,
      /* procnum */ PROCNUM_GET_MATRIX,
      /* encodage argument */ (xdrproc_t) xdr_matrix,
      /* argument */ (caddr_t)&mat,
      /* decodage retour */ (xdrproc_t)xdr_void,
      /* retour de la fonction distante */(caddr_t)&res,
      /*timeout*/TIMEOUT);
  int k;
  for (k = 0; k <10; k++) {
    stat = clnt_call(/* host */ serv,
        /* procnum */ PROCNUM_GENETIC,
        /* encodage argument */ (xdrproc_t) xdr_void,
        /* argument */ (caddr_t)pNULL,
        /* decodage retour */ (xdrproc_t)xdr_population,
        /* retour de la fonction distante */(caddr_t)&population,
        /*timeout*/TIMEOUT);

    for (i = 0; i < population->nb_adn; i++) {
      displayDna(screen,population->a[i]);
      printf("test\n");
    }
    SDL_Flip(screen);
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
