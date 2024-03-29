#ifndef INDIV_BASE_H
#define INDIV_BASE_H

#include "globals.h"
#include "node.h"
#include <cmath>
#include <QString>
#include <QStringList>

class indiv_base {
public:
    virtual ~indiv_base();
	double x;
	double y;

	void reset_inputs(){
		the_info.zebra.reset();
		the_info.nearest_hyena.reset();
		the_info.nearest_lion.reset();
		the_info.last_move.reset();
		the_info.mirrored.reset();
		the_info.nearest_calling.reset();
		the_info.named.reset();
		the_info.landmark.reset();
		the_info.num_lions = 0;
		the_info.num_hyenas = 0;
		the_info.hits = 0;
		the_info.last_pen = 0;
		the_info.randm_enabled = true;
		the_info.constant_enabled = true;
		the_info.north_enabled = true;
		the_info.moved_yet = false;
	}

	void set_type(agent_type t) {
		type = t;
	}

	void changeFit(double f, int test) {
		if(f > 0) reward += f;
		fitnesses[test] += f;
	}

	void set_north_enabled(bool set){
		the_info.north_enabled = set;
	}

	void set_randm_enabled(bool set){
		the_info.randm_enabled = set;
	}

	void set_constant_enabled(bool set){
		the_info.constant_enabled = set;
	}

	void set_landmark(vect v){
		the_info.landmark = v;
	}

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
	void set_named(vect v) {
		the_info.named = v;
	}
	void set_mirrored(vect v){
		the_info.mirrored = v;
	}
	void set_hyena_vect(int hyena_num, vect v){
		the_info.hyenas[hyena_num] = v;
	}
	void set_num_lions(int n) {
		the_info.num_lions = n;
	}
	void set_num_hyenas(int n) {
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

	void set_last_move(vect set){
		the_info.last_move = set;
	}

	inline double getX(void) {
		return x;
	}
	inline double getY(void) {
		return y;
	}
	double get_mean_fitness(void){
		double fit = 0;
		for(int i = 0; i < NUM_TESTS; i++){
			fit += fitnesses[i];
		}
		return fit;
	}
	double get_fitness(){
		return select_from_numtests(fitnesses);
	}

	double get_fitness(int test) {
		return fitnesses[test];
	}
	double get_reward(void) {
		return reward;
	}
	double get_avg_dist_to_zebra(void) {
		return avg_dist_to_zebra;
	}
	double get_lion_attacks(void) {
		return lion_attacks;
	}
	double get_penalty(void) {
		return attack_pen;
	}
	vect get_hyena_vect(int hyena_num){
		return the_info.hyenas[hyena_num];
	}
	void inc_dist_to_zebra(double d) {
		avg_dist_to_zebra += (d / (double)TIME_STEPS);
	}
	void set_avg_dist_to_zebra(double d) {
		avg_dist_to_zebra = d;
	}
	void inc_lion_attacks(double penalty) {
		lion_attacks++;
		the_info.last_pen = -penalty; // unary - to make positive
		attack_pen += penalty;
	}
	void zero_lion_attacks(void) {
		lion_attacks = 0;
	}
	void reset_pen_input(){
		the_info.last_pen = 0;
	}
	double get_moved(void){
		return the_info.moved_yet;
	}

	void set_position(double x_in, double y_in){
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

	agent_type get_type(void) {
		return type;
	}

    void set_info(agent_info other_info){
        the_info = other_info;
    }

    virtual QStringList serialize() = 0;
	virtual void deserialize(QStringList input) = 0;
    virtual vect eval_me() = 0;
    virtual QString graphviz() = 0;
    virtual void clear() = 0;
    virtual void generate() = 0;
    virtual void xOver(indiv_base*) = 0;
    virtual int get_size() = 0;
    virtual void mutate() = 0;

    void move();
    void lion_move();
    void reset_fitness();
    void reset();
protected:
    agent_info the_info;
	double fitnesses[NUM_TESTS];
	double reward;
	double avg_dist_to_zebra;
	double attack_pen;
	int lion_attacks;
	agent_type type;
	bool calling;
};

#endif // INDIV_BASE_H
