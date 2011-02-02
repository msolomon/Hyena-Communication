#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>

#include"vect.h"

const float PI = 3.141592654;

const int X = 25;
const int Y = 25;
//const int HYENA_SEE_ZEBRA_RADIUS = X / 8;
//const int HEAR_CALLING_RADIUS = X;
const int LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5;
//const int LION_SEES_ZEBRA = 5;
//const int LION_NEAR_ZEBRA = 1;

//const int INVESTIGATOR_RADIUS = 10;
//const int SCOUT_RADIUS = 20;

const int ZEBRAX = X / 2;
const int ZEBRAY = Y / 2;
// TODO: Figure out how many/where zebras there actually are

const int POP_SIZE = 80;
const int NUM_HYENAS = 20;
const int NUM_LIONS = 2;
//const int NUM_AGENTS = NUM_HYENAS + NUM_LIONS;
const int TIME_STEPS = 50;
const int NUM_TESTS = 1;
const int TOURNAMENT_SIZE = 5;
const int ITERATIONS = 15;
const int TEAM_SIZE = 3;
const int TRIALS = 2;
const int GROW_DEPTH = 4;
const int EVALUATE_EVERY = 3;
const bool DRAW = true;
const int DRAW_MS = 30;

//const int INTEREST_PERCENT = 0;

typedef struct {
	vect zebra;
	vect nearest_scout;
	vect nearest_invest;
	vect nearest_edge;
	vect last_move;
	vect nearest_calling;
	int num_investigators;
	int num_scouts;
} agent_info;

enum agent_type {
	scout, investigator
};

/* Thanks to N. Mundhenk of USC: <mundhenk@usc.edu>
   Source: http://ilab.usc.edu/wiki/index.php/Fast_Square_Root
*/
inline float fastSqrt_2(const float x){
    union{
        int i;
        float x;
    } u;

    u.x = x;
    u.i = (1<<29) + (u.i >> 1) - (1<<22);

  return u.x;
}

inline float sq_rt(float a){
	//return sqrt(a);
	return fastSqrt_2(a);
	return a;
}

inline float distance(float x, float y){
	return sq_rt(x * x + y * y);
//	return sq_rt(pow(x, 2) + pow(y, 2));
//	return fabs(x) + fabs(y);
}

#ifdef _WIN32
void sincosf(float x, float *s, float *c);
#endif

#endif
