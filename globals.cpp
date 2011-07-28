#include "globals.h"

//// Global function definitions

float select_from_numtests(float fitnesses[NUM_TESTS]){
	const int end = ceil(NUM_TESTS/2.0);
	const bool odd = ((NUM_TESTS % 2) == 1);
	float fit;
	switch(SELECTION_METHOD){
	case mean:
		fit = 0;
		for(int i = 0; i < NUM_TESTS; i++){
			fit += fitnesses[i];
		}
		fit /= NUM_TESTS;
		break;
	case median: // do a partial selection sort
		float currval;
		int currloc;
		for(int i = 0; i < end; i++){
			currloc = i;
			currval = fitnesses[i];
			// find smallest
			for(int j = i + 1; j < NUM_TESTS; j++){
				if(fitnesses[j] < currval){
					currval = fitnesses[j];
					currloc = j;
				}
			}
			// now swap them
			fitnesses[currloc] = fitnesses[i];
			fitnesses[i] = currval;
		}
		if(odd) fit = fitnesses[end];
		else fit = (fitnesses[end-1] + fitnesses[end]) / 2.0;
		break;
	case minimum:
		fit = fitnesses[0];
		for(int i = 1; i < NUM_TESTS; i++)
			if(fitnesses[i] < fit) fit = fitnesses[i];
		break;
	case maximum:
		fit = fitnesses[0];
		for(int i = 1; i < NUM_TESTS; i++)
			if(fitnesses[i] > fit) fit = fitnesses[i];
		break;
	}
	return fit;
}
