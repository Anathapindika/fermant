#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
using namespace std;
void bewegung1(int** ant, int swarm, int laenge_intern);
void bewegung2(int** ant, int** u, int** r, int** d, int** l, int** grid,int swarm, int mut, int laenge_intern, int gridg, bool tor);
void bewegung3(int** ant, int** r, int** u, int** l, int** d,int swarm, int gridg, int laenge_intern, int spur_dicke,int mut, bool tor);
void goal(int** ant, int swarm, int start_x, int start_y,int t, int* erfolgreich, int laenge_intern, int gridg);
void food(int** ant, int swarm, int food_x, int food_y,int mut, int* gefunden, int t, int gridg, int laenge_intern);
void richtung(int** ant, int swarm, int laenge_intern, int laenge_extern);
void bewegung0(int** ant, int swarm, int laenge_intern, int laenge_extern);
void dicke(int** ant, int** grid, int** u, int** d, int** r, int** l, int swarm, int spur_dicke, int richtung, int gridg, int laenge_intern);
void ziellauf(int** ant, int**grid, int** r, int** u, int** l, int** d, int spur_dicke, int laenge_intern, int swarm, int start_x, int start_y, int food_x, int food_y, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int phaeromon_abnahme, int t, struct Node*** a);
int phaeromona(int** ant, int food_phaeromon, int start_phaeromon, int swarm, int phaeromon_limite, int t, int phaeromon_abnahme);
int rt(int** r, int** ant, int swarm, int geruch_dicke, int gridg);
int lt(int** l, int** ant, int swarm, int geruch_dicke, int gridg);
int dt(int** d, int** ant, int swarm, int geruch_dicke, int gridg);
int ut(int** u, int** ant, int swarm, int geruch_dicke, int gridg);
int rin(int** r, int** ant, int swarm, int gridg);
int lin(int** l, int** ant, int swarm, int gridg);
int din(int** d, int** ant, int swarm, int gridg);
int uin(int** u, int** ant, int swarm, int gridg);
void grider1(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int gridg, int spur_dicke, float langsam, int start_x, int start_y, struct Node*** a);
void grider2(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int gridg, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int spur_dicke, float langsam, int start_x, int start_y, struct Node*** a);
int phaeromon(int** ant, int food_phaeromon, int start_phaeromon, int swarm, int phaeromon_limite, int t, int phaeromon_abnahme);
void dicke(int** ant, int** grid, int** u, int** d, int** r, int** l, int swarm, int spur_dicke, int richtung, int gridg, int laenge_intern, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, struct Node*** a);
void dicke2(int** ant, int** grid, int** u, int** d, int** r, int** l, int swarm, int spur_dicke, int richtung, int gridg, int laenge_intern);
void anti_dicke(int** ant, int** grid, int** u, int** d, int** r, int** l, int swarm, int spur_dicke, int richtung, int gridg, int laenge_intern, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int dunst);
void start_flucht(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm,int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int gridg, int spur_dicke, int dunst, int food_x, int food_y, int start_x, int start_y);
void food_flucht(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm,int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int gridg, int spur_dicke, int dunst, int food_x, int food_y, int start_x, int start_y);
int anti_phaeromon(int** ant, int food_phaeromon, int start_phaeromon, int swarm, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int dunst);
float inhomogenitaet(int** ant, int swarm, int gridg, int laenge_intern, float langsam);

struct Node
{
	int p_r,p_l,p_d,p_u,p_g;
	Node *next;
};


//Richtungswahl einer Ameise, falls sie sich auf einem Punkt befinden, welcher keine Pheromon aufweist. Achtung laenge_intern wird nicht mehr gebraucht!
void richtung(int** ant, int swarm, int laenge_intern, int laenge_extern)
{	
	int radius;
	radius=rand()%(laenge_extern)+1;				//Zufällige Radiuswahl 
	int ring=rand()%(4*radius);						//Wahl des Punktes auf dem Kreis (diamat), welcher von Radius aufgespannt und angelaufen wird.
	int rxx;
	int ryy;

	if(ring<radius)
	{
		rxx=radius-ring;
		ryy=ring;
	}
	else if(ring<2*radius)
	{
		rxx=-(ring-radius);
		ryy=2*radius-ring;
	}
	else if(ring<3*radius)
	{
		rxx=ring-3*radius;
		ryy=-(ring-2*radius);
	}

	else if(ring<4*radius)
	{
		rxx=ring-3*radius;
		ryy=-(4*radius-ring);
	}

	ant[6][swarm]=rxx;										//speicherung der Richtung in xx
	ant[7][swarm]=ryy;										//speicherung der Richtung in yy
	

	ant[8][swarm]=rand()%2;									//
	ant[10][swarm]=radius;
	
}

//Bewegungsfunktion, welche Ameisen in Richtung von richtung() laufen lässt.
void bewegung0(int** ant, int swarm, int laenge_intern, int laenge_extern)
{
	
	int xr=0;
	int yr=0;
	if(ant[6][swarm]==0 && ant[7][swarm]==0){					//richtungswahl
		richtung(ant,swarm,laenge_intern,laenge_extern);
	}

	if(abs(ant[6][swarm])>0)
		xr=rand()%abs(ant[6][swarm])+1;						//Welche Richtung gelaufen werden soll
	
	if(abs(ant[7][swarm])>0)
		yr=rand()%abs(ant[7][swarm])+1;						//Welche Richtung gelaufen werden soll

	if(xr>yr){
		if(ant[6][swarm]>0){
					ant[0][swarm]+=1;						//Bewegung
					ant[16][swarm]+=1;						//Manhatten
					ant[ant[9][swarm]+20][swarm]=1;			//Speicherung
					ant[9][swarm]+=1;						//Speicherung
					ant[6][swarm]-=1;						//Richtung
					ant[2][swarm]=1;						//Letzte Richtung
					return;
					
				}

		else if(ant[6][swarm]<0){
					ant[0][swarm]-=1;
					ant[16][swarm]-=1;
					ant[ant[9][swarm]+20][swarm]=3;
					ant[9][swarm]+=1;
					ant[6][swarm]+=1;
					ant[2][swarm]=3;
					return;
				}

	}

	else if(yr>xr){

		if(ant[7][swarm]>0){
					ant[1][swarm]+=1;
					ant[17][swarm]+=1;
					ant[ant[9][swarm]+20][swarm]=4;
					ant[9][swarm]+=1;
					ant[7][swarm]-=1;
					ant[2][swarm]=4;
					return;
				}
				else if(ant[7][swarm]<0){
					ant[1][swarm]-=1;
					ant[17][swarm]-=1;
					ant[ant[9][swarm]+20][swarm]=2;
					ant[9][swarm]+=1;
					ant[7][swarm]+=1;
					ant[2][swarm]=2;
					return;
				}

	}
	else if(xr==yr){
		if(abs(ant[6][swarm])<abs(ant[7][swarm]) || abs(ant[6][swarm])==abs(ant[7][swarm]) && ant[8][swarm]==0){

			if(ant[7][swarm]>0){
					ant[1][swarm]+=1;
					ant[17][swarm]+=1;
					ant[ant[9][swarm]+20][swarm]=4;
					ant[9][swarm]+=1;
					ant[7][swarm]-=1;
					ant[2][swarm]=4;
					return;
				}
				else if(ant[7][swarm]<0){
					ant[1][swarm]-=1;
					ant[17][swarm]-=1;
					ant[ant[9][swarm]+20][swarm]=2;
					ant[9][swarm]+=1;
					ant[7][swarm]+=1;
					ant[2][swarm]=2;
					return;
				}
		}
		else if(abs(ant[6][swarm])>abs(ant[7][swarm]) || abs(ant[6][swarm])==abs(ant[7][swarm]) && ant[8][swarm]==1){

			if(ant[6][swarm]>0){
					ant[0][swarm]+=1;
					ant[16][swarm]+=1;
					ant[ant[9][swarm]+20][swarm]=1;
					ant[9][swarm]+=1;
					ant[6][swarm]-=1;
					ant[2][swarm]=1;
					return;
					
				}

		else if(ant[6][swarm]<0){
					ant[0][swarm]-=1;
					ant[16][swarm]-=1;
					ant[ant[9][swarm]+20][swarm]=3;
					ant[9][swarm]+=1;
					ant[6][swarm]+=1;
					ant[2][swarm]=3;
					return;
				}
		}
	}

}

