#include "Fermant.h"

Grid::Grid(void){

	u=0;
	r=0;
	l=0;
	d=0;

}

Grid::~Grid(void)
{

}

void Grid::show_pheromon(){
	t=u+r+d+l;
	cout<<"up: "<<u<<endl<<"down: "<<d<<endl<<"right: "<<r<<endl<<"left: "<<l<<endl<<"total: "<<t<<endl;
}

void show_grid(Grid** grid){
	int gridg = 10;
	for(int i=0; i<gridg; i++){
		for(int j=0; j<gridg; j++){
			cout<<grid[i][j].r+grid[i][j].l+grid[i][j].d+grid[i][j].u<<"\t";
		}
		cout<<endl;
	}

}

