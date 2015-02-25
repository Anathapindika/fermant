#include<iostream>
#include <time.h>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include "Bewegung.h"
#include <fstream>
#include <string>
void manh(int** ant, int swarm, int laenge_intern, float* manhatten);
using namespace std;



int main(){

	
	srand((unsigned)time(NULL));		 //seed initialisierung für rand() funktion

///////////////////////////////
// Anfangsbedingungen
//////////////////////////////
	int iterationen=3000;
	int swarm=250;
	int vorhut=swarm;
	int nachhut=swarm;
	bool nachhutpass=true;
	int const gridg=1000;
	int hindernis = 5;
	int start_x=400;
	int start_y=400;
	int food_x=600;
	int food_y=600;
	int food_phaeromon=4;
	int start_phaeromon=2;
	int phaeromon_abnahme=20;				//pro phaeromon_abnahme-züge wird 1 phaeromon abgezogen
	int phaeromon_limite=0;
	float langsam=2;
	int mut=0;
	int abtasten1=15; //18	
	int abtasten2=10;	//72
	float random;
	int bodycount=0;
	int* p_bodycount=&bodycount;
	int erfolgreich=0;
	int* p_erfolgreich=&erfolgreich;
	int gefunden=0;
	int abnahme=8;
	int abnahme_intervall=35;
	int dunst=200;
	int* p_gefunden=&gefunden;
	random = rand()/(float)(RAND_MAX);
	int randdi = rand();
	int swarm_animation=50;
	int speicher=1;
	int verhunger=iterationen;
	int leitung=iterationen/10;
	int laenge_intern=15; //gridg/100;
	int laenge_extern=450;
	int spur_dicke=1;

	

//----------------------------------------------------
// Initialisierung für die Zeiger auf die Felder

	int** ant;										// ant bezeichnet eine nxm Matrix, wobei die Spaltenzahl 
	ant = new int*[20+3*laenge_intern];				//eine Information für spezifische Koordinaten darstellt, 
	for(int i=0;i<20+3*laenge_intern;++i)			//die Zeilenzahl die einzelnen Ants
		ant[i]= new int[swarm];
			
	for(int j=0;j<swarm;j++){						//Ursprungskoordinaten (hälfte der gridigrösse) füllen bzw.
			ant[0][j]=start_x;						//die dritte Koordinate (welche Information über bewegungsrichtung
			ant[1][j]=start_y;						//preis gibt) mit Nullen füllen.
			ant[2][j]=0;							//welche gelaufene Richtung // wird nicht mehr benötigt
			ant[3][j]=0;							//Angabe über Futter oder kein Futter
			ant[4][j]=0;							//Angabe über Zeitdauer, wann letztes Mal Checkpoint erreicht wurde
			ant[5][j]=1;							//Angabe über ziellauf und ende der Bewegungsschlaufe
			ant[6][j]=0;							//Angabe über x Richtung
			ant[7][j]=0;							//Angabe über y Richtung
			ant[8][j]=0;							//Angabe über welche Richtung zu erst gelaufen
			ant[9][j]=0;							//Angabe über wieviele schritte schon gelaufen sind
			ant[10][j]=0;							//Angabe über externe_länge
			ant[11][j]=0;							//Angabe über x Ziellauf
			ant[12][j]=0;							//Angabe über y Ziellauf
			ant[13][j]=start_x;						//Pseudo Ameise x
			ant[14][j]=start_y;						//Pseudo Ameise y
			ant[15][j]=0;							//Überlapp bei DickeFunktion îm Grider
			ant[16][j]=0;							//Manhatten x
			ant[17][j]=0;							//Manhatten y
			ant[18][j]=0;							//Angekommen
			ant[19][j]=0;							//Manhatten Zusatz
			for(int k=0;k<3*laenge_intern;k++){
				ant[20+k][j]=0;
			}
	}



	float* schritte;
	schritte = new float[swarm];

	for(int j=0;j<swarm;j++){
		schritte[j]=0;
	}

	float* manhatten;
	manhatten = new float[swarm];

	for(int j=0;j<swarm;j++){		
		manhatten[j]=0;
	}

	int** grid;										//initialisierung des Grids - ein Feld, welches Pheromon aufnimmt.
	grid = new int*[gridg];							//
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
		for(int j=0;j<gridg;++j){
			r[i][j]=0;
			}
		}



	int** l;										//initialisierung des Left-Feldes - Analog zu Up
	l = new int*[gridg];							
	for(int i=0;i<(gridg);i++)
		l[i]=new int[gridg];
	for(int i=0;i<gridg;++i){						//Mit nullen füllen
		for(int j=0;j<gridg;++j)
			l[i][j]=0;}


	Node*** p;
	p= new Node** [gridg];
	for(int i=0;i<gridg;i++){
		 p[i] = new Node* [gridg];
	}
	for(int i=0;i<gridg;i++){
		for(int j=0;j<gridg;j++){
			p[i][j]=new Node;
			p[i][j]->p_g=0;
			p[i][j]->p_r=0;
			p[i][j]->p_u=0;
			p[i][j]->p_l=0;
			p[i][j]->p_d=0;
			p[i][j]->next=NULL;
		}
	}

	Node*** actual;
	actual = new Node** [gridg];
	for(int i=0;i<gridg;i++){
		 actual[i] = new Node* [gridg];
	}
	for(int i=0;i<gridg;i++){
		for(int j=0;j<gridg;j++){
			actual[i][j]=p[i][j];
		}
	}

ofstream hist;
	hist.open("hist.dat");
	hist<<verhunger<<"\t"<<0<<endl;
	hist.close();


