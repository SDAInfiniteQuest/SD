
int main (void) {
  bool_t stat;

  stat = registerrpc(/* prognum */ PROGNUM,
      /* versnum */ VERSNUM,
      /* procnum */ PROCNUM_MULT,
      /* pointeur sur fonction */  multiplication,
      /* decodage arguments */ (xdrproc_t)xdr_matrix_couple,
      /* encodage retour de fonction */ (xdrproc_t)xdr_matrix);

  stat = registerrpc(/* prognum */ PROGNUM,
      /* versnum */ VERSNUM,
      /* procnum */ PROCNUM_ADD,
      /* pointeur sur fonction */  addition,
      /* decodage arguments */ (xdrproc_t)xdr_matrix_couple,
      /* encodage retour de fonction */ (xdrproc_t)xdr_matrix);

  if (stat != 0) {
    fprintf(stderr,"Echec de l'enregistrement\n");
    exit(1);
  }
  svc_run(); /* le serveur est en attente de clients eventuels */
  return(0); /* on y passe jamais ! */
}


