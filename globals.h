#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>

#include"vect.h"

const float PI = 3.141592654;

const int X = 25;
const int Y = 25;
//const int HYENA_SEE_ZEBRA_RADIUS = X / 8;
const int HEAR_CALLING_RADIUS = X + Y;
const int LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5;
//const int LION_SEES_ZEBRA = 5;
//const int LION_NEAR_ZEBRA = 1;
const int HEAR_CALLING_RADIUS_SQ = HEAR_CALLING_RADIUS * HEAR_CALLING_RADIUS;
const int LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const int LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;

//const int INVESTIGATOR_RADIUS = 10;
//const int SCOUT_RADIUS = 20;

const int ZEBRAX = X / 2;
const int ZEBRAY = Y / 2;
const float CALLING_RANGE = X / 4;
const float CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;


const int POP_SIZE = 80;
const int NUM_HYENAS = 20;
const int NUM_LIONS = 2;
//const int NUM_AGENTS = NUM_HYENAS + NUM_LIONS;
const int TIME_STEPS = 50;
const int NUM_TESTS = 1;
const int TOURNAMENT_SIZE = 5;
const int ITERATIONS = 21;
//const int TEAM_SIZE = 3;
const int TRIALS = 1;
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

inline float distance(float x, float y){
    return sqrt(x * x + y * y);
}

inline float distance_sq(float x, float y){
	return x * x + y * y;
}

#endif
