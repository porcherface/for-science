#include "bethepop.h"


myPopulation::myPopulation(){

     remove( FILE_NAME_SITE );
     
	 dStream.open(FILE_NAME_FIELD,fstream::app);

	 dStream << Ns << " ";


    for(int it=0;it<Nc;it++){

        Cluster[it].x_rsb = .24;
    }
    for(int it=0;it<Nh;it++)
    {for(int jt=0;jt<=it;jt++)
    {
            J_matrix[it][jt] = ((rand())>.5*RAND_MAX) * 2 - 1;
            J_matrix[jt][it] = J_matrix[it][jt];

        }
    }
}

void myPopulation::choose_sites(){

	for (int it = 0; it < K + 1; it++){
		NeighIdx[it] = rand() % Nh;
		J[it] =// J_matrix[currSiteIdx][it];
			((double)rand()>(double)RAND_MAX / 2) * 2 - 1;
	}

}

void myPopulation::evaluate_site(){


    double beta = 1. / T;
    //currSiteIdx = time%Nh;
    q_samestate[currSiteIdx]  = 0.;
    q_interstate[currSiteIdx] = 0.;

    int counter1=0,counter2=0;

    for (int it = 0; it < Ns; it++){
        for(int jt=0; jt<Ns;jt++){
			if (it != jt){
                q_interstate[currSiteIdx] += tanh(beta*currCluster->Hsite[it])*
                    tanh(beta*currCluster->Hsite[jt]);
                counter2++;
			}
			else{
				q_samestate[currSiteIdx] += tanh(beta*currCluster->Hsite[it])*tanh(beta*currCluster->Hsite[it]);
				counter1++;			
			
			}

		}

	}
    q_samestate[currSiteIdx] /=counter1;
    q_interstate[currSiteIdx] /=counter2;

	double sum = 0;
	double sumprime = 0;
	
	for (int it = 0; it < Ns; it++){

		sum += exp(-beta*currCluster->x_rsb*currCluster->dF[it]);
		sumprime += exp(-beta*currCluster->x_rsb*currCluster->dFsite[it]);

	}


	double fprime = (-1 / (beta*currCluster->x_rsb))*log(sum / Ns);
	double site_f = (-1 / (beta*currCluster->x_rsb))*log(sumprime / Ns);

	currCluster->mean_F = (K + 1) / 2 * fprime - (K - 1) / 2 * site_f;
}

void myPopulation::write_file(){

    //writing
    cout << "writing on " << FILE_NAME_FIELD << "..." << endl;

    dStream.open(FILE_NAME_FIELD, fstream::app);

    int hit = 0;
    int cit = 0;

    
        dStream << Cluster[cit].mean_F<< " ";
    
    dStream.close();

    dStream.open(FILE_NAME_SITE, fstream::app);


    for(int it = 0;it<Nh;it++){
        dStream << q_samestate[it] << " ";
        dStream << q_interstate[it] << " ";
    }dStream << endl;

    dStream.close();

}
