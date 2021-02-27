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
	init();


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
		}
		if (Sys.time % (MAX_TIME / 10) == 0){
			cout << ".";
		}

		Sys.time++;

	}//endsim

	return 0;
}
