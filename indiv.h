#ifndef INDIV_H
#define INDIV_H

#include <cmath>

#include "window.h"
#include "globals.h"
#include "node.h"
const float scale = 1.0;

class indiv {
public:
	void calc_size(void) {
		int s = 0;
		//if(tree == NULL)
		//	return;
		size = tree->calc_size(s);
	}
	indiv(void);

	void set_nearest_scout(vect v) {
		the_info.nearest_scout = v;
	}
	void set_nearest_invest(vect v) {
		the_info.nearest_invest = v;
	}
	void inc_num_scouts(void) {
		the_info.num_scouts++;
	}
	void set_num_scouts(int s) {
		the_info.num_scouts = s;
	}
	void set_zebra(vect v) {
		the_info.zebra = v;
	}
	void set_nearestcalling(vect v) {
		the_info.nearest_calling = v;
	}
	void set_num_lions(int n) {
		the_info.num_investigators = n;
	}
	void set_num_hyenas(int n) {
		the_info.num_scouts = n;
	}
	void set_calling(bool b) {
		calling = b;
	}
	//     void set_nearest_edge(vect v){the_info.nearest_edge = v;}
	bool get_calling() {
		return calling;
	}
	float getX(void) {
		return x;
	}
	float getY(void) {
		return y;
	}
	float get_fitness(void) {
		return fitness;
	}
	float get_avg_dist_to_zebra(void) {
		return avg_dist_to_zebra;
	}
	float get_lion_attacks(void) {
		return lion_attacks;
	}
	void inc_dist_to_zebra(float d) {
		avg_dist_to_zebra += (d / TIME_STEPS);
	}
	void set_avg_dist_to_zebra(float d) {
		avg_dist_to_zebra = d;
	}
	void inc_lion_attacks(void) {
		lion_attacks++;
	}
	void zero_lion_attacks(void) {
		lion_attacks = 0;
	}
	void rand_move(void);
	void lion_move(void);
	void move(void);
	indiv &operator=(const indiv &);
	void changeFit(float f) {
		fitness += f;
	}
	void mutate(void);
	void clear(void);
	void grow(void);
	void reset(void);
	void reset_fitness(void);
	void set_type(agent_type t) {
		type = t;
	}
	agent_type get_type(void) {
		return type;
	}
	int get_size(void) {
		return size;
	}

	void xOver(indiv*);
private:
	float x;
	float y;
	int size;
	agent_info the_info;
	node *tree;
	float fitness;
	float avg_dist_to_zebra;
	int lion_attacks;
	agent_type type;
	bool calling;
};

#endif
