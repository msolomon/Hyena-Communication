#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>

#include"vect.h"

const float PI = 3.141592654;

const int X = 25;
const int Y = 25;
//const int HYENA_SEE_ZEBRA_RADIUS = X / 8;
const int HEAR_CALLING_RADIUS = X * Y;
const int LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5;
//const int LION_SEES_ZEBRA = 5;
//const int LION_NEAR_ZEBRA = 1;
const int HEAR_CALLING_RADIUS_SQ = HEAR_CALLING_RADIUS * HEAR_CALLING_RADIUS;
const int LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const int LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;
const int LION_HYENA_RADIUS_SQ = LION_HYENA_RADIUS * LION_HYENA_RADIUS;


const float ZEBRAX = X / 2;
const float ZEBRAY = Y / 2;

// hyenas call when close to zebra
const float CALLING_RANGE = X / 4;
const float CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;


// reward getting close enough to actually eat
const float EAT_RADIUS = X / 16;
const float EAT_RADIUS_SQ = EAT_RADIUS * EAT_RADIUS;
const float EAT_BONUS = 1.0;
const bool EAT_BONUS_ACTIVE = false;

const int POP_SIZE = 80;
const char NUM_HYENAS = 20;
const char NUM_LIONS = 2;
//const int NUM_AGENTS = NUM_HYENAS + NUM_LIONS;
const int TIME_STEPS = 50;
const int NUM_TESTS = 1;
const int TOURNAMENT_SIZE = 5;
const int ITERATIONS = 1500;
//const int TEAM_SIZE = 3;
const int TRIALS = 1;
const int GROW_DEPTH = 4;
const int EVALUATE_EVERY = 30;
const bool DRAW = true;
const int DRAW_MS = 20;

//const int INTEREST_PERCENT = 0;

typedef struct {
	vect zebra;
	vect nearest_hyena;
	vect nearest_lion;
	vect last_move;
	vect mirrored;
	vect nearest_calling;
	char num_lions;
	char num_hyenas;
} agent_info;

enum agent_type {
	hyena, lion
};

inline float distance(float x, float y){
    return sqrt(x * x + y * y);
}

inline float distance_sq(float x, float y){
	return x * x + y * y;
}

#endif
