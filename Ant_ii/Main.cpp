#include<iostream>
#include <time.h>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include "Fermant.h"
#include <fstream>
#include <string>
void manh(int** ant, int swarm, int laenge_intern, float* manhatten);
using namespace std;


const int start_x = 100;
const int start_y = 100;
const int intern = 10;



int main(){

	int stat_nf = 1000;
	int stat_wf = 1000;
	int swarm = 10;
	const int gridg=10;


	srand(time(NULL));
	Grid** grid;
	grid = new Grid*[gridg];
	for(int i=0; i<gridg; i++){
		grid[i] = new Grid[gridg];
	}

	Ant** ant;
	ant = new Ant*[swarm];
	for(int i=0; i<swarm; i++)
		ant[i]=new Ant;





	for(int time=0; time<50; time++){
		cout<<time<<endl;
		bewegung(ant, grid, swarm, stat_nf, stat_wf, gridg, swarm);

		grider(ant, grid, swarm);
	}
	ant[0]->show_coordinates();
	grid[5][5].show_pheromon();
	show_grid(grid);
	getchar();

	return 0;

};
