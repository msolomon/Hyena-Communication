#include "globals.h"

//// Global function definitions

double select_from_numtests(double fitnesses[NUM_TESTS]){
	const int end = (int) ceil(NUM_TESTS/2.0);
	const bool odd = ((NUM_TESTS % 2) == 1);
	double fit;
	switch(COMBINE_METHOD){
	case mean:
		fit = 0;
		for(int i = 0; i < NUM_TESTS; i++){
			fit += fitnesses[i];
		}
		fit /= NUM_TESTS;
		break;
	case median: // do a partial selection sort
		double currval;
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

int poisson_sample(double lambda){
    /* sample from poission distribution, from Knuth: runs in O(lambda) */
    double L = exp(-lambda);
    int k = 0;
    double p = 1;
    do{
        k++;
        p *= Random::Global.FixedN();
    } while(p > L);
    return k - 1;
}

static double spare;
static bool spare_ready = false;
double normal_sample(double mu, double sigma){
    /* Generate random samples using the Marsaglia polar method */
    if(spare_ready){
        spare_ready = false;
        return mu + (spare * sigma);
    }

    double u, v, s;
    do{
        u = Random::Global.FixedW();
        v = Random::Global.FixedW();
        s = (u * u) + (v * v);
    } while(s >= 1 || s == 0);

    spare = v * sqrt(-2.0 * (log(s) / s));
    spare_ready = true;

    return mu + sigma * u * sqrt(-2.0 * (log(s) / s));
}
