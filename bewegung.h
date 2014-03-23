#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
using namespace std;


void bewegung1(int** ant, int swarm)
{
	//srand((unsigned)time(NULL));
	int r1;

    r1 = rand()%4+1;
	
	if(r1==1 && ant[2][swarm]!=3){
		ant[0][swarm]+=1;
		ant[2][swarm]=1;
		//cout<<"bewegung1_1"<<endl;
		//cout<<"x "<<ant[0][swarm]<<"\t"<<"y "<<ant[1][swarm]<<endl;
	}
	else if(r1==2 && ant[2][swarm]!=4){
		ant[1][swarm]-=1;
		ant[2][swarm]=2;
	//cout<<"bewegung1_2"<<endl;
	//cout<<"x "<<ant[0][swarm]<<"\t"<<"y "<<ant[1][swarm]<<endl;
	}
	else if(r1==3 && ant[2][swarm]!=1){
		ant[0][swarm]-=1;
		ant[2][swarm]=3;
	//cout<<"bewegung1_3"<<endl;
	//cout<<"x "<<ant[0][swarm]<<"\t"<<"y "<<ant[1][swarm]<<endl;
	}
	else if(r1==4 && ant[2][swarm]!=2){
		ant[1][swarm]+=1;
		ant[2][swarm]=4;
	//cout<<"bewegung1_4"<<endl;
	//cout<<"x "<<ant[0][swarm]<<"\t"<<"y "<<ant[1][swarm]<<endl;
	}
	else{
		bewegung1(ant, swarm);
	}

}

void bewegung2(int** ant, int** u, int** r, int** d, int** l, int** grid,int swarm, float mut)
{
	float wr1, wu1, wl1, wd1;

	//cout<<"grid_beweg_2 "<<(grid[ant[1][swarm]][ant[0][swarm]])<<endl;

	if(r[ant[1][swarm]][ant[0][swarm]] != 0){
		wr1 = ((float)r[ant[1][swarm]][ant[0][swarm]])/((float)grid[ant[1][swarm]][ant[0][swarm]]);
	//cout<<"rechtesfeld "<<(r[ant[1][swarm]][ant[0][swarm]])<<endl;
	}
	else{
		wr1 = mut;}
	
    if(u[ant[1][swarm]][ant[0][swarm]] != 0){
		wu1 = ((float)u[ant[1][swarm]][ant[0][swarm]])/((float)grid[ant[1][swarm]][ant[0][swarm]]);
	//cout<<"ufeld "<<(u[ant[1][swarm]][ant[0][swarm]])<<endl;
	}
	else{
		wu1 = mut;}
        
	if(l[ant[1][swarm]][ant[0][swarm]] != 0){
		wl1 = ((float)l[ant[1][swarm]][ant[0][swarm]])/((float)grid[ant[1][swarm]][ant[0][swarm]]);
	//cout<<"lfeld "<<(l[ant[1][swarm]][ant[0][swarm]])<<endl;
	}
	else{
		wl1 = mut;}
        
    if(d[ant[1][swarm]][ant[0][swarm]] != 0){
		wd1 = ((float)d[ant[1][swarm]][ant[0][swarm]])/((float)grid[ant[1][swarm]][ant[0][swarm]]);
	//cout<<"dfeld "<<(d[ant[1][swarm]][ant[0][swarm]])<<endl;
	}
	else{
		wd1 = mut;}
	
	//cout<<endl<<"wr  "<<wr<<endl<<"wu  "<<wu<<endl<<"wl "<<wl<<endl<<"wd "<<wd<<endl;
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
	r2= rand()/(float)(RAND_MAX);

	//cout<<"r2  "<<r2<<endl<<"wr  "<<wr<<endl<<"wu  "<<wu<<endl<<"wl "<<wl<<endl<<"wd "<<wd<<endl;

	if(0<r2 && r2<wr1){
		ant[0][swarm]+=1;
		ant[2][swarm]=1;
	//cout<<"bewegung2_rigth"<<endl;
	}

	else if(wr1<r2 && r2<wu1){
		ant[1][swarm]-=1;
		ant[2][swarm]=2;
	//cout<<"bewegung2_up"<<endl;
	}

	else if(wu1<r2 && r2<wl1){
		ant[0][swarm]-=1;
		ant[2][swarm]=3;
	//cout<<"bewegung2_left"<<endl;
	}

	else if(wl1<r2 && r2<1){
		ant[1][swarm]+=1;
		ant[2][swarm]=4;
	//cout<<"bewegung2_down"<<endl;
	}


}

