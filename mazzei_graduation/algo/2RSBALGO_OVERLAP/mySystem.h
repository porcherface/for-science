#pragma once
#include "defines.h"


class myCluster
{
public:
	myCluster();
	~myCluster();

	double State[Ns];
	double siteState[Ns];
	double linkState[Ns];

	double appSite[Ns];
	double appIter[Ns];
	double appLink[Ns];

	double dFiter[Ns];
	double dFsite[Ns];
	double dFlink[Ns];

	double appdFiter[Ns];
	double appdFsite[Ns];
	double appdFlink[Ns];

	double Fiter;
	double Flink;
	double Fsite;

	double x_rsb;

	double cumulativeIter[Ns];
	double cumulativeSite[Ns];
	double cumulativeLink[Ns];

	void reweigh();
	void evaluate();

};

class mySite
{
public:
	mySite();
	~mySite();

	class myCluster Cluster[Nc];
	class myCluster appCluster[Nc];

	double y_rsb;

	double cumulativeIter[Ns];
	double cumulativeSite[Ns];
	double cumulativeLink[Ns];

	void reweigh();
	void evaluate();

	double Fiter;
	double Fsite;
	double Flink;

	double FREE_ENERGY;
	double FREE_ENERGY2;

	double q0, q1, q2;
};

class mySystem
{

public:
	mySystem();
	~mySystem();

	int J_matrix[Nh][Nh];

	class mySite Site[Nh];
	class mySite *currSite;

	int time;
	int currSiteIndex;

	//methods
	void choose_sites();
	void write_file();

	void merge_fields();

	//neighbors
	int siteNeighs[K + 1], Jsite[K + 1];
	int linkNeighs[2 * K], Jlink[2 * K];
	int iterNeighs[K], Jiter[K];

	void evaluate_observables();
	fstream fileStream;

	double MEAN;
	double q0, q1, q2;
};