//Willkürliche Bewegung in eine willkürliche Richtung - immerdann, wenn ausfallschritte erforderlich sind.
void bewegung1(int** ant, int swarm, int laenge_intern)
{
	
	int r1;
	bool pass1 = true;
	while(pass1){

		r1 = rand()%4+1;
		if(r1==1 && ant[2][swarm]!=3){
			ant[0][swarm]+=1;
			ant[16][swarm]+=1;
			ant[2][swarm]=1;
			ant[ant[9][swarm]+20][swarm]=1;
			ant[9][swarm]+=1;
			pass1=false;
			
		}
		else if(r1==2 && ant[2][swarm]!=4){
			ant[1][swarm]-=1;
			ant[17][swarm]-=1;
			ant[2][swarm]=2;
			ant[ant[9][swarm]+20][swarm]=2;
			ant[9][swarm]+=1;
			pass1=false;
		
		}
		else if(r1==3 && ant[2][swarm]!=1){
			ant[0][swarm]-=1;
			ant[16][swarm]-=1;
			ant[2][swarm]=3;
			ant[ant[9][swarm]+20][swarm]=3;
			ant[9][swarm]+=1;
			pass1=false;
		
		}
		else if(r1==4 && ant[2][swarm]!=2){
			ant[1][swarm]+=1;
			ant[17][swarm]+=1;
			ant[2][swarm]=4;
			ant[ant[9][swarm]+20][swarm]=4;
			ant[9][swarm]+=1;
			pass1=false;
		
		}
		else{

		}
	}
}

//Immer dann, wenn gridpunkt schon betreten wurde - auswertungsbewegung.
void bewegung2(int** ant, int** u, int** r, int** d, int** l, int** grid,int swarm, int mut, int laenge_intern, int spur_dicke, int gridg, bool tor)
{
	if(mut!=0){
	int versuch=rand()%mut;
		if(versuch==1){
			
			bewegung1(ant,swarm,laenge_intern);
			return;
		}
	}

	int xk=ant[0][swarm];
	int yk=ant[1][swarm];
	int rg=0;
	int lg=0;
	int ug=0;
	int dg=0;

	if(tor){
		dg=dt(d,ant,swarm,1,gridg);
		rg=rt(r,ant,swarm,1,gridg);
		lg=lt(l,ant,swarm,1,gridg);
		ug=ut(u,ant,swarm,1,gridg);
	}
	else{
		dg=d[yk][xk];
		rg=r[yk][xk];
		lg=l[yk][xk];
		ug=u[yk][xk];
	}
	int grid2=rg+lg+ug+dg;

	float wr1, wu1, wl1, wd1;
	
	wr1 = ((float)rg)/((float)grid2);

	wu1 = ((float)ug)/((float)grid2);

	wl1 = ((float)lg)/((float)grid2);
	
	wd1 = ((float)dg)/((float)grid2);
		

	float ww1;
	
	ww1=wr1+wu1+wl1+wd1;				//Normierung auf (0,1)

	wu1 = wu1+wr1;
    wl1 = wl1+wu1;
    wd1 = wd1+wl1;
	
	wr1 = wr1/ww1;
    wu1 = wu1/ww1;
    wl1 = wl1/ww1;
    wd1 = wd1/ww1;

	float r2;
	bool pass2=true;
	
	while(pass2){
		r2= rand()/(float)(RAND_MAX);
		

		if(0<r2 && r2<wr1 && ant[2][swarm]!=3){
			ant[0][swarm]+=1;
			ant[16][swarm]+=1;
			ant[2][swarm]=1;
			ant[ant[9][swarm]+20][swarm]=1;
			ant[9][swarm]+=1;
			
			pass2=false;
		}

		else if(wr1<r2 && r2<wu1 && ant[2][swarm]!=4){
			ant[1][swarm]-=1;
			ant[17][swarm]-=1;
			ant[2][swarm]=2;
			ant[ant[9][swarm]+20][swarm]=2;
			ant[9][swarm]+=1;
			
			pass2=false;
		}

		else if(wu1<r2 && r2<wl1 && ant[2][swarm]!=1){
			ant[0][swarm]-=1;
			ant[16][swarm]-=1;
			ant[2][swarm]=3;
			ant[ant[9][swarm]+20][swarm]=3;
			ant[9][swarm]+=1;
			
			pass2=false;
		}

		else if(wl1<r2 && r2<1 && ant[2][swarm]!=2){
			ant[1][swarm]+=1;
			ant[17][swarm]+=1;
			ant[2][swarm]=4;
			ant[ant[9][swarm]+20][swarm]=4;
			ant[9][swarm]+=1;
			
			pass2=false;
		}
		else{
			bewegung1(ant,swarm,laenge_intern);
			
			pass2=false;
		}
	}
}

//immerdann, wenn Ameise im Besitz von Futter ist - gleiche Auswertung wie Bewegung 2 nur rückläufige Bewegung
void bewegung3(int** ant, int** r, int** u, int** l, int** d,int swarm, int gridg, int laenge_intern, int mut, bool tor){	
		
	if(mut!=0){
	int versuch=rand()%mut;
	if(versuch==1){
		
		bewegung1(ant,swarm,laenge_intern);
		return;
	}
	}
	float wr2, wu2, wl2, wd2;
	int rn, un, ln, dn;
	int xk=ant[0][swarm];
	int yk=ant[1][swarm];
	float total;
		
	if(tor){
		ln=lin(l,ant,swarm,gridg);
		rn=rin(r,ant,swarm,gridg);
		dn=din(d,ant,swarm,gridg);
		un=uin(u,ant,swarm,gridg);
	}
	else{
		if(xk==gridg-2){
			ln=l[yk][1];
		}
		else{
			ln=l[yk][xk+1];
		}
		if(xk==1){
			rn=r[yk][gridg-2];
		}
		else{
			rn=r[yk][xk-1];
		}
		if(yk==gridg-2){
			un=u[1][xk];
		}
		else{
			un=u[yk+1][xk];
		}
		if(yk==1){
			dn=d[gridg-2][xk];
		}
		else{
			dn=d[yk-1][xk];
		}
	}

	total=rn+un+ln+dn;
	
	wr2=(float)rn/total;
	wu2=(float)un/total;
	wl2=(float)ln/total;
	wd2=(float)dn/total;
	
	wu2 = wu2+wr2;
    wl2 = wl2+wu2;
    wd2 = wd2+wl2;


	float r3;
	bool pass3 =true;
	
	
	while(pass3){
		r3= rand()/(float)(RAND_MAX);
		
		if(0<r3 && r3<wr2 && ant[2][swarm]!=1){
			ant[0][swarm]-=1;
			ant[16][swarm]-=1;
			ant[2][swarm]=3;
			ant[ant[9][swarm]+20][swarm]=3;
			ant[9][swarm]+=1;
			pass3=false;
		}
		else if(wr2<r3 && r3<wu2 && ant[2][swarm]!=2){
			ant[1][swarm]+=1;
			ant[17][swarm]+=1;
			ant[2][swarm]=4;
			ant[ant[9][swarm]+20][swarm]=4;
			ant[9][swarm]+=1;
			pass3=false;
		}
		else if(wu2<r3 && r3<wl2 && ant[2][swarm]!=3){
			ant[0][swarm]+=1;
			ant[16][swarm]+=1;
			ant[2][swarm]=1;
			ant[ant[9][swarm]+20][swarm]=1;
			ant[9][swarm]+=1;
			pass3=false;
		}
		else if(wl2<r3 && r3<1 && ant[2][swarm]!=4){
			ant[1][swarm]-=1;
			ant[17][swarm]-=1;
			ant[2][swarm]=2;
			ant[ant[9][swarm]+20][swarm]=2;
			ant[9][swarm]+=1;
			pass3=false;
		}
		else{
			bewegung1(ant,swarm, laenge_intern);
			pass3=false;

		}
	}
	//cout<<"bewegung 3 draussen"<<endl;
}


void karte(int** ant, int swarm, int gridg){
		
	if(ant[0][swarm]==gridg-1){
		ant[0][swarm]=1;}
	
	else if(ant[1][swarm]==gridg-1){
		ant[1][swarm]=1;}

	else if(ant[0][swarm]==0){
		ant[0][swarm]=gridg-2;}

	else if(ant[1][swarm]==0){
		ant[1][swarm]=gridg-2;}

}

void pseudo_karte(int** ant, int swarm, int gridg, int laenge_intern){
		
	if(ant[13][swarm]==gridg-1){
		ant[13][swarm]=1;}
	
	else if(ant[14][swarm]==gridg-1){
		ant[14][swarm]=1;}

	else if(ant[13][swarm]==0){
		ant[13][swarm]=gridg-2;}

	else if(ant[14][swarm]==0){
		ant[14][swarm]=gridg-2;}
}


//statistik funktion - und wechsel von futtersuchend zu startsuchend
void food(int** ant, int swarm, int food_x, int food_y,int mut, int* gefunden, int t, int gridg, int laenge_intern){
	

	if(ant[0][swarm]>=food_x-(gridg)/200 && ant[0][swarm]<=food_x+(gridg)/200 && ant[1][swarm]<=food_y+gridg/200 && ant[1][swarm]>=food_y-(gridg)/200){

		ant[6][swarm]=0;//-ant[6][swarm];
		ant[7][swarm]=0;//-ant[7][swarm];
		
		ant[4][swarm]=t;
		ant[2][swarm]=0;
		ant[10][swarm]=0;
		int ende=ant[9][swarm];
		for(int i=ant[9][swarm];i<2*laenge_intern;i++){
		
			ant[ant[9][swarm]+20][swarm]=0;
			ant[9][swarm]+=1;
		}
		ant[9][swarm]=ende;

	if(*gefunden==0){
		cout<<"trouvee! bei "<<t<<" iterationen. Ameise Nr: "<<swarm<<endl;
		*gefunden=1;
		}
	}
}

