#include "bethepop.h"


myCluster::myCluster()
{
	for (int i = 0; i < Nh; i++){
		for (int j = 0; j < Ns; j++){
			Site[i][j] = (double)((double)rand() / RAND_MAX - 0.5);
		}
	}


}

void myCluster::reweigh_fields_opt(int currSite){

	//generate cumulative
	for (int it = 0; it < Ns; it++){
		
		partition[it] /= partition[Ns-1];
		partitionsite[it] /= partitionsite[Ns - 1];
	}


    for(int it = 0; it < Ns ;it++){

		double myRand = (double)rand() / RAND_MAX;
		int index = search_closest(partition, myRand);

		Site[currSite][it] = h0[index];
	

        myRand = (double)rand()/RAND_MAX;
        index = search_closest(partitionsite,myRand);
        
		Hsite[it] = h0site[index];
		
    }



}

void myCluster::merge_fields_opt(int *J,int *Neigh){

    double shift = 0;
    double u;
    double beta = 1. / T;

    double somma=0;
    double sommasite = 0;
    for (int s = 0; s < Ns ; s++){
        shift = 0;
        h0[s] = 0;
        h0site[s] = 0;
        //merging to update (iteration)

        for (int k = 0; k < K; k++){
            u = T*atanh(tanh(beta*J[k])*
                        tanh(beta*Site[ Neigh[k] ][s]));

            h0[s] += u;

            shift += log(cosh(beta*J[k])/cosh(beta*u));

        }
        dF[s] = shift + log(2*cosh(beta*h0[s]));



        //site contributions
        u = T*atanh(tanh(beta*J[K])*
                    tanh(beta*Site[ Neigh[K] ][s]));

        h0site[s] = h0[s] + u;
        shift += log(cosh(beta*J[K])/cosh(beta*u));

        dFsite[s] = dF[s] +
                shift + log(2*cosh(beta*h0site[s]));
        //w eval


        sommasite +=  exp(dFsite[s]*x_rsb);
        partitionsite[s] =sommasite;


        somma += exp(dF[s]*x_rsb);
        partition[s] =somma;
    }

}

int myCluster::search_closest(double *vec,double val){

    
    for(int i=0;i<Ns;i++){

        if(vec[i]>val){
            return i;
        }

    }

    return Ns;

}