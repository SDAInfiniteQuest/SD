
displacement_t create_displacement(point start,char dir,int length){
	displacement_t d=malloc(sizeof(struct str_displacement));
	d->start=(point)start;
	d->dir=dir;
	d->length=length;
	
	compute_displacement(d,dir,length);
	
	return d;
}

void compute_displacement(displacement_t dis,char dir,int length){
	point start=dis->start;
	point* end=&dis->end;
	
	if(dir==0){
		end->x=start.x;
		end->y=start.y+length;
	}
	else if(dir==1){
		end->x=start.x+length;
		end->y=start.y+length;
	}
	else if(dir==2){
		end->x=start.x+length;
		end->y=start.y;
	}
	else if(dir==3){
		end->x=start.x+length;
		end->y=start.y-length;
	}
	else if(dir==4){
		end->x=start.x;
		end->y=start.y-length;
	}
	else if(dir==5){
		end->x=start.x-length;
		end->y=start.y-length;
	}
	else if(dir==6){
		end->x=start.x-length;
		end->y=start.y;
	}
	else if(dir==7){
		end->x=start.x-length;
		end->y=start.y+length;
	}
}
adn_t create_ADN(){
	adn_t new=malloc(sizeof(struct str_adn));
	new->d=malloc(sizeof(struct str_displacement)*100);
	point start;
	start.x=0;
	start.y=0;
	d[0]=create_displacement(start,start,0,0);
	
	new->size=100;
	new->nb_displacement=1;
	return new;
}

//ajout uniquement des deplacement juste
bool add_displacement(adn_t ind,char dir,int lenght,matrix_t m){
	displacement_t new=create_displacement(ind->d[ind->nb_displacement-1]->end,dir,length);
	int size_adn=ind->size;
	int nb_displacement=ind->nb_displacement;

	if(test_displacement(new,m)){
		if(size-nb_displacement>0){
			ind->d[nb_displacement]=new;
			ind->nb_displacement++;
		}
		else{
			ind->d=realloc(ind->d,(size+50)*(sizeof(struct str_displacement)));
			ind->d[nb_displacement]=new;
			ind->nb_displacement++;
			ind->size+=50;
		}
		return TRUE;
	}
	return FALSE;
}
