#include "Fermant.h"




void bewegung(Ant** ant, Grid** grid, int anzahl, int stat_nf, int stat_wf, int gridg, int swarm){

	float wwertung = 1;
	int laenge_int =3;
	int schneid = 10;
	int r,u,l,d,t;

	for(int spez =0; spez<swarm; spez++){
		ant[spez]->temp_x = ant[spez]->x;
		ant[spez]->temp_y = ant[spez]->y;

		for(int k=0; k<laenge_int; k++){
		r=ant[spez]->rgos(grid,ant[spez], schneid);
		u=ant[spez]->ugos(grid,ant[spez], schneid);
		d=ant[spez]->dgos(grid,ant[spez], schneid);
		l=ant[spez]->lgos(grid,ant[spez], schneid);
		t=r+u+d+l;
		
		if((*ant[spez]).food){

				if(t>stat_wf){
					bewegung_stat(grid,ant[spez],r,u,l,d,wwertung);
				}
				else if(t<=stat_wf){
					bewegung_rand(ant[spez],100);
				}
			}

		else if(!(*ant[spez]).food){

				if(t>stat_nf){
					bewegung_stat(grid,ant[spez],r,u,l,d,wwertung);
				}
				else if(t<=stat_nf){
					bewegung_rand(ant[spez],100);
				}
			}
		edge(ant[spez],gridg);
		}
		ant[spez]->manh_x = 0;
		ant[spez]->manh_y = 0;
	}	
}


void bewegung_rand(Ant* ant, int length_max){


	/*Richtungswahl*/
	if(!ant->time_walk){
		int radius=rand()%length_max+1;
		int ring=rand()%(radius*4);

		ant->time_walk=radius;

		 if(ring<radius){
			 ant->dir_x=radius-ring;
			 ant->dir_y=ring;
		 }
		 else if(ring<2*radius){
			 ant->dir_x=radius-ring;
			 ant->dir_y=2*radius-ring;
		 }
		 else if(ring<3*radius){
			 ant->dir_x=ring-3*radius;
			 ant->dir_y=2*radius-ring;
		 }
		 else if(ring<4*radius){
			 ant->dir_x=ring-3*radius;
			 ant->dir_y=ring-4*radius;
		 }
	}

	/*Gehen*/
	int gx,gy;

	if(ant->dir_x==0)
		gx=0;
	else
		gx = rand()%abs(ant->dir_x)+1;
	if(ant->dir_y==0)
		gy=0;
	else
		gy = rand()%abs(ant->dir_y)+1;

	if(gx>gy){
		if(ant->dir_x>0){
			ant->go_r(ant);
			return;
		}
		else if(ant->dir_x<0){
			ant->go_l(ant);
			return;
		}
	}
	else if(gx<gy){
		if(ant->dir_y>0){
			ant->go_d(ant);
			return;
		}
		else if(ant->dir_y<0){
			ant->go_u(ant);
			return;
		}

	}
	else if(gx==gy){
		int tor = rand()%2;
		if(tor==0){
			if(ant->dir_x>0){
				ant->go_r(ant);
				return;
			}
			else if(ant->dir_x<0){
				ant->go_l(ant);
				return;
			}
		}
		else if(tor==1){
			if(ant->dir_y>0){
				ant->go_d(ant);
				return;
			}
			else if(ant->dir_y<0){
				ant->go_u(ant);
				return;
			}
		}
	}
}


void bewegung_stat(Grid** grid, Ant* ant, float r, float u, float l , float d, float wwertung){

	float wr, wu, wd, wl, rnd, t;

	r = pow(r,wwertung);
	u = pow(u,wwertung);
	l = pow(l,wwertung);
	d = pow(d,wwertung);

	t = r+u+l+d;
	
	wr = r/t;
	wu = u/t+wr;
	wl = l/t+wu;
	wd = d/t+wl;

	rnd = rand();

	if(rnd<wr){
		if(ant->food)
			ant->go_l(ant);
		else
			ant->go_r(ant);
		return;
	}
	else if(rnd<wu){
		if(ant->food)
			ant->go_d(ant);
		else
			ant->go_u(ant);
		return;
	}
	else if(rnd<wl){
		if(ant->food)
			ant->go_r(ant);
		else
			ant->go_l(ant);
		return;
	}
	else if(rnd<wd){
		if(ant->food)
			ant->go_u(ant);
		else
			ant->go_d(ant);
		return;
	}
}

void grider(Ant** ant, Grid** grid, int swarm){

	int x, y, len;
	short walk;

	for(int spez=0; spez<swarm; spez++){
		if((*ant[spez]).food){
			x = (*ant[spez]).x;
			y = (*ant[spez]).y;
			len = (*ant[spez]).length;
			for(int i=0; i<(*ant[spez]).length; i++){
				walk = (*ant[spez]).hist[len-i];
				switch(walk){
				case 1:
					x -= 1;
					grid[y][x].l += 1;
					break;
				case 2:
					y += 1;
					grid[y][x].u;
					break;
				case 3:
					x += 1;
					grid[y][x].r += 1;
					break;
				case 4:
					x -= 1;
					grid[y][x].d += 1;
					break;
				}
			}
		}
		else{
			x = (*ant[spez]).temp_x;
			y = (*ant[spez]).temp_y;
			for(int i=0; i<(*ant[spez]).length; i++){

				walk = (*ant[spez]).hist[i];
				switch(walk){
					case 1:
						grid[y][x].r += 1;
						x += 1;
						break;
					case 2:
						grid[y][x].u += 1;
						y -= 1;
						break;
					case 3:
						grid[y][x].l += 1;
						x -= 1;
						break;
					case 4:
						grid[y][x].d += 1;
						y += 1;
						break;
					}
				}
			}
			ant[spez]->length = 0;
		}
}

void edge(Ant* ant, int gridg){

	if((*ant).x == 1 && (*ant).dir_x<0){
		(*ant).dir_x = -(*ant).dir_x;
	}
	else if((*ant).x == gridg-2 && (*ant).dir_x>0){
		(*ant).dir_x = -(*ant).dir_x;
	}
	if((*ant).y == 1 && (*ant).dir_y<0){
		(*ant).dir_y = -(*ant).dir_y;
	}
	else if((*ant).y == gridg-2 && (*ant).dir_y>0){
		(*ant).dir_y = -(*ant).dir_y;
	}
	
}

void reach(Ant* ant, int food_x, int food_y, int start_x, int start_y, int gridg){
	int rndx,rndy;
	if((*ant).food){


	}
	else{
		if(food_x-gridg/100<(*ant).x && (*ant).x<food_x+gridg/100){
			while((*ant).x != food_x && (*ant).y != food_y){
				
				rndx = rand()%(abs((*ant).x-food_x));
				rndy = rand()%(abs((*ant).y-food_y));
				if(rndx>rndy){
					if((*ant).x>food_x)
						(*ant).go_l(ant);
					else
						(*ant).go_r(ant);
				}
				else if(rndx<rndy){
						if((*ant).y>food_y)
						(*ant).go_u(ant);
					else
						(*ant).go_d(ant);
				}
			}
		}
	}
}
