#include<iostream>
#include <time.h>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include "bewegung.h"
#include "grider.h"
//#include "vereinigung.h"
#include <fstream>

void bewegung(int** ant, int**grid, int** r, int** u, int** l, int** d, int swarm, int gridg, int mut);
void grider(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int gridg);
void reach(int** ant, int swarm, int start_x, int start_y, int food_x, int food_y, int mut, int* gefunden);

using namespace std;

int main(){
	srand((unsigned)time(NULL)); //seed initialisierung für rand() funktion


// Anfangsbedingungen
	int iterationen=10000;
	int swarm=30000;
	int gridg=48;
	int start_x=20;
	int start_y=20;
	int food_x=31;
	int food_y=31;
	float mut=0;
	float random;
	int gefunden=0;
	int* p_gefunden=&gefunden;
	random = rand()/(float)(RAND_MAX);
	int randdi = rand();
//----------------------------------------------------
// Initialisierung für die Zeiger auf die Felder

	int** ant;										// ant bezeichnet eine nxm Matrix, wobei die Spaltenzahl 
	ant = new int*[4];								//eine Information für spezifische Koordinaten darstellt, 
	for(int i=0;i<4;++i)							//die Zeilenzahl die einzelnen Ants
		ant[i]= new int[swarm];
			
	for(int j=0;j<swarm;j++){						//Ursprungskoordinaten (hälfte der gridigrösse) füllen bzw.
			ant[0][j]=(start_x);					//die dritte Koordinate (welche Information über bewegungsrichtung
			ant[1][j]=(start_y);					//preis gibt) mit Nullen füllen.
			ant[2][j]=0;
			ant[3][j]=0;
		}

	int** grid;										//initialisierung des Grids - ein Feld, welches zählt,
	grid = new int*[gridg];							//wo sich Ants befinden
	for(int i=0;i<gridg;i++)
		grid[i]=new int[gridg];
	for(int i=0;i<gridg;i++)						//Mit nullen füllen
		for(int j=0;j<gridg;j++)
			grid[i][j]=0;

	int** u;										//initialisierung des Up-Feldes - ein Feld, welches nur die
	u = new int*[gridg];							//Bewegungsrichtung pro Gridpunkt, nach oben zählt
	for(int i=0;i<gridg;i++)
		u[i]=new int[gridg];
	for(int i=0;i<gridg;i++)						//Mit nullen füllen
		for(int j=0;j<gridg;j++)
			u[i][j]=0;

	int** d;										//initialisierung des Down-Feldes - Analog zu Up
	d = new int*[gridg];							
	for(int i=0;i<(gridg);i++)
		d[i]=new int[gridg];
	for(int i=0;i<gridg;++i){						//Mit nullen füllen
		for(int j=0;j<gridg;++j)
			d[i][j]=0;}

	int** r;										//initialisierung des Right-Feldes - Analog zu Up
	r = new int*[gridg];							
	for(int i=0;i<(gridg);i++)
		r[i]=new int[gridg];
	for(int i=0;i<gridg;++i){						//Mit nullen füllen
		for(int j=0;j<gridg;++j)
			r[i][j]=0;}

	int** l;										//initialisierung des Left-Feldes - Analog zu Up
	l = new int*[gridg];							
	for(int i=0;i<(gridg);i++)
		l[i]=new int[gridg];
	for(int i=0;i<gridg;++i){						//Mit nullen füllen
		for(int j=0;j<gridg;++j)
			l[i][j]=0;}



//-----------

/*
for(int t=0;t<=iterationen;t++){
	/*
	for(int g=0;g<=swarm;g++){
		if(ant[3][g]==0){
		

			for(int i=0;i<swarm;i++){
				if(grid[ant[1][i]][ant[0][i]]==0){			//Übergabe an Bewegungsfunktionen
					bewegung1(ant,i);
				}
			
			else if(grid[ant[1][i]][ant[0][i]]!=0){
				bewegung2(ant,u,r,d,l,grid,i,mut);
				}
			}
			for(int i=0;i<swarm;i++){
				grider1(ant,u,r,d,l,grid,i);				//Übergabe an Zählfunktion
			}
			for(int i=0;i<swarm;i++){
				karte(ant,i,gridg);								//Übergabe an Funktion, welche die Ants auf einer geschlossenen Karte behält
			}
			for(int i=0;i<swarm;i++){
				food(ant,i,food_x,food_y);
			}
			//for(int i=0;i<=swarm;i++){
			//	testing(ant,grid,i,gridg);

			}
			
		else if(ant[3][g]==1){
			for(int i=0;i<swarm;i++){
				bewegung3(ant,r,u,l,d,i, gridg);
			}
			for(int i=0;i<swarm;i++){
				grider2(ant,u, r, d, l, grid, i);
			}
			for(int i=0;i<swarm;i++){
				karte(ant,i,gridg);	
			}
			for(int i=0;i<swarm;i++){
				goal(ant,i,start_x,start_y);
			}
		
		}
		else if(ant[3][g]==2){
			cout<<"sehr sehr gut"<<endl;
			for(int i=0;i<swarm;i++){
				neustart(ant,i);								//Übergabe an Funktion, welche die Ants auf einer geschlossenen Karte behält
			}
	
		}
	}
}
//}
/*
for(int o=0;o<1;o++){
	for(int i=0;i<swarm;i++){
		pseudo(ant,i, gridg);
	}
	for(int i=0;i<=swarm;i++){
				grider(ant,u,r,d,l,grid,i);				//Übergabe an Zählfunktion
			}
			for(int i=0;i<=swarm;i++){
				karte(ant,i,gridg);								//Übergabe an Funktion, welche die Ants auf einer geschlossenen Karte behält
			}
}
*/


//-----------------------------------------------------------------------------------------
//Speichern

for(int t=0;t<iterationen;t++){
	for(int i=0;i<swarm;i++){
		bewegung(ant,grid,r,u,l,d,i,gridg,mut);
	}
	for(int i=0;i<swarm;i++){
		grider(ant,u,r,d,l,grid,i, gridg);
	}
	for(int i=0;i<swarm;i++){
		karte(ant,i,gridg);
	}
	for(int i=0;i<swarm;i++){
		reach(ant, i, start_x, start_y, food_x, food_y, mut, p_gefunden);
	}
	if(t==200 || t==400 || t==600){
		cout<<"t; "<<t<<endl;
		for(int i=0;i<swarm;i++){
			hunger(ant,grid,r,u,l,d,i,start_x,start_y);
		}
	}
	//cout<<"gefunden; "<<gefunden<<endl;
}


	ofstream feld;
 	feld.open ("feld.dat");
	/*fermant <<"p1"<<"\t"<<"q1"<<"\t"<<"p2"<<"\t"<<"q2"<<endl;
	for(int i=0;i<gridg;++i){
		for(int k=0;k<gridg;++k){
 		fermant <<grid[k][i]<<"\t";
		}
	}	fermant <<endl;
 	fermant.close();
	*/
	/*
	fermant<<beweg1<<"\t"<<beweg2<<endl;
	for(int i=0;i<swarm;i++){
		fermant<<ant[0][i]<<"\t"<<ant[1][i]<<"\t"<<ant[2][i]<<endl;
	}*/
	for(int i=0;i<gridg;i++){
		for(int k=0;k<gridg;k++){
			feld<<grid[i][k]<<"\t";
		}
		feld<<endl;
	}
	feld.close();

	ofstream reach;
	reach.open("reach.dat");
	reach<<start_x<<"\t"<<start_y<<"\t"<<food_x<<"\t"<<food_y<<"\t"<<gridg<<endl;
	reach.close();

	ofstream rechts;
 	rechts.open ("rechts.dat");
	for(int i=0;i<gridg;i++){
		for(int k=0;k<gridg;k++){
			rechts<<r[i][k]<<"\t";
		}
		rechts<<endl;
	}

	ofstream links;
 	links.open ("links.dat");
	for(int i=0;i<gridg;i++){
		for(int k=0;k<gridg;k++){
			links<<l[i][k]<<"\t";
		}
		links<<endl;
	}

ofstream up;
 	up.open ("up.dat");
	for(int i=0;i<gridg;i++){
		for(int k=0;k<gridg;k++){
			up<<u[i][k]<<"\t";
		}
		up<<endl;
	}

	ofstream down;
 	down.open ("down.dat");
	for(int i=0;i<gridg;i++){
		for(int k=0;k<gridg;k++){
			down<<d[i][k]<<"\t";
		}
		down<<endl;
	}
	down.close();
	//fermant.close();
//------------------------------------------------------------------------------------------

	
	cout<<"1. "<<ant[0][0]<<endl;
	cout<<"2. "<<ant[1][0]<<endl;
	cout<<"3. "<<ant[3][0]<<endl;
	/*
	cout<<"grid "<<grid[0][0]<<endl;
	cout<<"up "<<u[0][0]<<endl;
	cout<<"down "<<d[gridg/2][gridg/2]<<endl;
	cout<<"left "<<l[0][0]<<endl;
	cout<<"rigth "<<u[0][0]<<endl;
	cout<<"random "<<random<<endl;
	cout<<"random2 "<<randdi<<endl;
	//cout<<"anter "<<ant[0][9]-1<<endl;
	cout<<"felder "<<(r[ant[0][0]-1][ant[1][0]])+(u[ant[0][0]][ant[1][0]-1])+(l[ant[0][0]+1][ant[1][0]])+(d[ant[0][0]][ant[1][0]+1])<<endl;
	*/
// ----------------------
	//Löschen des Speichers


	for(int i=0;i<4;i++){				//ant-feld
		delete[] ant[i];}
	delete[] ant;
	
	for(int i=0;i<(gridg);i++){		//grid-feld
		delete[] grid[i];}
	delete[] grid;

	for(int i=0;i<(gridg);i++){		//up-feld
		delete[] u[i];}
	delete[] u;
	
	for(int i=0;i<(gridg);++i){		//down-feld
		delete[] d[i];}
	delete[] d;

	for(int i=0;i<(gridg);++i){		//rigth-feld
		delete[] r[i];}
	delete[] r;

	for(int i=0;i<(gridg);++i){		//left-feld
		delete[] l[i];}
	delete[] l;



	system("pause");

	return 0;

}


