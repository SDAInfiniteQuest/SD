#include "grid.h"

bool outOfBound(int x,int y) {
	if(x<0 || y<0 || x>GRID_SIZE || y> GRID_SIZE) return TRUE;
	else return FALSE;
}

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
	return sqrt((double)((p1->x-p2->x)*(p1->x-p2->x)+(p1->y-p2->y)*(p1->y-p2->y)));
}

matrix_t setPoint(matrix_t m,int x,int y){
	int x_max=m->nb_columns;
	int y_max=m->nb_rows;

	if(x>x_max)
		x=x_max;
	if(x<0)
		x=0;

	if(y>y_max)
		y=y_max;
	if(y<0)
		y=0;

	m->m[y*m->nb_columns+x]=1;
	return m;
}

int getPoint(matrix_t m,int x,int y) {
	if(outOfBound(x,y)==TRUE) {
		fprintf(stderr, "erreur getPoint: x=%d, y=%d sont invalides\n", x, y);
		exit(EXIT_FAILURE);
	}
	return m->m[y*m->nb_columns+x];
}

matrix_t circle_in_matrix(matrix_t m, circle_t c){
	int x=0;
	int r=c->radius;
	int y=r;
	int d=r-1;
	//int midPoint=5-4*y;
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

		if (d >= 2*x)
		{
			d -= 2*x + 1;
			x ++;
		}
		else if (d < 2 * (r-y))
		{
			d += 2*y - 1;
			y --;
		}
		else
		{
			d += 2*(y - x - 1);
			y --;
			x ++;
		}

		/*if(midPoint>0){
			y--;
			midPoint-=8*y;
		}
		x++;
		midPoint+=8*x+4;*/
	}

	return m;
}



//Allocation de circleToDraw dans create_world
void create_world(matrix_t m,circle_t circleToDraw){
	int nb_circle=1000;
	int i=0,j=0,k=0,l=0;
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
  
  i=0;
	//a randomiser par la suite
	end.x=length;
	end.y=height/2;
  
  m->end=end;
  m->start=start;

	matrix_t tmp=m;
	circleToDraw=malloc(nb_circle*sizeof(struct str_circle));

	while(i<nb_circle){
		current.center.x=rand()%length;
		current.center.y=rand()%height;
		current.radius=6+rand()%(min(length,height)/8);
		//printf("(%d,%d,%d)\n",current.center.x,current.center.y,current.radius);

		if((distance(&current.center,&start)<=(current.radius+15)) || (distance(&current.center,&end)<=(current.radius+15))) 
			not_possible=TRUE;

		if(i>0)
			for (j=0 ; j < k && not_possible==FALSE; j++) 
				if (distance(&current.center,&obs[j].center)<=current.radius+obs[j].radius+5) 
					not_possible=TRUE;

		if (not_possible==FALSE) {
			obs[k]=current;
      
			circle_in_matrix(tmp,&obs[k]);
      for (l = 0; l < 6; l++) {
        current.radius--;
			  circle_in_matrix(tmp,&current);
      }
			circle_in_matrix(tmp,&obs[k]);
			circleToDraw[k]=obs[k];
			k++;
		}
		i++;

		not_possible=FALSE;
	}
}


void printMat(matrix_t m) {
	int i;
	int j;
	for(i=0;i<m->nb_rows;i++) {
		for(j=0;j<m->nb_columns;j++) {
			if(getPoint(m,i,j)!=0) printf("(%d,%d,%c)",i,j,getPoint(m,i,j));
			//else printf("%c",'.');
		}
		printf("\n");
	}
}


