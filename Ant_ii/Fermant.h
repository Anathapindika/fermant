#pragma once
#include <iostream>
using namespace std;

//void bewegung(Ant*, Grid**, int, int);


class Ant
{
private:
	int x;							//X-Coordinate
	int y;							//Y-Coordinate
	int temp_x;						//Pheromone X
	int temp_y;						//Pheromone	Y
	int dir_x;						//X-Direction (In Case of Gridpoint without Pheromone)
	int dir_y;						//Y-Direction (In Case of Gridpoint without Pheromone)
	bool food;						//Food or No Food
	int time_reach;					//Time since reaching Food or Goal
	int time_walk;					//Time since choosing Direction
	short hist[13];					//Walked Steps
	short length;					//How Many Walked Steps since Timestep
	short manh_x;
	short manh_y;
	short pheromone_f;
	short pheromone_g;

public:
	void show_coordinates();
	Ant(void);
	~Ant(void);
	friend class Grid;
	friend void bewegung(Ant** ant, Grid** grid, int anzahl, int stat_nf, int stat_wf, int gridg, int swarm);
	friend void bewegung_rand(Ant* ant, int length_max);
	friend void bewegung_stat(Grid** grid, Ant* ant, float r, float u, float l , float d, float wwertung);
	friend void reach(Ant* ant, int food_x, int food_y, int start_x, int start_y, int gridg);
	friend void grider(Ant** ant, Grid** grid, int swarm);
	friend void edge(Ant* ant, int gridg);
	int rgos(Grid**, Ant*, int schneid);
	int lgos(Grid**, Ant*, int schneid);
	int dgos(Grid**, Ant*, int schneid);
	int ugos(Grid**, Ant*, int schneid);
	int pheromone(Ant*, int abnahme, int time);
	void go_r(Ant* ant);
	void go_u(Ant* ant);
	void go_d(Ant* ant);
	void go_l(Ant* ant);

};


class Grid
{
private:

	int u;
	int d;
	int l;
	int r;
	int t;
	

public:
	void show_pheromon();
	friend void show_grid(Grid**);
	Grid(void);
	~Grid(void);
	friend void bewegung(Ant* ant, Grid** grid, int anzahl, int stat_nf, int stat_wf, int gridg, int swarm);
	friend void bewegung_stat(Grid** grid, Ant* ant, float r, float u, float l , float d, float wwertung);
	friend void grider(Ant** ant, Grid** grid, int swarm);
	friend int Ant::rgos(Grid**, Ant*, int);
	friend int Ant::lgos(Grid**, Ant*, int);
	friend int Ant::dgos(Grid**, Ant*, int);
	friend int Ant::ugos(Grid**, Ant*, int);
};