//äquivalent zu food()
void goal(int** ant, int swarm, int start_x, int start_y,int t, int* erfolgreich, int laenge_intern, int gridg){
	
	if(ant[0][swarm]>=start_x-(gridg/200) && ant[0][swarm]<=start_x+(gridg/200) && ant[1][swarm]>=start_y-(gridg/200) && ant[1][swarm]<=start_y+(gridg/200)){
		
		
		*erfolgreich+=1;
		//cout<<"Ameise "<<swarm<<" hat nach "<<ant[4][swarm]<<" Schritten erfolgreich Essen abgeliefert."<<endl;
		//(cout<<"Es ist die "<<t<<"-te Iteration."<<endl;

		//Histogramierungsdatei
		
		/*ofstream hist;
		hist.open("hist.dat", ios::app);
			hist<<2<<"\t"<<t-ant[4][swarm]<<endl;
		hist.close();*/

		ant[4][swarm]=t;
		ant[2][swarm]=0;
		ant[10][swarm]=0;
		
		/*
		ant[0][swarm]=start_x+1;
		ant[1][swarm]=start_y+1;
		ant[13][swarm]=start_x+1;
		ant[14][swarm]=start_y+1;
		*/
		for(int i=ant[9][swarm];i<2*laenge_intern;i++){
			
			ant[ant[9][swarm]+20][swarm]=0;
			ant[9][swarm]+=1;
		}
		//ant[15][swarm]=0;
		//cout<<"finished! "<< endl;

	}
}

//Für Ameisen, welche das Futter nicht finden und im Kreis laufen - sterben aus. - wird nicht mehr benötigt
void hunger(int** ant, int** grid, int** r, int** u, int** l, int** d, int swarm, int start_x, int start_y, int verhunger, int t, int* bodycount, int laenge_intern){
	
	if(t-ant[4][swarm]>verhunger){

		ant[0][swarm]=start_x;
		ant[1][swarm]=start_y;
		ant[13][swarm]=start_x;
		ant[14][swarm]=start_y;
		ant[16][swarm]=start_x;
		ant[17][swarm]=start_y;
		ant[3][swarm]=0;
		ant[10][swarm]=0;
		ant[4][swarm]=t;
		ant[15][swarm]=0;
		*bodycount+=1;

		if(ant[3][swarm]==0 || ant[3][swarm]==2){
		
		ofstream hist;
		hist.open("hist.dat", ios::app);
			hist<<1<<"\t"<<verhunger<<endl;
		hist.close();
		
		}
		if(ant[3][swarm]==1){
		ofstream hist;
		hist.open("hist.dat", ios::app);
			hist<<2<<"\t"<<verhunger<<endl;
		hist.close();
		
		}
	}
}


void bewegung(int** ant, int**grid, int** r, int** u, int** l, int** d, int swarm, int gridg, int mut, int t, int abtasten, int abtasten2, int laenge_intern, int laenge_extern, int food_x, int food_y, int start_x, int start_y, int spur_dicke, int dunst, int* gefunden, int* erfolgreich, float langsam, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int phaeromon_abnahme, float* manhatten, struct Node*** a, float* schritte)
{

	ant[13][swarm]=ant[0][swarm];					//Pseudo-Ameisen
	ant[14][swarm]=ant[1][swarm];
	int weite=laenge_intern-ant[19][swarm];
	ant[19][swarm]=0;
	float schrittl;
	int schritti;
	float xx;
	float yy;
	int xk=ant[0][swarm];
	int yk=ant[1][swarm];
	bool tor=false;

	xx=abs(ant[16][swarm]);
	yy=abs(ant[17][swarm]);
	int radius=xx+yy;
	float kreis=sqrt(xx*xx+yy*yy);
	float rest=radius-kreis+manhatten[swarm];
	int resti=rest;
	manhatten[swarm]=rest-resti;
	weite+=resti;
	ant[16][swarm]=0;
	ant[17][swarm]=0;
	
	while(ant[9][swarm]<weite && ant[5][swarm]){
	
		
		 if(ant[3][swarm]==0 || ant[3][swarm]==2){
			
			 int ug=0;
			 int rg=0;
			 int lg=0;
			 int dg=0;

			rg=rt(r,ant,swarm,1,gridg);
			lg=lt(l,ant,swarm,1,gridg);
			ug=ut(u,ant,swarm,1,gridg);
			dg=dt(d,ant,swarm,1,gridg);

			int grid2=rg+lg+ug+dg;
			if(true){
				tor=true;
			}
			else{
				tor=false;
				dg=d[yk][xk];
				rg=r[yk][xk];
				lg=l[yk][xk];
				ug=u[yk][xk];
				grid2=rg+lg+ug+dg;
			 }
			
					
				if(grid2<abtasten)
				{
					bewegung0(ant,swarm, laenge_intern, laenge_extern);
				}
				else if(grid2>=abtasten){
					bewegung2(ant,u,r,d,l,grid,swarm,mut,laenge_intern, spur_dicke, gridg, tor);

				}
				
				if(ant[0][swarm]>=food_x-(gridg)/100 && ant[0][swarm]<=food_x+(gridg)/100 && ant[1][swarm]<=food_y+gridg/100 && ant[1][swarm]>=food_y-(gridg)/100){
					ziellauf(ant,grid,r,u,l,d,spur_dicke,laenge_intern,swarm,start_x,start_y,food_x,food_y, food_phaeromon, start_phaeromon, phaeromon_limite, phaeromon_abnahme, t, a);
					food(ant,swarm,food_x,food_y,mut,gefunden,t,gridg,laenge_intern);
			}
		}


		else if(ant[3][swarm]==1)
		{
			int rn, un, ln, dn;
			float total;

			ln=lin(l,ant,swarm,gridg);
			rn=rin(r,ant,swarm,gridg);
			dn=din(d,ant,swarm,gridg);
			un=uin(u,ant,swarm,gridg);
			total=rn+un+ln+dn;

			if(true){
				tor=true;
			}
			else{

				tor=false;
				if(xk==gridg-2){
					ln=l[yk][1];
				}
				else{
					ln=l[yk][xk+1];
				}
				if(xk==1){
					rn=r[yk][gridg-2];
				}
				else{
					rn=r[yk][xk-1];
				}
				if(yk==gridg-2){
					un=u[1][xk];
				}
				else{
					un=u[yk+1][xk];
				}
				if(yk==1){
					dn=d[gridg-2][xk];
				}
				else{
					dn=d[yk-1][xk];
				}

			
			}
			
			total=rn+un+ln+dn;

				if(total<abtasten2)
				{

					bewegung0(ant,swarm, laenge_intern, laenge_extern);
					
				}
				else if(total>=abtasten2){

					bewegung3(ant,r,u,l,d,swarm,gridg,laenge_intern, mut, tor);
				}
				
				if(ant[0][swarm]>=start_x-(gridg/200) && ant[0][swarm]<=start_x+(gridg/200) && ant[1][swarm]>=start_y-(gridg/200) && ant[1][swarm]<=start_y+(gridg/200)){ //ant[0][swarm]>start_x-(gridg)/100 && ant[0][swarm]<start_x+(gridg)/100 && ant[1][swarm]<start_y+gridg/100 && ant[1][swarm]>start_y-(gridg)/100){
					ziellauf(ant,grid,r,u,l,d,spur_dicke,laenge_intern,swarm,start_x,start_y,food_x,food_y, food_phaeromon, start_phaeromon, phaeromon_limite, phaeromon_abnahme, t, a);
					goal(ant,swarm,start_x,start_y,t,erfolgreich,laenge_intern, gridg);
				}
				
				
		}
		karte(ant,swarm,gridg);
	
		schrittl=inhomogenitaet(ant,swarm,gridg,laenge_intern, langsam);
		schritte[swarm]+=schrittl;
		schritti=schritte[swarm];
		schritte[swarm]-=schritti;
		weite-=schritti;

	}
	ant[19][swarm]=ant[9][swarm]-weite;
	
	
	ant[18][swarm]=ant[9][swarm];
	ant[9][swarm]=0;
	ant[5][swarm]=1;
}

void reach(int** ant, int swarm, int start_x, int start_y, int food_x, int food_y, int mut, int* gefunden, int t, int* p_erfolgreich, int gridg, int laenge_intern){
	
	
	if(ant[3][swarm]==0 || ant[3][swarm]==2){
		if(ant[0][swarm]>=food_x-(gridg)/200 && ant[0][swarm]<=food_x+(gridg)/200 && ant[1][swarm]<=food_y+gridg/200 && ant[1][swarm]>=food_y-(gridg)/200){
			ant[3][swarm]=1;
		}
	}
	else if(ant[3][swarm]==1){
		if(ant[0][swarm]>=start_x-(gridg/200) && ant[0][swarm]<=start_x+(gridg/200) && ant[1][swarm]>=start_y-(gridg/200) && ant[1][swarm]<=start_y+(gridg/200)){
			ant[3][swarm]=2;
		}
	}
}

