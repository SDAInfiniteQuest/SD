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

  if(codeError=getaddrinfo(host,NULL,&hints,&infoAddr))
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

  scanf("%c",&choix);
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
    stat = clnt_call(/* host */ serv,
        /* procnum */ PROCNUM_DISPLAY_ADN,
        /* encodage argument */ (xdrproc_t) xdr_adn,
        /* argument */ (caddr_t)&old->a[0],
        /* decodage retour */ (xdrproc_t)xdr_void,
        /* retour de la fonction distante */(caddr_t)&res,
        /*timeout*/TIMEOUT);
    displayDna(screen,old->a[0]);
  }  
  else if(choix=='3'){
    stat = clnt_call(/* host */ serv,
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
