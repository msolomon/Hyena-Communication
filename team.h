#ifndef TEAM_H
#define TEAM_H

#include "globals.h"
#include "indiv.h"

class team {
public:
	team();
	float calc_avg_fit();
	float get_avg_fit() {
		return this->avg_fit;
	}
	void calc_size();
	void mutate();
	void mutate(int);
	void xOver(team *);
	void xOver(team *, int);
	void copy(team *);
	void copy(team *, int);
	void generate(void);
	void clear(void);
	void reset_team(void);
	void reset_inputs();
	float get_hyena_fit(int i) {
		return hyena_fits[i];
	}
	float get_avg_dist_to_zebra() {
		return avg_dist_to_zebra;
	}
	float get_avg_lion_attacks() {
		return avg_lion_attacks;
	}
    float get_avg_penalty() {
        return avg_penalty;
    }
	float get_avg_hits() {
		return avg_hits;
	}
	float* get_uses(){
		return (float*) &uses;
	}
	double* get_importance(){
		return (double*) &importance;
	}
	void reset_fitness(void);
	void reset_calling();
	indiv hyenas[NUM_HYENAS];
	indiv lions[NUM_LIONS];
	float hyena_fits[NUM_HYENAS];
	float avg_fit; // average team fitness
	float avg_lion_attacks;
    float avg_penalty;
	float avg_dist_to_zebra;
	float avg_hits;
	float avg_size;
	float uses[NUM_OPS];
	double importance[NUM_OPS];
};

#endif