void ziellauf(int** ant, int**grid, int** r, int** u, int** l, int** d, int spur_dicke, int laenge_intern, int swarm, int start_x, int start_y, int food_x, int food_y, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int phaeromon_abnahme, int t, struct Node*** a){
	
	int zuschlag=phaeromona(ant,food_phaeromon, start_phaeromon, swarm, phaeromon_limite,t,phaeromon_abnahme);
	


	if(ant[3][swarm]==0 || ant[3][swarm]==2){
		
		ant[11][swarm]=ant[0][swarm];
		ant[12][swarm]=ant[1][swarm];

		int rr=rand()%2;
		while(rr!=3){
			if(rr==0){
			if(ant[0][swarm]<food_x){
				while(ant[0][swarm]!=food_x){
							for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]+i][ant[0][swarm]]+=zuschlag;
								r[ant[1][swarm]+i][ant[0][swarm]]+=zuschlag;

								a[ant[1][swarm]+i][ant[0][swarm]]->p_g+=zuschlag;
								a[ant[1][swarm]+i][ant[0][swarm]]->p_r+=zuschlag;
							}
							ant[0][swarm]+=1;
						}
					}
			else if(ant[0][swarm]>food_x){
				while(ant[0][swarm]!=food_x){
							for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]+i][ant[0][swarm]]+=zuschlag;
								l[ant[1][swarm]+i][ant[0][swarm]]+=zuschlag;

								a[ant[1][swarm]+i][ant[0][swarm]]->p_g+=zuschlag;
								a[ant[1][swarm]+i][ant[0][swarm]]->p_l+=zuschlag;
							}
							ant[0][swarm]-=1;
						}
					}
				if(ant[1][swarm]==food_y){
					rr=3;
				}
				else if(ant[1][swarm]!=food_y){
					rr=1;
				}

			}
			if(rr==1){
			if(ant[1][swarm]<food_y){
					while(ant[1][swarm]!=food_y){
						for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]][ant[0][swarm]+i]+=zuschlag;
								d[ant[1][swarm]][ant[0][swarm]+i]+=zuschlag;

								a[ant[1][swarm]][ant[0][swarm]+i]->p_g+=zuschlag;
								a[ant[1][swarm]][ant[0][swarm]+i]->p_d+=zuschlag;
							}
						ant[1][swarm]+=1;
					}
				}
			else if(ant[1][swarm]>food_y){
						while(ant[1][swarm]!=food_y){
							for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]][ant[0][swarm]+i]+=zuschlag;
								u[ant[1][swarm]][ant[0][swarm]+i]+=zuschlag;

								a[ant[1][swarm]][ant[0][swarm]+i]->p_g+=zuschlag;
								a[ant[1][swarm]][ant[0][swarm]+i]->p_u+=zuschlag;
							}
							ant[1][swarm]-=1;
						}
					}
			}
			if(ant[0][swarm]==food_x){
				rr=3;
			}
			else{
				rr=0;
			}
		}
	
	}
	else if(ant[3][swarm]==1){
		ant[11][swarm]=ant[0][swarm];
		ant[12][swarm]=ant[1][swarm];
		int rr=rand()%2;
		while(rr!=3){
			if(rr==0){
			if(ant[0][swarm]<start_x){
				while(ant[0][swarm]!=start_x){
						ant[0][swarm]+=1;
					for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]+i][ant[0][swarm]+1]+=zuschlag;
								l[ant[1][swarm]+i][ant[0][swarm]+1]+=zuschlag;

								a[ant[1][swarm]+i][ant[0][swarm]+1]->p_g+=zuschlag;
								a[ant[1][swarm]+i][ant[0][swarm]+1]->p_l+=zuschlag;
							}
						}
					}
			else if(ant[0][swarm]>start_x){
				while(ant[0][swarm]!=start_x){
						ant[0][swarm]-=1;
							for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]+i][ant[0][swarm]-1]+=zuschlag;
								r[ant[1][swarm]+i][ant[0][swarm]-1]+=zuschlag;

								a[ant[1][swarm]+i][ant[0][swarm]-1]->p_g+=zuschlag;
								a[ant[1][swarm]+i][ant[0][swarm]-1]->p_r+=zuschlag;
							}
						}
					}
				if(ant[1][swarm]==start_y){
					rr=3;
				}
				else{
					rr=1;
				}

			}
			if(rr==1){
			if(ant[1][swarm]<start_y+1){
					while(ant[1][swarm]!=start_y){
						ant[1][swarm]+=1;
						for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]+1][ant[0][swarm]+i]+=zuschlag;
								u[ant[1][swarm]+1][ant[0][swarm]+i]+=zuschlag;

								a[ant[1][swarm]+1][ant[0][swarm]+i]->p_g+=zuschlag;
								a[ant[1][swarm]+1][ant[0][swarm]+i]->p_u+=zuschlag;
							}
						
					}
				}
			else if(ant[1][swarm]>start_y){
						while(ant[1][swarm]!=start_y){
							ant[1][swarm]-=1;
							for(int i=-(spur_dicke/2);i<=(spur_dicke/2);i++){
								grid[ant[1][swarm]-1][ant[0][swarm]+i]+=zuschlag;
								d[ant[1][swarm]-1][ant[0][swarm]+i]+=zuschlag;

								a[ant[1][swarm]-1][ant[0][swarm]+i]->p_g+=zuschlag;
								a[ant[1][swarm]-1][ant[0][swarm]+i]->p_d+=zuschlag;
							}
							
						}
					}
			}
			if(ant[0][swarm]==start_x){
				rr=3;
			}
			else{
				rr=0;
			}
		}
		
	}
	if((ant[0][swarm]!=start_x || ant[1][swarm]!=start_y) && ant[3][swarm]==1)
		cout<<"fehler ziellauf"<<endl;
		ant[5][swarm]=0;
}
 
int phaeromona(int** ant, int food_phaeromon, int start_phaeromon, int swarm, int phaeromon_limite, int t, int phaeromon_abnahme)
{
	if(ant[3][swarm]==1)
	{
		int zusatz;
		
		zusatz=food_phaeromon-(t-ant[4][swarm])/phaeromon_abnahme;

			if(zusatz<phaeromon_limite){
				zusatz = phaeromon_limite;
				return zusatz;			}
		return zusatz;
	}

	if(ant[3][swarm]==0 || ant[3][swarm]==2){

		int zusatz;
		zusatz=start_phaeromon-(t-ant[4][swarm])/phaeromon_abnahme;

			if(zusatz<phaeromon_limite){
				zusatz = phaeromon_limite;
				return zusatz;			}
		return zusatz;
		
	}

}

int rt(int** r, int** ant, int swarm, int geruch_dicke, int gridg){

	int rn=0;
	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	rn+=10*r[yy][xx];

	
	for(int i=(-1);i<=1;i++){
		rn+=r[yy+i][xx+1];
	}
	
	return rn;
}

int lt(int** l, int** ant, int swarm, int geruch_dicke, int gridg){

	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int ln=0;
	ln+=10*l[yy][xx];
	
	for(int i=(-1);i<=1;i++){
		ln+=l[yy+i][xx-1];
	}
	return ln;
}

int ut(int** u, int** ant, int swarm, int geruch_dicke, int gridg){

	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int un=0;
	un+=10*u[yy][xx];
	
	for(int i=(-1);i<=1;i++){
		un+=u[yy-1][xx+i];
	}
	return un;
}

int dt(int** d, int** ant, int swarm, int geruch_dicke, int gridg){

	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int dn=0;
	dn+=10*d[yy][xx];

	
	for(int i=(-1);i<=1;i++){
		dn+=d[yy+1][xx+i];
	}

	return dn;
}

int rin(int** r, int** ant, int swarm, int gridg){


	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int geruch_dicke=1;
	int rn=0;
	rn+=10*r[yy][xx-1];

	if(xx==1)
		xx=gridg-3;
	else if(xx==2)
		xx=gridg-2;
	else
		xx-=2;
	
	for(int i=-geruch_dicke;i<=geruch_dicke;i++){
		rn+=r[yy+i][xx];
	}
	

	return rn;
}

int lin(int** l, int** ant, int swarm, int gridg){

	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int geruch_dicke=1;
	int ln=0;
	ln+=10*l[yy][xx+1];
	
	if(xx==gridg-2)
		xx=2;
	else if(xx==gridg-3)
		xx=1;
	else
		xx+=2;
	
	for(int i=-geruch_dicke;i<=geruch_dicke;i++){
		ln+=l[yy+i][xx];
	}
	

	return ln;
}

int uin(int** u, int** ant, int swarm, int gridg){

	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int un=0;
	int geruch_dicke=1;
	un+=10*u[yy+1][xx];
	
	if(yy==gridg-2)
		yy=2;
	if(yy==gridg-3)
		yy=1;
	else
		yy+=2;
	
	for(int i=-geruch_dicke;i<=geruch_dicke;i++){
		un+=u[yy][xx+i];
	}
	
	return un;
}

