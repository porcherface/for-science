#include "mySystem.h"


myCluster::myCluster()
{
}

myCluster::~myCluster()
{
}

void myCluster::reweigh()
{


	// get weights
	for (int it = 0; it < Ns; it++){
		cumulativeIter[it] = exp(x_rsb*dFiter[Ns]);
		cumulativeSite[it] = exp(x_rsb*dFsite[Ns]);
		cumulativeLink[it] = exp(x_rsb*dFlink[Ns]);

		if (it>0){
			cumulativeSite[it] += cumulativeSite[it - 1];
			cumulativeIter[it] += cumulativeIter[it - 1];
			cumulativeLink[it] += cumulativeLink[it - 1];
		}
	}

	//reweigh
	for (int it = 0; it < Ns; it++){

		double myRand = (double)rand() / RAND_MAX * cumulativeIter[Ns - 1];
		int index = search_closest(cumulativeIter, myRand);

		appIter[it] = State[index];
		//appdFiter[it] = dFiter[index];

		myRand = (double)rand() / RAND_MAX * cumulativeSite[Ns - 1];
		index = search_closest(cumulativeSite, myRand);

		appSite[it] = siteState[index];
		//appdFsite[it] = dFsite[index];

		myRand = (double)rand() / RAND_MAX * cumulativeLink[Ns - 1];
		index = search_closest(cumulativeLink, myRand);

		appLink[it] = linkState[index];
		//appdFlink[it] = dFlink[index];
		

	}

	for (int it = 0; it < Ns; it++){
		State[it] = appIter[it];
		siteState[it] = appSite[it];
		linkState[it] = appLink[it];
		//dFiter[it] = appdFiter[it];
		//dFsite[it] = appdFsite[it];
		//dFlink[it] = appdFlink[it];
		
		
	}

}

void myCluster::evaluate(){
	 
	double sum = 0, sumsite = 0, sumlink = 0;

	for (int it = 0; it < Ns; it++){
	sum     += exp(x_rsb*dFiter[it]);
	sumsite += exp(x_rsb*dFsite[it]);
	sumlink += exp(x_rsb*dFlink[it]);
	}

	Fsite = (1 / x_rsb)*log(sumsite / Ns);
	Fiter = (1 / x_rsb)*log(sum / Ns);
	Flink = (1 / x_rsb)*log(sumlink / Ns);
}