ofstream animation;
 	animation.open ("animation.dat");
	for(int i=0;i<swarm_animation;i++){
			animation<<start_x<<"\t";
		}
		animation<<endl;
	for(int i=0;i<swarm_animation;i++){
			animation<<start_y<<"\t";
		}
		animation<<endl;
	for(int i=0;i<swarm_animation;i++){
			animation<<0<<"\t";
		}
		animation<<endl;
animation.close();



//-----------------------------------------------------------------------------------------
// Bewegungsfunktion

swarm=vorhut;
int essen=1;


for(int t=0;t<iterationen;t++){
	
	if(t==3000)
		cout<<"Ueber Halbzeit durch "<<endl;
		if(t==dunst){
				cout<<"beginn der Dunstphase "<<t<<" - Ameisenablieferung: "<<erfolgreich<<endl;
		}
	

		if(erfolgreich>essen*100){
			cout<<"es haben "<<erfolgreich<<" Ameisen Essen abgeliefert"<<endl;
			essen+=1;
		}
	
		for(int i=0;i<swarm;i++){

			bewegung(ant,grid,r,u,l,d,i,gridg,mut,t,abtasten1, abtasten2, laenge_intern, laenge_extern, food_x, food_y, start_x, start_y, spur_dicke, dunst, p_gefunden, p_erfolgreich, langsam, food_phaeromon, start_phaeromon, phaeromon_limite, phaeromon_abnahme, manhatten,actual,schritte);
		}
		for(int i=0;i<swarm;i++){
			grider(ant,u,r,d,l,grid,i, gridg,food_phaeromon,start_phaeromon,phaeromon_limite,t, phaeromon_abnahme, laenge_intern, spur_dicke, langsam, food_x, food_y, start_x, start_y, actual);
		}
		for(int i=0;i<swarm;i++){
			reach(ant,i,start_x,start_y,food_x,food_y,mut,p_gefunden,t,p_erfolgreich,gridg,laenge_intern);
		}
		for(int i=0;i<swarm;i++){
			karte(ant,i,gridg);
		}
		for(int i=0;i<swarm;i++){
			hunger(ant,grid,r,u,l,d,i,start_x,start_y, verhunger, t, p_bodycount, laenge_intern); //nicht mehr gebraucht
		}
		for(int i=0;i<swarm;i++){
			ant[19][i]=0;
		}
		dampf(u,r,d,l,grid,actual,p,gridg,t,dunst);

	
	if(( t==500)){//t==10 || t==100 || t==200 || t==300 || t==400 || t==500 || t==1000 || t==2000 || t==3000 || t==4000 || t==5000 || t==6000 || t==7000)){
			cout<<"t; "<<t<<" Ameisenabgabe: "<<erfolgreich<<endl;
			
			//string name ="feldtemp" + intToString(t) +
			ofstream feld;
 			feld.open ("feldtemp.dat");
	
			for(int i=0;i<gridg;i++){
				for(int k=0;k<gridg;k++){
					feld<<grid[i][k]<<"\t";
					}
				feld<<endl;
				}
			feld.close();
			
			
			ofstream reach;
			reach.open("reachtemp.dat");
			reach<<start_x<<"\t"<<start_y<<"\t"<<food_x<<"\t"<<food_y<<"\t"<<gridg<<"\t"<<iterationen<<"\t"<<swarm<<"\t"<<swarm_animation<<endl;
			reach.close();
			getchar();
		}
	
		ofstream animation;
 		animation.open ("animation.dat", fstream::app|fstream::out);
			for(int i=0;i<swarm_animation;i++){
				animation<<ant[0][i]<<"\t";
			}
			animation<<endl;
			for(int i=0;i<swarm_animation;i++){
				animation<<ant[1][i]<<"\t";
			}
			animation<<endl;

		for(int i=0;i<swarm_animation;i++){
				animation<<ant[3][i]<<"\t";
			}
			animation<<endl;
		animation.close();
		
		if(erfolgreich>150 && nachhutpass){
			cout<<"nachhut ist gestartet - es haben nun "<<erfolgreich<<" ameisen nach "<<t<<" iterationen, nahrung abgegeben"<<endl;
			nachhutpass=false;
		}
	
		if(t%100==0){
			cout<<t<<endl;}
		

		
}

cout<<ant[0][0]<<" "<<ant[1][0]<<endl;
cout<<"Bei "<<iterationen<<" Iterationen und "<<swarm<<" Ameisen ergab sich folgende statistik:"<<endl;
cout<<"Es sind "<<bodycount<<" Ameisen verhungert."<<endl;
cout<<"Es haben "<<erfolgreich<<" Ameisen Essen abgeliefert."<<endl;

//-----------------------------------------------------------------------------------------
//Speichern



	ofstream feld;
 	feld.open ("feld.dat");
	
	for(int i=0;i<gridg;i++){
		for(int k=0;k<gridg;k++){
			feld<<grid[i][k]<<"\t";
		}
		feld<<endl;
	}
	feld.close();

	

	ofstream reach;
	reach.open("reach.dat");
	reach<<start_x<<"\t"<<start_y<<"\t"<<food_x<<"\t"<<food_y<<"\t"<<gridg<<"\t"<<iterationen<<"\t"<<swarm<<"\t"<<swarm_animation<<endl;
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

	
	
// ----------------------
	//Löschen des Speichers

	/*
	for(int i=0;i<16+laenge_intern;i++){				//ant-feld
		delete[] ant[i];}
	delete[] ant;
	
	for(int i=0;i<(gridg);i++){		//grid-feld
		delete[] grid[i];}
	delete[] grid;

	/*
	for(int i=0;i<(gridg)/10;i++){		//grod-feld
		delete[] grod[i];}
	delete[] grod;
	

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

	*/
	system("pause");

	return 0;

}

