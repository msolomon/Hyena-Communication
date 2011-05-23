#ifndef TEAM_H
#define TEAM_H

#include "globals.h"
#include "indiv.h"

class team {
public:
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
	float get_hyena_fit(int i) {
		return hyena_fits[i];
	}
//	float get_invest_fit(int i) {
//		return invest_fits[i];
//	}
	float get_avg_dist_to_zebra(void) {
		return avg_dist_to_zebra;
	}
	float get_avg_lion_attacks(void) {
		return avg_lion_attacks;
	}
	void reset_fitness(void);

	indiv hyenas[NUM_HYENAS];
	indiv lions[NUM_LIONS];
	float hyena_fits[NUM_HYENAS];
//	float invest_fits[NUM_LIONS];
	float avg_fit;
	float avg_lion_attacks;
	float avg_dist_to_zebra;
};

#endif
