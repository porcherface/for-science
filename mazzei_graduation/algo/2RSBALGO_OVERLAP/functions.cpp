#include "defines.h"

int search_closest(double *vec, double val){


	for (int i = 0; i<Ns; i++){

		if (vec[i]>val){
			return i;
		}

	}

	return Ns;

}
