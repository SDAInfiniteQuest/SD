#include "include.h"
int main (int argc, char **argv) {
  char *host = argv[1];
  enum clnt_stat stat;

  srand(time(NULL));

  if (argc!=2) {
    printf("Usage :%s [IP serveur]\n",argv[0]);
  }


//
//  if(choix=='m'){
//    stat = callrpc(/* host */ host,
//        /* prognum */ PROGNUM,
//        /* versnum */ VERSNUM,
//        /* procnum */ PROCNUM_MULT,
//        /* encodage argument */ (xdrproc_t) xdr_matrix_couple,
//        /* argument */ (char *)&donnee,
//        /* decodage retour */ (xdrproc_t)xdr_matrix,
//        /* retour de la fonction distante */(char *)&res);
//  }
//*/
//  else if(choix=='a'){
//    stat = callrpc(/* host */ host,
//        /* prognum */ PROGNUM,
//        /* versnum */ VERSNUM,
//        /* procnum */ PROCNUM_ADD,
//        /* encodage argument */ (xdrproc_t) xdr_matrix_couple,
//        /* argument */ (char *)&donnee,
//        /* decodage retour */ (xdrproc_t)xdr_matrix,
//        /* retour de la fonction distante */(char *)&res);
//  }
  
  if (stat != RPC_SUCCESS) { 
    fprintf(stderr, "Echec de l'appel distant\n");
    clnt_perrno(stat);      fprintf(stderr, "\n");
  }
	else{
  }

  return(0);
}
