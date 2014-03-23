#include <iostream>
using namespace std;


void grider1(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm)
{
	if(ant[2][swarm]==1){
		r[(ant[1][swarm])][(ant[0][swarm])-1] += 1;
        grid[(ant[1][swarm])][(ant[0][swarm])-1] += 1;
		//cout<<"grid_raechts"<<grid[(ant[0][swarm])-1][(ant[1][swarm])]<<endl;
	}

    else if (ant[2][swarm]==2){
        u[(ant[1][swarm])+1][(ant[0][swarm])] += 1;
        grid[(ant[1][swarm])+1][(ant[0][swarm])] += 1;
		//cout<<"grid_up"<<grid[(ant[0][swarm])][(ant[1][swarm])-1]<<endl;
	}

    else if (ant[2][swarm]==3){
        l[(ant[1][swarm])][(ant[0][swarm])+1] += 1;
        grid[(ant[1][swarm])][(ant[0][swarm])+1] += 1;
		//cout<<"grid_left"<<grid[(ant[0][swarm])+1][(ant[1][swarm])]<<endl;
	}

	else if (ant[2][swarm]==4){
        d[(ant[1][swarm])-1][(ant[0][swarm])] += 1;
        grid[(ant[1][swarm])-1][(ant[0][swarm])] += 1;
		//cout<<"grid_down"<<grid[(ant[0][swarm])][(ant[1][swarm]+1)]<<endl;
	}

}

void grider2(int** ant, int** u, int** r, int** d, int** l, int** grid, int swarm, int gridg){


	if(ant[2][swarm]==1){
		grid[ant[1][swarm]][ant[0][swarm]-1]+=1;
		if(ant[0][swarm]==gridg-1){
			l[ant[1][swarm]][1]+=1;
		}
		else{
		l[ant[1][swarm]][ant[0][swarm]]+=1;
		}
	}

	else if(ant[2][swarm]==2){
		grid[ant[1][swarm]+1][ant[0][swarm]]+=1;
		
		if(ant[1][swarm]==0){
			d[gridg-2][ant[0][swarm]]+=1;
		}
		else{
			d[ant[1][swarm]][ant[0][swarm]]+=1;
		}
	}
	else if(ant[2][swarm]==3){
		
		grid[ant[1][swarm]][ant[0][swarm]+1]+=1;

		if(ant[0][swarm]==0){
			r[ant[1][swarm]][gridg-2] +=1;
		}
		else{
		r[ant[1][swarm]][ant[0][swarm]]+=1;
		}
	}

	else if(ant[2][swarm]==4){

		grid[ant[1][swarm]-1][ant[0][swarm]]+=1;

		if(ant[1][swarm]==gridg-1){
			u[1][ant[0][swarm]] += 1;
		}
		else{
		u[ant[1][swarm]][ant[0][swarm]]+=1;
		}
	}
}