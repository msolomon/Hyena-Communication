#ifndef POP_H
#define POP_H

#include "globals.h"
#include "indiv.h"
#include "team.h"
#include "environment.h"
#include "helper.h"

class pop: public QObject {
	Q_OBJECT
public:
	pop();
	void generate(Helper*);
	void generate();
	void run();
	int select_best(int, agent_type);
	int select_best_team(int);
	int tourn_select(int, agent_type);
	int tourn_select(int);
	//     void get_fitnesses(void);
	void write_fitnesses(void);
	void save_data(int, int);
	void evolve(int);
	void evaluate_agent(int, int, int);
	void evaluate_team(int, int, int);
	void evaluate_team(int, int);
	void team_reproduce();
	void member_reproduce();
	void island_reproduce();
	void OET1_reproduce();
	void oet_generational();
	int member_select(int, int, agent_type);
private:
	//     float fitnesses_scouts[POP_SIZE];
	//    float fitnesses_investigators[POP_SIZE];
	environment ENV;
	team *the_pop[POP_SIZE];
	float data[(TEAM_SIZE * 2 + 4) * TRIALS][ITERATIONS];
	float pop_bestfitness;
	int pop_bestteam;
	Helper *helper;

signals:
	void next_calc_iteration(QString);
	void calc_iteration_total(QString);
	void calc_percent(int);
	void calc_percent_total(int);

};

#endif
