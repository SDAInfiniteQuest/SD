#include "include.h"
#include "xdr_struct.h"


bool_t xdr_matrix(XDR *xdrs,matrix_t* e){
  int i,j;
  int length;
  int height;
  matrix_t m;

  if (xdrs->x_op==XDR_ENCODE){
    m=(*e);
    length=m->nb_columns;
    height=m->nb_rows;
    printf("test\n");
    if(xdr_int(xdrs,&length)!=TRUE)
      return FALSE;
    printf("test\n");
    if(xdr_int(xdrs,&height)!=TRUE)
      return FALSE;
  }else if (xdrs->x_op==XDR_DECODE){
    if(xdr_int(xdrs,&length)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&height)!=TRUE)
      return FALSE;
    printf("%d\n",length);
    printf("%d\n",height);
    m=init_matrix(length,height);
    (*e)=m;
  }

  for (i = 0; i < height; i++) {
    for (j = 0; j < length; j++) {

      if(xdr_char(xdrs,&(m->m[j*length+i]))!=TRUE){
        printf("%d %d\n",i,j);
        return FALSE;
      }
    }
  }
  return TRUE;
}

bool_t xdr_point(XDR* xdrs,point* p){
  if(xdr_int(xdrs,&((*p).x))!=TRUE)
    return FALSE;
  if(xdr_int(xdrs,&((*p).y))!=TRUE)
    return FALSE;

  return TRUE;
}

bool_t xdr_displacement(XDR *xdrs, displacement_t* d) {
  displacement_t tmp;
  int length;
  char dir;
  point start,end;

  if (xdrs->x_op==XDR_ENCODE){
    tmp=(*d);

    if(xdr_point(xdrs,&tmp->start)!=TRUE)
      return FALSE;
    if(xdr_char(xdrs,&tmp->dir)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&tmp->length)!=TRUE)
      return FALSE;

  }else if (xdrs->x_op==XDR_DECODE){
    
    if(xdr_point(xdrs,&start)!=TRUE)
      return FALSE;
    if(xdr_char(xdrs,&dir)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&length)!=TRUE)
      return FALSE;
     
   tmp=create_displacement(start,dir,length);
   (*d)=tmp;
  }

  return TRUE;
}


bool_t xdr_adn(XDR *xdrs,adn_t* ind) {
  adn_t tmp;
  int size;
  int nb_displacement;
  double path_length;
  double note;
  int i;
  
  if (xdrs->x_op==XDR_ENCODE){
    tmp=(*ind);

    if(xdr_int(xdrs,&tmp->nb_displacement)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&tmp->size)!=TRUE)
      return FALSE;
    if(xdr_double(xdrs,&tmp->path_length)!=TRUE)
      return FALSE;
    if(xdr_double(xdrs,&tmp->note)!=TRUE)
      return FALSE;
  

  }else if (xdrs->x_op==XDR_DECODE){
    
    if(xdr_int(xdrs,&nb_displacement)!=TRUE)
      return FALSE;
    if(xdr_int(xdrs,&size)!=TRUE)
      return FALSE;
    if(xdr_double(xdrs,&path_length)!=TRUE)
      return FALSE;
    if(xdr_double(xdrs,&note)!=TRUE)
      return FALSE;
     
    tmp=alloc_adn(nb_displacement,size,path_length,note);
   (*ind)=tmp;
  }

  for (i = 0; i < tmp->nb_displacement; i++) {
    if(xdr_displacement(xdrs,&tmp->d[i])!=TRUE)
      return FALSE;
  }

  return TRUE;
}

//on y arrive
bool_t xdr_population(XDR *xdrs,population_t* pop) {
  population_t tmp;
  int nb_adn;
  int i;

  if (xdrs->x_op==XDR_ENCODE){
    tmp=(*pop);

    if(xdr_int(xdrs,&tmp->nb_adn)!=TRUE)
      return FALSE;

  }else if (xdrs->x_op==XDR_DECODE){
    
    if(xdr_int(xdrs,&nb_adn)!=TRUE)
      return FALSE;
     
    tmp=create_population(POPULATION_SIZE);
    tmp->nb_adn=nb_adn;
   (*pop)=tmp;
  }

  for (i = 0; i < tmp->nb_adn; i++) {
    if(xdr_adn(xdrs,&tmp->a[i]));  
  }

  return TRUE;
}


