#ifndef POP_H
#define POP_H

#include "globals.h"
#include "indiv.h"
#include "team.h"
#include "environment.h"
#include "drawhelper.h"

class pop: public QObject {
	Q_OBJECT
public:
	pop();
	~pop();
	void generate();
	void run();
	int select_best_team(int);
	int tourn_select(int);
        // TODO: fix TEAM_SIZE and re-enable calls to write_fitnesses and save_data
//	void write_fitnesses(void);
//	void save_data(int, int);
	void write_data(int);
	void save_data(int);
	void evolve_repeat();
	void evolve_repeat(int);
	void evolve(int);
	void evaluate_agent(int, int, int);
	void evaluate_team(int);
	void evaluate_team(team *);
	void team_reproduce();
	void member_reproduce();
	void island_reproduce();
	void OET1_reproduce();
	void all_generational();
	int member_select(int, int);
	void add_blank_nodes();
	void draw_best(int, int);
	qint64 trialstarttime;
	DrawHelper *helper;
	environment *ENV;
private:
	//     float fitnesses_scouts[POP_SIZE];
	//    float fitnesses_investigators[POP_SIZE];
	team *the_pop[POP_SIZE];
//        float data[(TEAM_SIZE * 2 + 4) * TRIALS][ITERATIONS];
	// data. all team fitnesses plus 8 iteration attributes (avg. and soforth)
	static const int NUM_EXTRA = 7;
	float data[GENERATIONS][NUM_EXTRA + NUM_TERMS+NUM_NON_TERMS + 3*NUM_HYENAS];
	float pop_bestfitness;
	int pop_bestteam;
	int pop_worstteam;

signals:
	void calc_iter(QString);
	void calc_iter_total(QString);
	void calc_trial(QString);
	void calc_trial_total(QString);
	void calc_iter_percent(int);
	void calc_iter_percent_total(int);
	void calc_trial_percent(int);
	void calc_trial_percent_total(int);

};

#endif
