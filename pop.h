#ifndef POP_H
#define POP_H

#include <vector>

#include "globals.h"
#include "indiv.h"
#include "indiv_nn.h"
#include "indiv_hybrid.h"
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
//	void write_fitnesses(void);
//	void save_data(int, int);
    void write_data(int trial, int iteration);
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
    void all_generational(int generation);
	int member_select(int, int);
	void add_blank_nodes();
	void draw_best(int, int);
	void serialize_best(const char*);
    void final_test(int trial,
                    const char* const video_template,
                    const char* const data_template,
                    const ops disabled[],
                    int disabled_len);
	qint64 trialstarttime;
	DrawHelper *helper;
	environment *ENV;
private:
	//     double fitnesses_scouts[POP_SIZE];
	//    double fitnesses_investigators[POP_SIZE];
	team *the_pop[POP_SIZE];
//        double data[(TEAM_SIZE * 2 + 4) * TRIALS][ITERATIONS];
	// data. all team fitnesses plus 8 iteration attributes (avg. and soforth)
	static const int NUM_EXTRA = 15;
    double data[NUM_EXTRA + NUM_OPS + 3*NUM_HYENAS];
	double pop_bestfitness;
	int pop_bestteam;

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
