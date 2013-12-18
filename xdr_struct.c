#include "include.h"


bool_t xdr_matrix(XDR *xdrs,matrix_t* e){
  int i,j;
  int length;
  int height;
  matrix_t m;

  if (xdrs->x_op==XDR_ENCODE){
    m=(*e);
    length=m->nb_columns;
    height=m->nb_rows;
    if(xdr_int(xdrs,&length)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&height)!=TRUE)
      return FALSE;
  }else if (xdrs->x_op==XDR_DECODE){
    if(xdr_int(xdrs,&length)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&height)!=TRUE)
      return FALSE;
    printf("%d\n",length);
    printf("%d\n",height);
    m=init_matrix(dim);
    m->dim=dim;
    (*e)=m;
  }

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++) {

      if(xdr_float(xdrs,&(m->mat[i][j]))!=TRUE)
        return FALSE;
    }
  }
  return TRUE;
}


}
