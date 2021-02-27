#include "defines.h"

int main(){

	//be polite	
	cout << "hello!";


	//random seed for randStream
	srand(0);

	//remove previous data
	remove(FILE_NAME_XY);

	//initialize variables
	mySystem Sys;
	
	//init del sistema
	const int NUMSIM = 1;
	double x_sample[NUMSIM];
	double y_sample[NUMSIM];

	for (int it = 0; it < NUMSIM; it++){

		x_sample[it] = 0.07;
			y_sample[it] = 0.45;
	}

	int TOTSIM = NUMSIM*NUMSIM;
	int sim_number = 0;
	for (int currSim1 = 0; currSim1 < NUMSIM; currSim1++){

		for (int currSim2 = 0; currSim2 < NUMSIM; currSim2++){
			
			
			//init per single run
			
			for (int jt = 0; jt < Nh; jt++){
				Sys.Site[jt].y_rsb = y_sample[currSim1];
				for (int it = 0; it < Nc; it++){
					Sys.Site[jt].Cluster[it].x_rsb = x_sample[currSim2];
					for (int kt = 0; kt < Ns; kt++){
					
						Sys.Site[jt].Cluster[it].State[kt] =( (double)rand() / RAND_MAX - .5)* 2 * K;
					}
				}
			}

			Sys.fileStream.open(FILE_NAME_XY, fstream::app);
			Sys.fileStream << y_sample[currSim1] << " " << x_sample[currSim2];

			sim_number++;
			cout << endl << "Performing sim " << sim_number << " of " << TOTSIM << "..." << endl;


			//////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////
			Sys.time = 0;
			while (Sys.time < MAX_TIME)
			{
				
				//choose indexes
				Sys.currSiteIndex = Sys.time%Nh;
				Sys.currSite = &Sys.Site[Sys.currSiteIndex];

				Sys.choose_sites();

				//merge 
				Sys.merge_fields();

				//reweigh
				Sys.currSite->reweigh();

				//evaluate free energy
				Sys.currSite->evaluate();

				if (Sys.time > BIAS && Sys.time % Nh == 0){

					//observables
					Sys.evaluate_observables();
					Sys.write_file();
				}

				if (Sys.time == MAX_TIME / 2){
					cout << "Halfway done ";
					cout << "(F: " << Sys.MEAN << ")";
				}
				if (Sys.time % (MAX_TIME / 20) == 0){
					cout << ".";
				}

				Sys.time++;
				if (Sys.time == MAX_TIME){
					cout << "Done!";
					cout << "(F: " << Sys.MEAN << ")";
				}

			}//endsim

			Sys.fileStream.open(FILE_NAME_XY, fstream::app);
			Sys.fileStream << endl;
			Sys.fileStream.close();

		}
	}//endall
	return 0;
}
