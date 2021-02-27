#include "mySystem.h"


mySite::mySite()
{
}

mySite::~mySite()
{
}


void mySite::reweigh(){

	for (int it = 0; it < Nc; it++){
		
		Cluster[it].reweigh();
		Cluster[it].evaluate();
			
		cumulativeIter[it] = exp(y_rsb*Cluster[it].Fiter);
		cumulativeSite[it] = exp(y_rsb*Cluster[it].Fsite);
		cumulativeLink[it] = exp(y_rsb*Cluster[it].Flink);

		if (it>0){
			cumulativeSite[it] += cumulativeSite[it - 1];
			cumulativeIter[it] += cumulativeIter[it - 1];
			cumulativeLink[it] += cumulativeLink[it - 1];
		}
	}

	//reweigh
	for (int it = 0; it < Nc; it++){

		double myRand = (double)rand() / RAND_MAX * cumulativeIter[Nc - 1];
		int index = search_closest(cumulativeIter, myRand);

		double myRandSite = (double)rand() / RAND_MAX * cumulativeSite[Nc - 1];
		int indexSite = search_closest(cumulativeSite, myRandSite);

		double myRandLink = (double)rand() / RAND_MAX * cumulativeLink[Nc - 1];
		int indexLink = search_closest(cumulativeLink, myRandLink);

		for (int jt = 0; jt < Ns; jt++){
		
			appCluster[it].State[jt] = Cluster[index].State[jt];
			//appCluster[it].Fiter = Cluster[index].Fiter;
			
			appCluster[it].siteState[jt] = Cluster[index].siteState[jt];
			//appCluster[it].Fsite = Cluster[index].Fsite;

			appCluster[it].linkState[jt] = Cluster[index].linkState[jt];
			//appCluster[it].Flink = Cluster[index].Flink;

		}
	}

	for (int it = 0; it < Nc; it++){
		for (int jt = 0; jt < Ns; jt++){

			Cluster[it].State[jt] = appCluster[it].State[jt];
			//Cluster[it].Fiter = appCluster[it].Fiter;

			Cluster[it].siteState[jt]=appCluster[it].siteState[jt];
			//Cluster[it].Fsite= appCluster[it].Fsite;
			
			Cluster[it].linkState[jt] = appCluster[it].linkState[jt];
			//Cluster[it].Flink = appCluster[it].Flink;

		
		}
	}

}

void mySite::evaluate(){

	double beta = 1 / T;

	double sum = 0, sumsite = 0, sumlink = 0;

	for (int it = 0; it < Nc; it++){
		sum += exp(y_rsb*Cluster[it].Fiter);
		sumsite += exp(y_rsb*Cluster[it].Fsite);
		sumlink += exp(y_rsb*Cluster[it].Flink);
	}

	Fsite = (-1 / beta/ y_rsb)*log(sumsite / Nc);
	Fiter = (-1 / beta/ y_rsb)*log(sum / Nc);
	Flink = (-1 / beta / y_rsb)*log(sumlink / Nc);

	FREE_ENERGY = Fiter*(K + 1) / 2  - Fsite*(K - 1) / 2;
	FREE_ENERGY2 = Flink*(K + 1) / 2  - K*Fsite;
	int c0 = 0, c1 = 0, c2 = 0;

	for (int jt = 0; jt < Nc; jt++){
		for (int kt = 0; kt < Ns; kt++){

			for (int jjt = 0; jjt < Nc; jjt++){
				for (int kkt = 0; kkt < Ns; kkt++){

					if (kkt != kt){
						if (jt != jjt){
							q2 = tanh(beta*Cluster[jt].siteState[kt])*
								tanh(beta*Cluster[jjt].siteState[kkt]);
							c2++;

						}
						else{
							q1 = tanh(beta*Cluster[jt].siteState[kt])*
								tanh(beta*Cluster[jjt].siteState[kkt]);
							c1++;

						}

					}
					else{
						q0 = tanh(beta*Cluster[jt].linkState[kt])*
							tanh(beta*Cluster[jt].linkState[kt]);
						c0++;
					}
				}
			}
		}
	}
}