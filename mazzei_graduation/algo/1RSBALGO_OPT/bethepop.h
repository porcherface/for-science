#ifndef BETHEPOP_H
#define BETHEPOP_H

#include "defines.h"

class myCluster{

public:

    myCluster();

    double x_rsb;

    void merge_fields_opt(int *,int *);
    void reweigh_fields_opt(int);

    double Site[Nh][Ns];
    double Hsite[Ns];

    double dF[Ns];
    double dFsite[Ns];


    double h0[Ns];
    double h0site[Ns];
    double weights[Ns];
    double partition[Ns];
    double partitionsite[Ns];

	double mean_F;

    int search_closest(double *,double);
};



class myPopulation{
public:

    myPopulation();

	int J[K + 1];

    class myCluster Cluster[Nc];
    class myCluster* currCluster;

	void choose_sites();

	void evaluate_site();
	void evaluate_bond();

    void write_file();

    int currSiteIdx;
    int currStateIdx;
    int currClusterIdx;

    int NeighIdx[K + 1];

    int time;
 

	//observ.
	
    double q_samestate[Nh];
	double q_interstate[Nh];
	double q_intercluster[Nh];
	double site_f;
	double bond_f;
    double energy;

    double J_matrix[Nh][Nh];

	std::stringstream  sstream;
	std::ofstream dStream;


};


#endif // BETHEPOP_H
