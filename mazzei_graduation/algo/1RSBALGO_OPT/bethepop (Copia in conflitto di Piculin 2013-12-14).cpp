#include "bethepop.h"


myPopulation::myPopulation(){

     remove( FILE_NAME_SITE );
     remove( FILE_NAME_FIELD );

    for(int it=0;it<Nc;it++){

        Cluster[it].x_rsb = .24;
    }
    for(int it=0;it<Nh;it++)
    {for(int jt=0;jt<=2*K+2;jt++)
    {
            J_matrix[it][jt] = ((rand())>.5*RAND_MAX) * 2 - 1;

        }
    }
}

void myPopulation::evaluate_site(){


    double beta = 1. / T;
    //currSiteIdx = time%Nh;
    q_samestate[currSiteIdx]  = 0.;
    q_interstate[currSiteIdx] = 0.;

    int counter1=0,counter2=0;

    for (int it = 0; it < Ns; it++){
        q_samestate[currSiteIdx] += tanh(beta*currCluster->Hsite[it])*tanh(beta*currCluster->Hsite[it]);
        counter1++;
        for(int jt=0; jt<Ns;jt++){
			if (it != jt){
                q_interstate[currSiteIdx] += tanh(beta*currCluster->Hsite[it])*
                    tanh(beta*currCluster->Hsite[jt]);
                counter2++;
			}
		}

	}
    q_samestate[currSiteIdx] /=counter1;
    q_interstate[currSiteIdx] /=counter2;


}

void myPopulation::evaluate_bond(){


}

void myPopulation::choose_sites(){

    for (int it = 0; it < 2 * K + 2; it++){
        NeighIdx[it] = rand() % Nh;
        J[it] = J_matrix[currSiteIdx][it];
        //J[it] = ((rand())>.5*RAND_MAX) * 2 - 1;
    }

}

void myPopulation::write_file(){

    //writing
    cout << "writing on " << FILE_NAME_FIELD << "..." << endl;

    dStream.open(FILE_NAME_FIELD, fstream::app);

    int hit = 0;
    int cit = 0;

    for (int sit = 0; sit < Ns; sit++){

        dStream << Cluster[cit].Site[hit][sit]<< " ";
    }

    dStream << endl;
    dStream.close();

    dStream.open(FILE_NAME_SITE, fstream::app);


    for(int it = 0;it<Nh;it++){
        dStream << q_samestate[it] << " ";
        dStream << q_interstate[it] << " ";
    }dStream << endl;

    dStream.close();

}


myCluster::myCluster()
{
    for (int i = 0; i < Nh; i++){
        for (int j = 0; j < Ns; j++){
            Site[i][j] = K*(double)((double)rand() / RAND_MAX - 0.5);
        }
    }


}
