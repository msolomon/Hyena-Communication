#ifndef INDIV_H
#define INDIV_H

#include <cmath>

#include "globals.h"
#include "node.h"

class indiv {
public:
	void calc_size(void) {
		//if(tree == NULL)
		//	return;
		size = tree->calc_size();
	}
	indiv(void);

	void set_nearest_hyena(vect v) {
		the_info.nearest_hyena = v;
	}
	void set_nearest_lion(vect v) {
		the_info.nearest_lion = v;
	}
	void inc_num_hyenas(void) {
		the_info.num_hyenas++;
	}
	void set_zebra(vect v) {
		the_info.zebra = v;
	}
	void set_nearestcalling(vect v) {
		the_info.nearest_calling = v;
	}
	void set_leader(vect v) {
		the_info.leader = v;
	}
	void set_mirrored(vect v){
		the_info.mirrored = v;
	}
	void set_num_lions(int n) {
		the_info.num_lions = n;
	}
	void set_num_hyenas(char n) {
		the_info.num_hyenas = n;
	}
	void set_calling(bool b) {
		calling = b;
	}
//	void inc_used(ops i){
//		the_info.uses[i]++;
//	}
/*
	void record_last_fitness(){
		the_info.last_fitness = the_info.curr_fitness;
		the_info.curr_fitness = fitness;
	}
*/
	//     void set_nearest_edge(vect v){the_info.nearest_edge = v;}
	bool get_calling() {
		return calling;
	}
	vect get_last_move(){
		return the_info.last_move;
	}

	inline float getX(void) {
		return x;
	}
	inline float getY(void) {
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
		the_info.num_attacks++;
	}
	void zero_lion_attacks(void) {
		lion_attacks = 0;
	}
	void reset_attack_input(){
		the_info.num_attacks = 0;
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
	void set_position(float x_in, float y_in){
		x = x_in;
		y = y_in;
	}
//	int* get_uses(){
//		return (int*) &(the_info.uses);
//	}
	double* get_importance(){
		return (double*) &(the_info.importance);
	}
	int get_hits(){
		return the_info.hits;
	}

	void xOver(indiv*);

	node *tree;
	float x;
	float y;
private:
	int size;
	agent_info the_info;
	float fitness;
	float avg_dist_to_zebra;
	int lion_attacks;
	agent_type type;
	bool calling;
};

#endif
