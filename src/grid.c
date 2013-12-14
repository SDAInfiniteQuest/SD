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

int distance(point_t p1,point_t p2){
	return sqrt((p1->x+p2->x)*(p1->x+p2->x)+(p1->y+p2->y)*(p1->y+p2->y));
}

void setPoint(matrix_t m,int x,int y){
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

	m->m[x*y_max+y]=1;
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
		
		if(m>0){
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
	
	//a randomiser par la suite
	start.x=0;
	start.y=height/2;

	//a randomiser par la suite
	start.x=length;
	start.y=height/2;
	
	while(i<nb_circle){
		current.center.x=rand()%length;
		current.center.y=rand()%length;
		current.radius=1+rand()%(min(length,height)/2);

		for (j=0 ; j < i; j++) {
			if (distance(&current.center,&obs[i].center)<=current.radius+obs[i].radius+15) {
				break;
			}
			else if(distance(&current.center,&start)<=current.radius+15){
				break;
			}
			else if(distance(&current.center,&end)<=current.radius+15){
				break;
			}
			else{
				obs[i]=(circle)current;
				i++;
			}
		}
	}

	circleToDraw=malloc(nb_circle*sizeof(struct str_circle));
	
	//#pragma omp parallel for
	for (i = 0; i < nb_circle; i++) {
		circle_in_matrix(m,&obs[i]);
		circleToDraw[i]=obs[i];
	}

}


void printMat(matrix_t m) {
	int i;
	int j;
	for(i=0;i<m->nb_columns;i++) {
		for(j=0;j<m->nb_rows;j++) {
			printf("%c",getPoint(m,i,j));
		}
		printf("\n");
	}
}


bool test_displacement(displacement_t d,matrix_t m){
	int startX=d->start.x;
	int startY=d->start.y;
	int length=d-.length;
  int i;

	if(d->dir==0){
		for(i=0;i<length;i++){
			if(m->[startX][startY+i]==1)
				return FALSE;
		}
	}
	else if(d_>dir==1){
		for(i=0;i<length;i++){
			if(m->[startX+i][startY+i]==1)
				return FALSE;
		}
	}
	else if(d_>dir==2){
		for(i=0;i<length;i++){
			if(m->[startX+i][startY]==1)
				return FALSE;
		}
	}
	else if(d_>dir==3){
		for(i=0;i<length;i++){
			if(m->[startX+i][startY-i]==1)
				return FALSE;
		}
	}
	else if(d_>dir==4){
		for(i=0;i<length;i++){
			if(m->[startX][startY-i]==1)
				return FALSE;
		}
	}
	else if(d_>dir==5){
		for(i=0;i<length;i++){
			if(m->[startX-i][startY-i]==1)
				return FALSE;
		}
	}
	else if(d_>dir==6){
		for(i=0;i<length;i++){
			if(m->[startX-i][startY]==1)
				return FALSE;
		}
	}
	else if(d_>dir==7){
		for(i=0;i<length;i++){
			if(m->[startX-i][startY+i]==1)
				return FALSE;
		}
	}
	return TRUE;
}

bool test_ADN(adn_t ind,matrix_t m){
	int i;
  for (i = 0; i < ind->nb_displacement; i++) {
		if(!test_displacement(&ind->displace[i],m))
			return FALSE;
	}
	return TRUE;
}