void bewegung(int** ant, int**grid, int** r, int** u, int** l, int** d, int swarm, int gridg, int mut){
	
	if(ant[3][swarm]==0){
		if(grid[ant[1][swarm]][ant[0][swarm]]==0){
			bewegung1(ant,swarm);
		}
		else if(grid[ant[1][swarm]][ant[0][swarm]]!=0){
				bewegung2(ant,u,r,d,l,grid,swarm,mut);
			}
	}
	else if(ant[3][swarm]==1){
		bewegung3(ant,r,u,l,d,swarm,gridg);
	}
	else if(ant[3][swarm]==2){

	}
}

void grider(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int gridg){
	
	if(ant[3][swarm]==0){
		grider1(ant,u,r,d,l,grid,swarm);
	}
	else if(ant[3][swarm]==1){
		grider2(ant,u,r,d,l,grid,swarm, gridg);
	}
	else if(ant[3][swarm]==2){

	}
}

void reach(int** ant, int swarm, int start_x, int start_y, int food_x, int food_y, int mut, int* gefunden){
	
	if(ant[3][swarm]==0 || ant[3][swarm]==3){
		food(ant,swarm,food_x,food_y, mut, gefunden);
	}
	else if(ant[3][swarm]==1){
		goal(ant,swarm,start_x,start_y);
	}
	else if(ant[3][swarm]==2){
		neustart(ant,swarm);
	}

}