void bewegung3(int** ant, int** r, int** u, int** l, int** d,int swarm, int gridg){
	
	//if(ant[3][swarm]==1){
		
		float wr2, wu2, wl2, wd2;
		int rn, un, ln, dn;
		float total;

		if(ant[0][swarm]==gridg-2){
			ln=l[ant[1][swarm]][1];
			//cout<<"l"<<endl;
		}
		else{
			ln=l[ant[1][swarm]][ant[0][swarm]+1];
		}
		if(ant[0][swarm]==1){
			rn=r[ant[1][swarm]][gridg-2];
			//cout<<"r rand "<<r[ant[1][swarm]][gridg-2]<<endl;
		}
		else{
			rn=r[ant[1][swarm]][ant[0][swarm]-1];
			//cout<<"r nrom "<<r[ant[1][swarm]][ant[0][swarm]-1]<<endl;
		}
		if(ant[1][swarm]==gridg-2){
			un=u[1][ant[0][swarm]];
			//cout<<"u"<<endl;
		}
		else{
			un=u[ant[1][swarm]+1][ant[0][swarm]];
			//cout<<"uperns"<<u[ant[1][swarm]+1][ant[0][swarm]]<<endl;
		}
		if(ant[1][swarm]==1){
			dn=d[gridg-2][ant[0][swarm]];
			//cout<<"d"<<endl;
		}
		else{
			dn=d[ant[1][swarm]-1][ant[0][swarm]];
			//cout<<"downerns "<<d[ant[1][swarm]-1][ant[0][swarm]]<<endl;
		}
		

		total=rn+un+ln+dn;
		//cout<<total<<endl;

		wr2=(float)rn/total;
		wu2=(float)un/total;
		wl2=(float)ln/total;
		wd2=(float)dn/total;
		

					
	wu2 = wu2+wr2;
    wl2 = wl2+wu2;
    wd2 = wd2+wl2;
	

	float r2;
	r2= rand()/(float)(RAND_MAX);

	if(0<r2 && r2<wr2){
		ant[0][swarm]-=1;
		ant[2][swarm]=3;
		//cout<<"rb"<<endl;
	}
	else if(wr2<r2 && r2<wu2){
		ant[1][swarm]+=1;
		ant[2][swarm]=4;
		//cout<<"ub"<<endl;
	}
	else if(wu2<r2 && r2<wl2){
		ant[0][swarm]+=1;
		ant[2][swarm]=1;
		//cout<<"lb"<<endl;
	}
	else if(wl2<r2 && r2<1){
		ant[1][swarm]-=1;
		ant[2][swarm]=2;
		//cout<<"db"<<endl;
	}
	}




void karte(int** ant, int swarm, int gridg){
	//srand((unsigned)time(NULL));
	
	if(ant[0][swarm]==gridg-1 && ant[2][swarm]==1){
		ant[0][swarm]=1;}
	
	else if(ant[1][swarm]==gridg-1 && ant[2][swarm]==4){
		ant[1][swarm]=1;}

	else if(ant[0][swarm]==0 && ant[2][swarm]==3){
		ant[0][swarm]=gridg-2;}

	else if(ant[1][swarm]==0 && ant[2][swarm]==2){
		ant[1][swarm]=gridg-2;}
	
	else if(ant[1][swarm]!=0 || ant[0][swarm]==0 || ant[1][swarm]==gridg-1 || ant[0][swarm]==gridg-1){
	}
	else{
	cout<<"error grider "<<endl;
	}

}

void food(int** ant, int swarm, int food_x, int food_y,int mut, int* gefunden){
	

	if(ant[0][swarm]==food_x && ant[1][swarm]==food_y){
		ant[3][swarm]=1;
		mut=0.0;
	}
	if(*gefunden==0){
		cout<<"trouvee! "<< endl;
		*gefunden=1;
	}
}

void goal(int** ant, int swarm, int start_x, int start_y){
	
	if(ant[0][swarm]==start_x && ant[1][swarm]==start_y){
		ant[3][swarm]=2;
		//cout<<"finished! "<< endl;
	}
}


/*
void bewegung4(int** ant, int** grid, int swarm){

	int rr, uu, ll, dd;
	rr=grid[ant[0][swarm]-1][ant[1][swarm]];
	uu=grid[ant[0][swarm]][ant[1][swarm]+1];
	ll=grid[ant[0][swarm]+1][ant[1][swarm]];
	dd=grid[ant[0][swarm]][ant[1][swarm]-1];

	int total=rr+uu+ll+dd;

	float wrr;

}
*/
void neustart(int** ant, int swarm){
	ant[3][swarm]=3;
	//cout<<"restart"<<endl;

}

void hunger(int** ant, int** grid, int** r, int** u, int** l, int** d, int swarm, int start_x, int start_y){
	
	if(ant[3][swarm]==0){
		ant[0][swarm]=start_x;
		ant[1][swarm]=start_y;
		grid[ant[1][swarm]][ant[0][swarm]]=0;
		grid[ant[1][swarm]+1][ant[0][swarm]]=0;
		grid[ant[1][swarm]][ant[0][swarm]+1]=0;
		grid[ant[1][swarm]][ant[0][swarm]-1]=0;
		grid[ant[1][swarm]-1][ant[0][swarm]]=0;

		r[ant[1][swarm]][ant[0][swarm]]=0;
		r[ant[1][swarm]+1][ant[0][swarm]]=0;
		r[ant[1][swarm]][ant[0][swarm]+1]=0;
		r[ant[1][swarm]-1][ant[0][swarm]]=0;
		r[ant[1][swarm]][ant[0][swarm]-1]=0;

		u[ant[1][swarm]][ant[0][swarm]]=0;
		u[ant[1][swarm]+1][ant[0][swarm]]=0;
		u[ant[1][swarm]][ant[0][swarm]+1]=0;
		u[ant[1][swarm]-1][ant[0][swarm]]=0;
		u[ant[1][swarm]][ant[0][swarm]-1]=0;

		d[ant[1][swarm]][ant[0][swarm]]=0;
		d[ant[1][swarm]+1][ant[0][swarm]]=0;
		d[ant[1][swarm]][ant[0][swarm]+1]=0;
		d[ant[1][swarm]-1][ant[0][swarm]]=0;
		d[ant[1][swarm]][ant[0][swarm]-1]=0;

		l[ant[1][swarm]][ant[0][swarm]]=0;
		l[ant[1][swarm]+1][ant[0][swarm]]=0;
		l[ant[1][swarm]][ant[0][swarm]+1]=0;
		l[ant[1][swarm]-1][ant[0][swarm]]=0;
		l[ant[1][swarm]][ant[0][swarm]-1]=0;
	}

}