int din(int** d, int** ant, int swarm, int gridg){

	int xx=ant[0][swarm];
	int yy=ant[1][swarm];
	int dn=0;
	int geruch_dicke=1;
	dn+=10*d[yy-1][xx];
	
	if(yy==1)
		yy=gridg-3;
	else if(yy==2)
		yy=gridg-2;
	else
		yy-=2;
	
	for(int i=-geruch_dicke;i<=geruch_dicke;i++){
		dn+=d[yy][xx+i];
	}

	return dn;
}
//funktionen, welche den Ort der jeweiligen Ameisen (nach der Bewegung) in ein Grid einliest.


//////////////////GRIDER//////////////////////////////////////////////
//////////////////GRIDER/////////////////////////////////////////////

void grider1(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm,int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int gridg, int spur_dicke, float langsam, int start_x, int start_y, struct Node*** a)
{

	
	
	int richtung =0;
	int weite=ant[18][swarm];

	for(int k=0;k<weite;k++){
				
		

		/*
		cout<<"richtungsweisung der pseudoameise "<<ant[k+20][0]<<endl;
		cout<<ant[13][0]<<"  "<<ant[14][0]<<endl;
		*/
		//cout<<"grider 1 "<<ant[13][swarm]<<"  "<<ant[14][swarm]<<"  "<<ant[k+20][swarm]<<endl;
		if(ant[k+20][swarm]==1){
			

			if((ant[k+20-1][swarm]==4 && k!=0) || (k==0 && ant[15][swarm]==4)){
				richtung=41;
				}
			else if((ant[k+20-1][swarm]==2 && k!=0) || (k==0 && ant[15][swarm]==2)){
				richtung=21;
			}
			else
				richtung=1;

			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[13][swarm]+=1;
			
		}

		else if (ant[k+20][swarm]==2){
			
			if ((ant[k+20-1][swarm]==3 && k!=0) || (k==0 && ant[15][swarm]==3)){
				richtung = 32;
			}
			else if ((ant[k+20-1][swarm]==1 && k!=0) || (k==0 && ant[15][swarm]==1)){
				richtung = 12;
			}
			else
				richtung=2;
			
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[14][swarm]-=1;
		}
		else if (ant[k+20][swarm]==3){
			
			if ((ant[k+20-1][swarm]==4 && k!=0) || (k==0 && ant[15][swarm]==4)){
				richtung =43;
			}
			else if ((ant[k+20-1][swarm]==2 && k!=0) || (k==0 && ant[15][swarm]==2)){
				richtung =23;
			}
			else
				richtung=3;
			//cout<<"grid_left"<<grid[(ant[0][swarm])+1][(ant[1][swarm])]<<endl;
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[13][swarm]-=1;
		}
		else if (ant[k+20][swarm]==4){
			
			if ((ant[k+20-1][swarm]==3 && k!=0) || (k==0 && ant[15][swarm]==3)){
				richtung =34;
			}
			else if ((ant[k+20-1][swarm]==1 && k!=0)|| (k==0 && ant[15][swarm]==1)){
				richtung=14;
			}
			else
				richtung=4;
			
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[14][swarm]+=1;
		}
		pseudo_karte(ant,swarm,gridg,laenge_intern);

		richtung=0;
		
	}
	

	ant[15][swarm]=ant[19+weite][swarm];
	if(ant[0][swarm]==start_x && ant[1][swarm]==start_y)
	{
		ant[13][swarm]=start_x;
		ant[14][swarm]=start_y;

	}
	
	ant[18][swarm]=0;
}

void grider2(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int gridg, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int spur_dicke, float langsam, int start_x, int start_y, struct Node*** a)
{

	ant[13][swarm]=ant[0][swarm];
	ant[14][swarm]=ant[1][swarm];
	
	int weite=ant[18][swarm];
	
	int richtung = 0;
	if(ant[19+weite][swarm]==1){
		ant[13][swarm]-=1;
		if(ant[13][swarm]<=0){
			ant[13][swarm]=gridg-2;
		}
	}
	else if(ant[19+weite][swarm]==3){
		ant[13][swarm]+=1;
		if(ant[13][swarm]>=gridg-1){
			ant[13][swarm]=1;
		}
	}
	else if(ant[19+weite][swarm]==2){
		ant[14][swarm]+=1;
		if(ant[14][swarm]==gridg-1){
			ant[14][swarm]=1;
		}
	}
	else if(ant[19+weite][swarm]==4){
		ant[14][swarm]-=1;
		if(ant[14][swarm]==0){
			ant[14][swarm]=gridg-2;
		}
	}

	if(ant[0][swarm]==start_x && ant[1][swarm]==start_y){
		ant[13][swarm]=ant[11][swarm];
		ant[14][swarm]=ant[12][swarm];
	}

	
	for(int k=1;k<weite;k++){
		

		if(ant[19+weite-k][swarm]==1){

			if((ant[19+weite-k+1][swarm]==2)){
				richtung=43;
			}
			else if((ant[19+weite-k+1][swarm]==4)){
				richtung=23;
			}
			else
				richtung=3;
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[13][swarm]-=1;

			if(ant[13][swarm]==0){
				ant[13][swarm]=gridg-2;
			}
			
			
		}

		else if(ant[19+weite-k][swarm]==2){
			if((ant[19+weite-k+1][swarm]==3)){
				richtung=14;
			}
			else if((ant[19+weite-k+1][swarm]==1)){
				richtung=34;
			}
			else
				richtung=4;
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[14][swarm]+=1;
			if(ant[14][swarm]==gridg-1){
				ant[14][swarm]=1;
			}
		}

		else if(ant[19+weite-k][swarm]==3){
			if((ant[19+weite-k+1][swarm]==4)){
				richtung=21;
			}
			else if((ant[19+weite-k+1][swarm]==2)){
				richtung=41;
			}
			else
				richtung=1;
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[13][swarm]+=1;

			if(ant[13][swarm]==gridg-1){
				ant[13][swarm]=1;
			}
		}

		else if(ant[19+weite-k][swarm]==4){
			if((ant[19+weite-k+1][swarm]==3)){
				richtung=12;
			}
			else if((ant[19+weite-k+1][swarm]==1)){
				richtung=32;
			}
			else
				richtung=2;
			dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
			ant[14][swarm]-=1;
			if(ant[14][swarm]==0){
				ant[14][swarm]=gridg-2;
			}	
		}

	}
	
	richtung=0;
	

	if(ant[15][swarm]==1){
		
		if((ant[20][swarm]==2)){
				richtung=43;
			}
		else if((ant[20][swarm]==4)){
				richtung=23;
			}
		else
			richtung=3;
	}
	else if(ant[15][swarm]==2){
			
			if((ant[20][swarm]==3)){
				richtung=14;
			}
			else if((ant[20][swarm]==1)){
				richtung=34;
			}
			else
				richtung=4;
	}
	else if(ant[15][swarm]==3){
		
			if((ant[20][swarm]==4)){
				richtung=21;
			}
			else if((ant[20][swarm]==2)){
				richtung=41;
			}
			else
				richtung=1;
	}
	else if(ant[15][swarm]==4){
		
			if((ant[20][swarm]==3)){
				richtung=12;
			}
			else if((ant[20][swarm]==1)){
				richtung=32;
			}
			else
				richtung=2;
	}
	dicke(ant,grid,u,d,r,l,swarm,spur_dicke,richtung,gridg, laenge_intern, food_phaeromon, start_phaeromon, phaeromon_limite, t, phaeromon_abnahme, a);
	ant[15][swarm]=ant[19+weite][swarm];
	ant[18][swarm]=0;
}

void grider(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int gridg, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, int laenge_intern, int spur_dicke, float langsam, int food_x, int food_y, int start_x, int start_y, struct Node*** a ){
	


	if(ant[3][swarm]==0 || ant[3][swarm]==2){
		grider1(ant,u,r,d,l,grid,swarm,food_phaeromon,start_phaeromon,phaeromon_limite,t, phaeromon_abnahme, laenge_intern, gridg, spur_dicke, langsam, start_x, start_y, a);
	}
	else if(ant[3][swarm]==1){
		grider2(ant,u,r,d,l,grid,swarm, gridg, food_phaeromon,start_phaeromon,phaeromon_limite,t, phaeromon_abnahme, laenge_intern, spur_dicke, langsam, start_x, start_y, a);
	}
	
}

int phaeromon(int** ant, int food_phaeromon, int start_phaeromon, int swarm, int phaeromon_limite, int t, int phaeromon_abnahme)
{
	if(ant[3][swarm]==1)
	{
		int zusatz;
		
		zusatz=food_phaeromon-(t-ant[4][swarm])/phaeromon_abnahme;

			if(zusatz<phaeromon_limite){
				zusatz = phaeromon_limite;
				return zusatz;			}
		return zusatz;
	}

	if(ant[3][swarm]==0 || ant[3][swarm]==2){

		int zusatz;
		zusatz=start_phaeromon-(t-ant[4][swarm])/phaeromon_abnahme;

			if(zusatz<phaeromon_limite){
				zusatz = phaeromon_limite;
				return zusatz;			}
		return zusatz;
		
	}

}

