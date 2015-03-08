#include "Fermant.h"

Ant::Ant(void)
{
	x = 5;
	y = 5;
	temp_x = 5;
	temp_y = 5;
	dir_x = 0;
	dir_y = 0;
	time_walk= 0;
	time_reach = 0;
	food = false;
	length = 0;
	manh_x = 0;
	manh_y = 0;

}

Ant::~Ant(void)
{

}

void Ant::show_coordinates(){

	cout<<"X-Value: "<<x<<endl<<"Y-Value: "<<y<<endl;

};


int Ant::rgos(Grid** grid, Ant* ant, int schneid){

	int r = 0;
	int x = ant->x;
	int y = ant->y;
	
	if(ant->food){
		r += schneid*grid[y][x-1].r;
		for(int i=-1; i<2; i++){
			r += grid[y+i][x-2].r;
		}
	}
	else{
		r += schneid*grid[y][x].r;
		for(int i=-1; i<2; i++){
			r += grid[y+i][x+1].r;
		}
	}
	return r;
}

int Ant::ugos(Grid** grid, Ant* ant, int schneid){

	int u = 0;
	int x = ant->x;
	int y = ant->y;

	if(ant->food){
		u += schneid*grid[y+1][x].u;
		for(int i=-1; i<2; i++){
			u += grid[y+2][x+i].u;
		}
	}
	else{
		u += schneid*grid[y][x].u;
		for(int i=-1;i<2;i++){
			u += grid[y-1][x+i].u;
		}
	}
	return u;
}

int Ant::lgos(Grid** grid, Ant* ant, int schneid){

	int l = 0;
	int x = ant->x;
	int y = ant->y;

	if(ant->food){
		l += schneid*grid[y][x+1].l;
		for(int i=-1; i<2; i++){
			l += grid[y+i][x+2].l;
		}
	}
	else{
		l += schneid*grid[y][x].l;
		for(int i=-1; i<2; i++){
			l += grid[y+i][x-1].l;
		}
	}
	return l;
}

int Ant::dgos(Grid** grid, Ant* ant, int schneid){

	int d = 0;
	int x = ant->x;
	int y = ant->y;

	if(ant->food){
		d+=schneid*grid[y-1][x].d;
		for(int i=-1;i<2;i++){
			d+=grid[y-2][x+i].d;
		}
	}
	else{
		d += schneid*grid[y][x].d;
		for(int i=-1; i<2; i++){
			d += grid[y+1][x+i].d;
		}
	}
	return d;
}

void Ant::go_r(Ant* ant){
	ant->x += 1;
	ant->hist[ant->length] = 1;
	ant->length += 1;
	ant->manh_x += 1;
}

void Ant::go_u(Ant* ant){
	ant->y -= 1;
	ant->hist[ant->length] = 2;
	ant->length += 1;
	ant->manh_y -= 1;
}

void Ant::go_l(Ant* ant){
	ant->x -= 1;
	ant->hist[ant->length] = 3;
	ant->length += 1;
	ant->manh_x -= 1;
}

void Ant::go_d(Ant* ant){
	ant->y += 1;
	ant->hist[ant->length] = 4;
	ant->length += 1;
	ant->manh_y += 1;
}

int Ant::pheromone(Ant* ant, int abnahme, int time){
	int phero;

	if(ant->food){
		phero = (ant->pheromone_f-(time-ant->time_reach))/abnahme;
	}
	else{
		phero = (ant->pheromone_g-(time-ant->time_reach))/abnahme;
	}

	if(phero<0)
		phero=0;

	return phero;
}
