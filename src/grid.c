#include "grid.h"

matrix_t init_matrix(int height,int length){
  matrix_t mat;
  mat=malloc(sizeof(struct str_matrix));
  mat->m=calloc(height*length,sizeof(char));
  mat->nb_rows=height;
  mat->nb_columns=length;

  return mat;
}

int min(int a,int b){
  if (a>=b)
    return b;
  else
    return a;
}

double distance(point_t p1,point_t p2){
  return sqrt((double)((p1->x+p2->x)*(p1->x+p2->x)+(p1->y+p2->y)*(p1->y+p2->y)));
}

matrix_t setPoint(matrix_t m,int x,int y){
  int x_max=m->nb_rows;
  int y_max=m->nb_columns;

  if(x>x_max)
    x=x_max;
  if(x<0)
    x=0;

  if(y>y_max)
    y=y_max;
  if(y<0)
    y=0;

  m->m[x*m->nb_columns+y]=1;
  return m;
}

int getPoint(matrix_t m,int x,int y) {
  return m->m[x*m->nb_columns+y];
}

matrix_t circle_in_matrix(matrix_t m, circle_t c){
  int x=0,y=c->radius;
  int midPoint=5-4*y;
  int x_center=c->center.x;
  int y_center=c->center.y;
  while(x<=y){
    setPoint(m,x+x_center, y+y_center ) ;
    setPoint(m,y+x_center, x+y_center ) ;
    setPoint(m,-x+x_center, y+y_center ) ;
    setPoint(m,-y+x_center, x+y_center ) ;
    setPoint(m,x+x_center, -y+y_center ) ;
    setPoint(m,y+x_center, -x+y_center ) ;
    setPoint(m,-x+x_center, -y+y_center ) ;
    setPoint(m,-y+x_center, -x+y_center ) ;

    if(midPoint>0){
      y--;
      midPoint-=-8*y;
    }
    x++;
    midPoint+=8*x+4;
  }

  return m;
}



//Allocation de circleToDraw dans create_world
void create_world(matrix_t m,circle_t circleToDraw){
  int nb_circle=1+rand()%10;
  int i=0,j=0;
  circle obs[nb_circle];
  circle current;
  int length=m->nb_columns;
  int height=m->nb_rows;
  point start;
  point end;
  bool not_possible=FALSE;	
  //a randomiser par la suite
  start.x=0;
  start.y=height/2;

  //a randomiser par la suite
  end.x=length;
  end.y=height/2;
  m->end=end;
  m->start=start;
  matrix_t tmp=m;

  while(i<nb_circle){
    current.center.x=rand()%length;
    current.center.y=rand()%length;
    current.radius=1+rand()%(min(length,height)/2);

    for (j=0 ; j <= i; j++) {
      if (distance(&current.center,&obs[j].center)<=current.radius+obs[j].radius+15) {
        not_possible=TRUE;
        break;
      }
      else if(distance(&current.center,&start)<=current.radius+15){
        not_possible=TRUE;
        break;
      }
      else if(distance(&current.center,&end)<=current.radius+15){
        not_possible=TRUE;
        break;
      }
    }
    
    if (!not_possible) {
      obs[i]=current;
      i++;
    }
    not_possible=FALSE;

  }
  circleToDraw=malloc(nb_circle*sizeof(struct str_circle));

  //#pragma omp parallel for
  for (i = 0; i < nb_circle; i++) {
    circle_in_matrix(tmp,&obs[i]);
    circleToDraw[i]=obs[i];
  }
  printf("Trouve un monde\n");
}


void printMat(matrix_t m) {
  int i;
  int j;
  for(i=0;i<m->nb_rows;i++) {
    for(j=0;j<m->nb_columns;j++) {
      if(getPoint(m,i,j)==0) printf("%c",'#');
      else printf("%c",'.');
    }
    printf("\n");
  }
}