void dicke(int** ant, int** grid, int** u, int** d, int** r, int** l, int swarm, int spur_dicke, int richtung, int gridg, int laenge_intern, int food_phaeromon, int start_phaeromon, int phaeromon_limite, int t, int phaeromon_abnahme, struct Node*** a)
{

	
	int zuschlag;

	zuschlag = phaeromon(ant,food_phaeromon, start_phaeromon,swarm,phaeromon_limite,t, phaeromon_abnahme);
	if(zuschlag==0)
		return;


	
	int aa=ant[13][swarm];
	int bb=ant[14][swarm];

	
	if(richtung==1){
		
		for(int i=-(spur_dicke)/2; i<=(spur_dicke/2); i++){
			if(ant[14][swarm]+i>=(gridg-1)){
				grid[1+i][ant[13][swarm]]+=zuschlag;
				r[1+i][ant[13] [swarm]]+=zuschlag;

				a[1+i][ant[13][swarm]]->p_g+=zuschlag;
				a[1+i][ant[13][swarm]]->p_r+=zuschlag;
			}
			else if(ant[14][swarm]+i<=0){
				grid[gridg-1+i][ant[13][swarm]]+=zuschlag;
				r[gridg-1+i][ant[13][swarm]]+=zuschlag;

				a[gridg-1+i][ant[13][swarm]]->p_g+=zuschlag;
				a[gridg-1+i][ant[13][swarm]]->p_r+=zuschlag;
			}
			else{
				grid[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
				r[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

				a[ant[14][swarm]+i][ant[13][swarm]]->p_g+=zuschlag;
				a[ant[14][swarm]+i][ant[13][swarm]]->p_r+=zuschlag;
			}
		}
	}
	else if(richtung==12){
		
		ant[14][swarm]+=(spur_dicke)/2;									//um spur neu anzufangen/ nach unten versetzen
	
			for(int k=0;k<(spur_dicke);k++){
				if(ant[14][swarm]>gridg-2){
					int uber = ant[14][swarm]-gridg+2;
					ant[14][swarm] = 1+uber;
				}
				if(ant[14][swarm]==0){
					ant[14][swarm]=gridg-2;
				}
				for(int i=-(spur_dicke)/2; i<=(spur_dicke/2); i++){
					if(ant[13][swarm]+i>=(gridg-1)){
						if(i<0 && k<=spur_dicke/2){
							//r[ant[14][swarm]][i]-=zuschlag;
							u[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_u+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][i]+=zuschlag;
							u[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_u+=zuschlag;
							a[ant[14][swarm]][i]->p_g+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
							//r[ant[14][swarm]][i]-=zuschlag;
							//grid[ant[14][swarm]][i]-=zuschlag;
						}
					}
					else if(ant[13][swarm]+i<=0){
						if(i<0 && k<=spur_dicke/2){
							//r[ant[14][swarm]][gridg-1+i]-=zuschlag;
							u[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_u+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][gridg-1+i]+=zuschlag;
							u[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_u+=zuschlag;
							a[ant[14][swarm]][gridg-1+i]->p_g+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
							//grid[ant[14][swarm]][gridg-1+i]-=zuschlag;
							//r[ant[14][swarm]][gridg-1+i]-=zuschlag;
						}

					}
					else{
						if(i<0 && k<=spur_dicke/2){
							//r[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							u[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_u+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;
							u[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_g+=zuschlag;
							a[ant[14][swarm]][ant[13][swarm]+i]->p_u+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
							//grid[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							//r[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
						}
					}
				}
					ant[14][swarm]-=1;
		
			}
		ant[14][swarm]+=(spur_dicke)/2+1;

/*
		}
		else(){ //zweite m\F6glichkeit


		}
		*/
	}
	else if(richtung==14){
		//c=14;
		//cout<<"r 14"<<endl;
		ant[14][swarm]-=(spur_dicke)/2;									//um spur neu anzufangen/ nach unten versetzen
		
			for(int k=0;k<(spur_dicke);k++){

				if(ant[14][swarm]<1){
					int uber=1-ant[14][swarm];
					ant[14][swarm]=gridg-1-uber;
				}
				if(ant[14][swarm]==gridg-1){
					ant[14][swarm]=1;
				}
				for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
					if(ant[13][swarm]+i>=(gridg-1)){
						if(i<0 && k<=spur_dicke/2){
							d[ant[14][swarm]][i]+=zuschlag;
							//r[ant[14][swarm]][i]-=zuschlag;

							a[ant[14][swarm]][i]->p_d+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][i]+=zuschlag;
							d[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_g+=zuschlag;
							a[ant[14][swarm]][i]->p_d+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
							//r[ant[14][swarm]][i]-=zuschlag;
							//grid[ant[14][swarm]][i]-=zuschlag;
						}
					}
					else if(ant[13][swarm]+i<=0){
						if(i<0 && k<=spur_dicke/2){
							//r[ant[14][swarm]][gridg-1+i]-=zuschlag;
							d[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_d+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][gridg-1+i]+=zuschlag;
							d[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_g+=zuschlag;
							a[ant[14][swarm]][gridg-1+i]->p_d+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
							//r[ant[14][swarm]][gridg-1+i]-=zuschlag;
							//grid[ant[14][swarm]][gridg-1+i]-=zuschlag;
						}
					} 
					else{
						if(i<0 && k<=spur_dicke/2){
							//r[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							d[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_d+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;
							d[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_g+=zuschlag;
							a[ant[14][swarm]][ant[13][swarm]+i]->p_d+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
							//r[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							//grid[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
						}
					}
				}	
				ant[14][swarm]+=1;
			}
			ant[14][swarm]-=(spur_dicke/2)+1;
	}
	else if(richtung==2){
		
		for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
			if(ant[13][swarm]+i>=(gridg-1)){
				grid[ant[14][swarm]][i]+=zuschlag;
				u[ant[14][swarm]][i]+=zuschlag;

				a[ant[14][swarm]][i]->p_g+=zuschlag;
				a[ant[14][swarm]][i]->p_u+=zuschlag;
			}
			else if(ant[13][swarm]+i<=0){//cout<<ant[13][swarm]+i<<"  "<<ant[14][swarm]<<"   "<<swarm<<endl;
				grid[ant[14][swarm]][gridg-1+i]+=zuschlag;
				u[ant[14][swarm]][gridg-1+i]+=zuschlag;

				a[ant[14][swarm]][gridg-1+i]->p_g+=zuschlag;
				a[ant[14][swarm]][gridg-1+i]->p_u+=zuschlag;
			}
			else{
				grid[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;
				u[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

				a[ant[14][swarm]][ant[13][swarm]+i]->p_g+=zuschlag;
				a[ant[14][swarm]][ant[13][swarm]+i]->p_u+=zuschlag;
			}
		}
	}
	else if(richtung==21){
		//cout<<"21 "<<endl;
		ant[13][swarm]-=(spur_dicke)/2;
			for(int k=0;k<(spur_dicke);k++){	
				if(ant[13][swarm]<1){
					int uber=1-ant[13][swarm];
					ant[13][swarm]=gridg-1-uber;
				}
				if(ant[13][swarm]==gridg-1){
					ant[13][swarm]=1;
				}
				for(int i=-(spur_dicke)/2; i<=(spur_dicke/2); i++){
					if(ant[14][swarm]+i>=(gridg-1)){
						if(i>0 && k<=spur_dicke/2){
							//u[1+i][ant[13][swarm]]-=zuschlag;
							r[1+i][ant[13] [swarm]]+=zuschlag;

							a[1+i][ant[13] [swarm]]->p_r+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[1+i][ant[13][swarm]]+=zuschlag;
							r[1+i][ant[13] [swarm]]+=zuschlag;

							a[1+i][ant[13] [swarm]]->p_g+=zuschlag;
							a[1+i][ant[13] [swarm]]->p_r+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
							//grid[1+i][ant[13][swarm]]-=zuschlag;
							//u[1+i][ant[13][swarm]]-=zuschlag;
						}
					
					}
					else if(ant[14][swarm]+i<=0){
						if(i>0 && k<=spur_dicke/2){
							//u[gridg-1+i][ant[13][swarm]]-=zuschlag;
							r[gridg-1+i][ant[13][swarm]]+=zuschlag;

							a[gridg-1+i][ant[13][swarm]]->p_r+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[gridg-1+i][ant[13][swarm]]+=zuschlag;
							r[gridg-1+i][ant[13][swarm]]+=zuschlag;

							a[gridg-1+i][ant[13][swarm]]->p_g+=zuschlag;
							a[gridg-1+i][ant[13][swarm]]->p_r+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
							//grid[gridg-1+i][ant[13][swarm]]-=zuschlag;
							//u[gridg-1+i][ant[13][swarm]]-=zuschlag;
						}
					}
					else{
						if(i>0 && k<=spur_dicke/2){
							//cout<<ant[14][swarm]<<"   "<<ant[13][swarm]+i<<endl;
							//u[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
							r[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

							a[ant[14][swarm]+i][ant[13][swarm]]->p_r+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
							r[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

							a[ant[14][swarm]+i][ant[13][swarm]]->p_g+=zuschlag;
							a[ant[14][swarm]+i][ant[13][swarm]]->p_r+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
							//grid[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
							//u[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
						}
					}
				}
				ant[13][swarm]+=1;
			}
			ant[13][swarm]-=(spur_dicke)/2+1;
		//	cout<<ant[13][swarm]<<endl;
	}
	else if(richtung==23){
		//c=23;
		//cout<<"r 23"<<endl;
		ant[13][swarm]+=(spur_dicke)/2;
		for(int k=0;k<(spur_dicke);k++){	
			if(ant[13][swarm]>gridg-2){
				int uber = ant[13][swarm]-gridg+2;
				ant[13][swarm] = 1+uber;
			}
			if(ant[13][swarm]==0){
				ant[13][swarm]=gridg-2;
			}
			for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
				if(ant[14][swarm]+i>=(gridg-1)){
					if(i>0 && k<=spur_dicke/2){
					//	u[1+i][ant[13][swarm]]-=zuschlag;
						l[1+i][ant[13][swarm]]+=zuschlag;

						a[1+i][ant[13][swarm]]->p_l+=zuschlag;
					}
					else if(i<=0 && k<=spur_dicke/2){
						grid[1+i][ant[13][swarm]]+=zuschlag;
						l[1+i][ant[13][swarm]]+=zuschlag;

						a[1+i][ant[13][swarm]]->p_g+=zuschlag;
						a[1+i][ant[13][swarm]]->p_l+=zuschlag;
					}
					else if(i>0 && k>spur_dicke/2){
					//	grid[1+i][ant[13][swarm]]-=zuschlag;
					//	u[1+i][ant[13][swarm]]-=zuschlag;
					}
				}
				else if(ant[14][swarm]+i<=0){
					if(i>0 && k<=spur_dicke/2){
						//u[gridg-1+i][ant[13][swarm]]-=zuschlag;
						l[gridg-1+i][ant[13][swarm]]+=zuschlag;
						
						a[gridg-1+i][ant[13][swarm]]->p_l+=zuschlag;
					}
					else if(i<=0 && k<=spur_dicke/2){
						grid[gridg-1+i][ant[13][swarm]]+=zuschlag;
						l[gridg-1+i][ant[13][swarm]]+=zuschlag;

						a[gridg-1+i][ant[13][swarm]]->p_g+=zuschlag;
						a[gridg-1+i][ant[13][swarm]]->p_l+=zuschlag;
					}
					else if(i>0 && k>spur_dicke/2){
						//grid[gridg-1+i][ant[13][swarm]]-=zuschlag;
						//u[gridg-1+i][ant[13][swarm]]-=zuschlag;
					}
				}
				else{
					if(i>0 && k<=spur_dicke/2){
						//cout<<ant[14][swarm]<<"   "<<ant[13][swarm]+i<<endl;
						//u[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
						l[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

						a[ant[14][swarm]+i][ant[13][swarm]]->p_l+=zuschlag;
					}
					else if(i<=0 && k<=spur_dicke/2){
						grid[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
						l[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

						a[ant[14][swarm]+i][ant[13][swarm]]->p_g+=zuschlag;
						a[ant[14][swarm]+i][ant[13][swarm]]->p_l+=zuschlag;
					}
					else if(i>0 && k>spur_dicke/2){
						//grid[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
						//u[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
					}
				}
			}
			ant[13][swarm]-=1;
		}
		ant[13][swarm]+=spur_dicke/2+1;
	}
	else if(richtung==3){
		for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
			if(ant[14][swarm]+i>=(gridg-1)){
				grid[1+i][ant[13][swarm]]+=zuschlag;
				l[1+i][ant[13][swarm]]+=zuschlag;

				a[1+i][ant[13][swarm]]->p_g+=zuschlag;
				a[1+i][ant[13][swarm]]->p_l+=zuschlag;
			}
			else if(ant[14][swarm]+i<=0){
				//cout<<ant[14][swarm]+i<<" hambel"<<endl;
				grid[gridg-1+i][ant[13][swarm]]+=zuschlag;
				l[gridg-1+i][ant[13][swarm]]+=zuschlag;

				a[gridg-1+i][ant[13][swarm]]->p_g+=zuschlag;
				a[gridg-1+i][ant[13][swarm]]->p_l+=zuschlag;
			}
			else{
				grid[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
				l[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

				a[ant[14][swarm]+i][ant[13][swarm]]->p_g+=zuschlag;
				a[ant[14][swarm]+i][ant[13][swarm]]->p_l+=zuschlag;
			}
		}
	}
	else if(richtung==32){
		//c=32;
		//cout<<"r 32"<<endl;
		//cout<<ant[14][swarm]<<endl;
		ant[14][swarm]+=(spur_dicke)/2;
			for(int k=0;k<(spur_dicke);k++){				
				if(ant[14][swarm]>gridg-2){
					int uber = ant[14][swarm]-gridg+2;
					ant[14][swarm] = 1+uber;
				}
				if(ant[14][swarm]==0){
					ant[14][swarm]=gridg-2;
				}
				for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
					if(ant[13][swarm]+i>=(gridg-1)){
						if(i>0 && k<=spur_dicke/2){
							//l[ant[14][swarm]][i]-=zuschlag;
							u[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_u+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][i]+=zuschlag;
							u[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_g+=zuschlag;
							a[ant[14][swarm]][i]->p_u+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
							//grid[ant[14][swarm]][i]-=zuschlag;
							//l[ant[14][swarm]][i]-=zuschlag;
						}
					}
					else if(ant[13][swarm]+i<=0){
						if(i>0 && k<=spur_dicke/2){
							//l[ant[14][swarm]][gridg-1+i]-=zuschlag;
							u[ant[14][swarm]][gridg-1+i]+=zuschlag;	

							a[ant[14][swarm]][gridg-1+i]->p_u+=zuschlag;	
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][gridg-1+i]+=zuschlag;
							u[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_g+=zuschlag;
							a[ant[14][swarm]][gridg-1+i]->p_u+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
							//grid[ant[14][swarm]][gridg-1+i]-=zuschlag;
							//l[ant[14][swarm]][gridg-1+i]-=zuschlag;
						}
					}
					else{
						if(i>0 && k<=spur_dicke/2){
							//l[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							u[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_u+=zuschlag;

						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;
							u[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_g+=zuschlag;
							a[ant[14][swarm]][ant[13][swarm]+i]->p_u+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
							//grid[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							//l[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
						}
					}
				}
					ant[14][swarm]-=1;
			}
		ant[14][swarm]+=spur_dicke/2+1;
		//cout<<ant[14][swarm]<<endl;
	}
	else if(richtung==34){
	//	c=34;
		//cout<<"r 34"<<endl;
		ant[14][swarm]-=(spur_dicke)/2;
		for(int k=0;k<(spur_dicke);k++){	
				if(ant[14][swarm]<1){
					int uber=1-ant[14][swarm];
					ant[14][swarm]=gridg-1-uber;
				}
				if(ant[14][swarm]==gridg-1){
					ant[14][swarm]=1;
				}
				for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){		
					if(ant[13][swarm]+i>=(gridg-1)){
						if(i>0 && k<=spur_dicke/2){
		//					l[ant[14][swarm]][i]-=zuschlag;
							d[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_d+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][i]+=zuschlag;
							d[ant[14][swarm]][i]+=zuschlag;

							a[ant[14][swarm]][i]->p_g+=zuschlag;
							a[ant[14][swarm]][i]->p_d+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
			//				grid[ant[14][swarm]][i]-=zuschlag;
			//				l[ant[14][swarm]][i]-=zuschlag;
						}
					
					}
					else if(ant[13][swarm]+i<=0){
						if(i>0 && k<=spur_dicke/2){
			//				l[ant[14][swarm]][gridg-1+i]-=zuschlag;
							d[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_d+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][gridg-1+i]+=zuschlag;
							d[ant[14][swarm]][gridg-1+i]+=zuschlag;

							a[ant[14][swarm]][gridg-1+i]->p_g+=zuschlag;
							a[ant[14][swarm]][gridg-1+i]->p_d+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
			//				grid[ant[14][swarm]][gridg-1+i]-=zuschlag;
			//				l[ant[14][swarm]][gridg-1+i]-=zuschlag;
						}
					}
					else{
						if(i>0 && k<=spur_dicke/2){
			//				l[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
							d[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_d+=zuschlag;
						}
						else if(i<=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;
							d[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

							a[ant[14][swarm]][ant[13][swarm]+i]->p_g+=zuschlag;
							a[ant[14][swarm]][ant[13][swarm]+i]->p_d+=zuschlag;
						}
						else if(i>0 && k>spur_dicke/2){
			//				grid[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
			//				l[ant[14][swarm]][ant[13][swarm]+i]-=zuschlag;
						}
					}
				}
				ant[14][swarm]+=1;
		}
		ant[14][swarm]-=spur_dicke/2+1;
	}
	else if(richtung==4){
		//c=4;
		for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
			if(ant[13][swarm]+i>=(gridg-1)){
				grid[ant[14][swarm]][i]+=zuschlag;
				d[ant[14][swarm]][i]+=zuschlag;

				a[ant[14][swarm]][i]->p_g+=zuschlag;
				a[ant[14][swarm]][i]->p_d+=zuschlag;
			}
			else if(ant[13][swarm]+i<=0){
				grid[ant[14][swarm]][gridg-1+i]+=zuschlag;
				d[ant[14][swarm]][gridg-1+i]+=zuschlag;

				a[ant[14][swarm]][gridg-1+i]->p_g+=zuschlag;
				a[ant[14][swarm]][gridg-1+i]->p_d+=zuschlag;
			}
			else{
				//cout<<ant[14][swarm]<<"  "<<ant[13][swarm]+i<<endl;
				grid[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;
				d[ant[14][swarm]][ant[13][swarm]+i]+=zuschlag;

				a[ant[14][swarm]][ant[13][swarm]+i]->p_g+=zuschlag;
				a[ant[14][swarm]][ant[13][swarm]+i]->p_d+=zuschlag;
			}
		}
	}
	else if(richtung==41){
		//c=41;
		//cout<<"r 41"<<endl;
		ant[13][swarm]-=(spur_dicke)/2;
		for(int k=0;k<(spur_dicke);k++){	
			if(ant[13][swarm]<1){
				int uber=1-ant[13][swarm];
				ant[13][swarm]=gridg-1-uber;
			}
			if(ant[13][swarm]==gridg-1){
				ant[13][swarm]=1;
			}
			for(int i=-(spur_dicke)/2; i<=(spur_dicke/2); i++){
				if(ant[14][swarm]+i>=(gridg-1)){
					if(i<0 && k<=spur_dicke/2){
			//			d[1+i][ant[13][swarm]]-=zuschlag;
						r[1+i][ant[13] [swarm]]+=zuschlag;

						a[1+i][ant[13] [swarm]]->p_r+=zuschlag;
					}
					else if(i>=0 && k<=spur_dicke/2){
						grid[1+i][ant[13][swarm]]+=zuschlag;
						r[1+i][ant[13] [swarm]]+=zuschlag;

						a[1+i][ant[13][swarm]]->p_g+=zuschlag;
						a[1+i][ant[13][swarm]]->p_r+=zuschlag;
					}
					else if(i<0 && k>spur_dicke/2){
			//			grid[1+i][ant[13][swarm]]-=zuschlag;
			//			d[1+i][ant[13] [swarm]]-=zuschlag;
					}
				} 
				else if(ant[14][swarm]+i<=0){
					if(i<0 && k<=spur_dicke/2){
			//			d[gridg-1+i][ant[13][swarm]]-=zuschlag;
						r[gridg-1+i][ant[13][swarm]]+=zuschlag;

						a[gridg-1+i][ant[13][swarm]]->p_r+=zuschlag;
					}
					else if(i>=0 && k<=spur_dicke/2){
						grid[gridg-1+i][ant[13][swarm]]+=zuschlag;
						r[gridg-1+i][ant[13][swarm]]+=zuschlag;

						a[gridg-1+i][ant[13][swarm]]->p_g+=zuschlag;
						a[gridg-1+i][ant[13][swarm]]->p_r+=zuschlag;
					}
					else if(i<0 && k>spur_dicke/2){
			//			grid[gridg-1+i][ant[13][swarm]]-=zuschlag;
			//			d[gridg-1+i][ant[13][swarm]]-=zuschlag;
					}
				}
				else{
					if(i<0 && k<=spur_dicke/2){
			//			d[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
						r[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

						a[ant[14][swarm]+i][ant[13][swarm]]->p_r+=zuschlag;
					}
					else if(i>=0 && k<=spur_dicke/2){
						grid[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
						r[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

						a[ant[14][swarm]+i][ant[13][swarm]]->p_g+=zuschlag;
						a[ant[14][swarm]+i][ant[13][swarm]]->p_r+=zuschlag;
					}
					else if(i<0 && k>spur_dicke/2){
			//			grid[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
			//			d[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
					}
				}
			}
				ant[13][swarm]+=1;
		}
		ant[13][swarm]-=spur_dicke/2+1;
	}
	else if(richtung==43){
		//c=43;
		//cout<<"r 43"<<endl;
		//cout<<ant[13][swarm]<<endl;
		ant[13][swarm]+=(spur_dicke)/2;
			for(int k=0;k<(spur_dicke);k++){	
				if(ant[13][swarm]>gridg+2){
					int uber = ant[13][swarm]-gridg-2;
					ant[13][swarm] = 1+uber;
				}
				if(ant[13][swarm]==0){
					ant[13][swarm]=gridg-2;
				}
				for(int i=-(spur_dicke)/2; i<=spur_dicke/2; i++){
					if(ant[14][swarm]+i>=(gridg-1)){
						if(i<0 && k<=spur_dicke/2){
			//				d[1+i][ant[13][swarm]]-=zuschlag;
							l[1+i][ant[13][swarm]]+=zuschlag;

							a[1+i][ant[13][swarm]]->p_l+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[1+i][ant[13][swarm]]+=zuschlag;
							l[1+i][ant[13][swarm]]+=zuschlag;

							a[1+i][ant[13][swarm]]->p_g+=zuschlag;
							a[1+i][ant[13][swarm]]->p_l+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
			//				grid[1+i][ant[13][swarm]]-=zuschlag;
			//				d[1+i][ant[13][swarm]]-=zuschlag;
						}
					}
					else if(ant[14][swarm]+i<=0){
						if(i<0 && k<=spur_dicke/2){
			//				d[gridg-1+i][ant[13][swarm]]-=zuschlag;
							l[gridg-1+i][ant[13][swarm]]+=zuschlag;
							//NUR HIER
							a[gridg-1+i][ant[13][swarm]]->p_l+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[gridg-1+i][ant[13][swarm]]+=zuschlag;
							l[gridg-1+i][ant[13][swarm]]+=zuschlag;

							a[gridg-1+i][ant[13][swarm]]->p_g+=zuschlag;
							a[gridg-1+i][ant[13][swarm]]->p_l+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
			//				grid[gridg-1+i][ant[13][swarm]]-=zuschlag;
			//				d[gridg-1+i][ant[13][swarm]]-=zuschlag;
						}
					}
					else{
						if(i<0 && k<=spur_dicke/2){
							//cout<<ant[14][swarm]<<"   "<<ant[13][swarm]+i<<endl;
			//				d[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag; HIIIIIIIER
							l[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
							a[ant[14][swarm]+i][ant[13][swarm]]->p_l+=zuschlag;
						}
						else if(i>=0 && k<=spur_dicke/2){
							grid[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;
							l[ant[14][swarm]+i][ant[13][swarm]]+=zuschlag;

							a[ant[14][swarm]+i][ant[13][swarm]]->p_g+=zuschlag;
							a[ant[14][swarm]+i][ant[13][swarm]]->p_l+=zuschlag;
						}
						else if(i<0 && k>spur_dicke/2){
			//				grid[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
			//				d[ant[14][swarm]+i][ant[13][swarm]]-=zuschlag;
						}
					}
				}
				ant[13][swarm]-=1;
			}
			ant[13][swarm]+=spur_dicke/2+1;
			//cout<<ant[13][swarm]<<endl;
		}
	//pseudo_karte(ant,swarm,gridg,laenge_intern);
	//ant[13][swarm]=ant[13][swarm];
	//ant[14][swarm]=ant[14][swarm];
	
	ant[13][swarm]=aa;
	ant[14][swarm]=bb;
}


void dampf(int** u, int** r, int** d, int** l, int** grid, struct Node*** a, struct Node*** p,int gridg, int t, int dunst)
{
	int iter=dunst/15;
	
	if(t%iter!=0)
		return;

	if(t<dunst){
		if(t%iter==0){
			for(int i=0;i<gridg;i++){
				for(int j=0;j<gridg;j++){
					a[i][j]->next=new Node;
					a[i][j]=a[i][j]->next;
					a[i][j]->p_g=0;
					a[i][j]->p_r=0;
					a[i][j]->p_u=0;
					a[i][j]->p_l=0;
					a[i][j]->p_d=0;
					a[i][j]->next=NULL;
				}
			}
		}
	}
	else{

		if(!a[gridg-1][gridg-1]->next){
			for(int i=0;i<gridg;i++){
				for(int j=0;j<gridg;j++){
				a[i][j]=p[i][j];
				}
			}
		}
		else{
			for(int i=0;i<gridg;i++){
				for(int j=0;j<gridg;j++){
					a[i][j]=a[i][j]->next;
				}
			}
		}

		for(int i=0;i<gridg;i++){
			for(int j=0;j<gridg;j++){
				grid[i][j]-=a[i][j]->p_g;
				a[i][j]->p_g=0;

				u[i][j]-=a[i][j]->p_u;
				a[i][j]->p_u=0;

				r[i][j]-=a[i][j]->p_r;
				a[i][j]->p_r=0;

				d[i][j]-=a[i][j]->p_d;
				a[i][j]->p_d=0;

				l[i][j]-=a[i][j]->p_l;
				a[i][j]->p_l=0;
			}
		}
	}
}

float inhomogenitaet(int** ant, int swarm, int gridg, int laenge_intern, float langsam)
{
	float laufen;
	if(ant[0][swarm]>500){
		laufen=langsam-1;
	}
	else{
		laufen=0;
	}

	return laufen;
}
