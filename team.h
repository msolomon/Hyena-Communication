#ifndef TEAM_H
#define TEAM_H

#include "globals.h"
#include "indiv_hybrid.h"
#include "indiv_nn.h"
#include "indiv.h"
#include <fstream>
#include <QFile>
#include <QTextStream>

class team {
public:
	team();
    ~team();
    double recalc_team_avg_fit();
	double calc_team_fit();
	double write_team_fit_final(std::ofstream&, int, int, int, int);
	double get_team_fit() {
		return this->team_fit;
	}
    int get_size();
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
    void apply_parsimony();
	double get_hyena_fit(int i) {
		return hyena_fits[i];
	}
	double get_avg_dist_to_zebra() {
		return avg_dist_to_zebra;
	}
	double get_avg_lion_attacks() {
		return avg_lion_attacks;
	}
    double get_avg_penalty() {
        return avg_penalty;
    }
	double get_avg_reward() {
		return avg_reward;
	}
    double get_avg_parsimony() {
        return avg_parsimony;
    }
	double get_avg_hits() {
		return avg_hits;
	}
	double* get_uses(){
		return (double*) &uses;
	}
	double* get_importance(){
		return (double*) &importance;
	}
	void force_fitness(double fit){
		team_fit = fit;
	}
	void get_leaders(int &leader_idx, int &leader_score,
					 int &leader2_idx, int &leader2_score);
	void reset_fitness(void);
	QStringList serialize();
	void deserialize(QStringList);
	void load_team(QString filename);
    indiv_base *hyenas[NUM_HYENAS];
    indiv lions[NUM_LIONS]; // internals of ann/vet aren't used anyway
	double hyena_fits[NUM_HYENAS];
	double team_fit; // SELECTION_METHOD team fitness
	double avg_lion_attacks;
    double avg_penalty;
	double avg_reward;
    double avg_parsimony;
	double avg_dist_to_zebra;
	double avg_hits;
	double avg_size;
	double uses[NUM_OPS];
	double importance[NUM_OPS];
	int *leadership;
};

#endif
