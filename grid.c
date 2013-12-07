
matrix_t init_matrix(int height,int length){
	matrix_t mat;
	mat=malloc(sizeof(struct str_matrix));
	mat->m=calloc(height*length,sizeof(char));
	mat->nb_rows=height;
	mat->nb_columns=length;
}

int min(int a,int b){
	if (a>=b)
		return b;
	else
		return a;
}

int distance(point_t p1,point_t p2){
	return sqrt((p1.x+p2.x)*(p1.x+p2.x)+(p1.y+p2.y)*(p1.y+p2.y));
}

void setPoint(matrix_m m,int x,int y){
	int x_max=m->length;
	int y_max=m->height;

	if(x>x_max)
		x=x_max;
	if(x<0)
		x=0;

	if(y>y_max)
		y=y_max;
	if(y<0)
		y=0;

	m->mat[x][y]=1;
}

void circle_in_matrix(matrix_t m, circle_t c){
	int x=0,y=c->radius;
	int m=5-4*c->radius;
	int x_center=c_>center.x;
	int y_center=c_>center.y;
	while(x<=y){
		setPoint(m,x+x_centre, y+y_centre ) ;
		setPoint(m,y+x_centre, x+y_centre ) ;
		setPoint(m,-x+x_centre, y+y_centre ) ;
		setPoint(m,-y+x_centre, x+y_centre ) ;
		setPoint(m,x+x_centre, -y+y_centre ) ;
		setPoint(m,y+x_centre, -x+y_centre ) ;
		setPoint(m,-x+x_centre, -y+y_centre ) ;
		setPoint(m,-y+x_centre, -x+y_centre ) ;
		
		if(m>0){
			y--;
			m-=-8*y;
		}
		x++;
		m+=8*x+4;
	}
}




void create_world(matrix_t m){
	int nb_circle=1+rand()%10;
	int i=0;
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
		current.radius=1+rand()%(min(lenght,height)/2);

		for (j=0 ; j < i; j++) {
			if (distance(&current.center,&obs[i].center)<=current.radius+obs[i].radius+15) {
				break;
			}
			else if(distance(&current.center,&start)<=current.radius+15){
				break;
			}
			else if(distance(&current.center,&end)<=current.radius+15){
				break;
			else{
				obs[i]=(circle)current;
				i++;
			}
		}
	}

	for (i = 0; i < nb_circle; i++) {
		circle_in_matrix(m,&obs[i]);
	}
}

bool test_displacement(displacement_t d,matrix_t m){
	int startX=d->start.x;
	int startY=d->start.y;
	int length=d-.length;

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
	for (i = 0; i < ind->nb_displacement; i++) {
		if(!test_displacement(&ind->displace[i],m))
			return FALSE;
	}
	return TRUE;
}
