#include "mySystem.h"


mySystem::mySystem()
{
	for (int it = 0; it < Nh; it++){
		for (int jt = 0; jt < Nh; jt++){
			J_matrix[it][jt] = ((rand())>.5*RAND_MAX) * 2 - 1;
			J_matrix[jt][it] = J_matrix[it][jt];
		}
	}
}

mySystem::~mySystem()
{
}

void mySystem::choose_sites(){


	for (int it = 0; it < 2 * K; it++){
		if (it < K + 1){
			siteNeighs[it] = rand() % Nh;
			while(siteNeighs[it] == currSiteIndex){
				siteNeighs[it] = rand() % Nh;
			}
			//Jsite[it] = ((rand()) > .5*RAND_MAX) * 2 - 1;
			Jsite[it] = J_matrix[currSiteIndex][siteNeighs[it]];
		
		}
		if (it < K){
			iterNeighs[it] = rand() % Nh;
			while (iterNeighs[it] == currSiteIndex){
				iterNeighs[it] = rand() % Nh;
			}
			//Jiter[it] = ((rand())>.5*RAND_MAX) * 2 - 1;
			Jiter[it] = J_matrix[currSiteIndex][siteNeighs[it]];
		}

		linkNeighs[it] = rand() % Nh;
		Jlink[it] = ((rand()) > .5*RAND_MAX) * 2 - 1;
	}
	
}

void mySystem::merge_fields(){

	// evaluate for each cluster & state the 
	// merged field and the free energy
	double u, usite, ulink;
	double beta = 1. / T;
	double shift,shiftsite,shiftlink1,shiftlink2;

	double h0,h0site,h0link,g0link;

	for (int cit = 0; cit < Nc; cit++){
		for (int sit = 0; sit < Nc; sit++)
		{
			h0 = 0;
			h0site = 0;
			h0link=0;
			g0link = 0;
			shift = 0;
			shiftsite = 0;
			shiftlink1 = 0;
			shiftlink2 = 0;
			for (int k = 0; k < 2 * K; k++){
				if (k < K){
					u = T*atanh(tanh(beta*Jiter[k])*
						tanh(beta*Site[iterNeighs[k]].Cluster[cit].State[sit]));
					h0 += u;
					shift += log(cosh(beta*Jiter[k]) / cosh(beta*u));
				}
				if (k < K + 1){
					usite = T*atanh(tanh(beta*Jsite[k])*
						tanh(beta*Site[siteNeighs[k]].Cluster[cit].State[sit]));
					shiftsite += log(cosh(beta*Jsite[k]) / cosh(beta*usite));
					h0site += usite;
				}
				if (k < K){
					ulink = T*atanh(tanh(beta*Jlink[k])*
						tanh(beta*Site[linkNeighs[k]].Cluster[cit].State[sit]));
					h0link += ulink;
					shiftlink1 += log(cosh(beta*Jlink[k]) / cosh(beta*ulink));
				}
				else{
					ulink = T*atanh(tanh(beta*Jlink[k])*
						tanh(beta*Site[linkNeighs[k]].Cluster[cit].State[sit]));
					g0link += ulink;
					shiftlink2 += log(cosh(beta*Jlink[k]) / cosh(beta*ulink));
					
				}
			}
			//add low noise
			
			double noise = 0.0001;

			h0 += noise*((double)rand() / RAND_MAX - 0.5);
			h0site += noise*((double)rand() / RAND_MAX - 0.5);
			h0link += noise*((double)rand() / RAND_MAX - 0.5);
			g0link += noise*((double)rand() / RAND_MAX - 0.5);

			double J0 = ((rand())>.5*RAND_MAX) * 2 - 1;

			double v0 = T*atanh((tanh(beta*J0) + tanh(beta*h0link)*tanh(beta*g0link)) /
				(1 + tanh(beta*J0)*tanh(beta*h0link)*tanh(beta*g0link)));

			currSite->Cluster[cit].State[sit] = h0;
			currSite->Cluster[cit].siteState[sit] = h0site;
			currSite->Cluster[cit].linkState[sit] = v0;

			double newlinkshift = 0;
			double expo=0;
			double sigma, tau;

			
			for (int tau = -1; tau <= 1; tau = tau + 2){
				for (int sigma = -1; sigma <= 1; sigma = sigma + 2){
					expo += exp(beta*J0*sigma*tau + beta*sigma*h0link + beta*tau*g0link);
				}
			}

			newlinkshift = log(expo);

			currSite->Cluster[cit].dFiter[sit] = shift + log(2 * cosh(beta*h0));
			currSite->Cluster[cit].dFsite[sit] = shift + log(2 * cosh(beta*h0site));
			currSite->Cluster[cit].dFlink[sit] = shiftlink1 + shiftlink2 + newlinkshift;
		}

	}

}

void mySystem::evaluate_observables(){

	//free energy
	MEAN = 0;
	double beta = 1 / T;
	
	q0 = 0; q1 = 0; q2 = 0;
	int c0 = 0, c1 = 0, c2 = 0;
	for (int it = 0; it < Nh; it++){

		MEAN += Site[it].FREE_ENERGY2;

	}
	
	for (int it = 0; it < Nh; it++){

		q0 += Site[it].q0;
		q1 += Site[it].q1;
		q2 += Site[it].q2;
	}
	
	MEAN /= Nh;
	q0 /= Nh; q1 /= Nh; q2 /= Nh;
}

void mySystem::write_file(){

	

		fileStream.open(FILE_NAME_XY, fstream::app);
		fileStream << " " << MEAN;
		fileStream.close();
		fileStream.open(FILE_NAME_Q, fstream::app);
		fileStream << q0 << " " << q1 << " " << q2 << endl;
}


