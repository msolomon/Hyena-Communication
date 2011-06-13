#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>

#include "vect.h"
#include "limits.h"

//// Common settings
const int ITERATIONS = 2000;
const int POP_SIZE = 80;
const char NUM_HYENAS = 20;
const char NUM_LIONS = 2;
const int TIME_STEPS = 100;
const int NUM_TESTS = 1; // times to repeat tests to prevent luck
// Only pick one method below
const bool TEAM_GENERATIONAL = false;
const bool OET_GENERATIONAL = true;
const bool ISLAND_GENERATIONAL = false;
const bool ISLAND_STEADY = false;
// GUI/Drawing settings
const bool GUI = true;
const bool DRAW = true; // if false, videos are unavailable
const int DRAW_EVERY = 10; // draw every X generations
const bool ANTIALIAS = true; // antialias GUI drawing
const bool HYENA_MARKERS = true; // short line to ID different hyenas

// Use %1 for trial number
const char* const VIDEO_TEMPLATE = "video_%1.txt";
const char* const DATA_TEMPLATE = "data_%1.txt";

//// Constants
const int TOURNAMENT_SIZE = 5;
const int GROW_DEPTH = 4;
const int EVALUATE_EVERY = 1;
const int TRIALS = 1; // leaks memory; do via script
const float PI = 3.141592654;
const int X = 32;
const int Y = 32;
const float ZEBRAX = X / 2;
const float ZEBRAY = Y / 2;
const int HEAR_CALLING_RADIUS = (int) sqrt(INT_MAX);
const float LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5; // both ways
const int HYENA_HYENA_RADIUS = 10;
const int HYENA_LION_FEAR_RATIO = 3;
// Squared versions of constants (for performance)
const int HEAR_CALLING_RADIUS_SQ = INT_MAX;
const float LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const int LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;
const int LION_HYENA_RADIUS_SQ = LION_HYENA_RADIUS * LION_HYENA_RADIUS;
const int HYENA_HYENA_RADIUS_SQ = HYENA_HYENA_RADIUS * HYENA_HYENA_RADIUS;
// hyenas call when close to zebra
const float CALLING_RANGE = 8;
const float CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;
// reward getting close enough to actually eat
const bool EAT_BONUS_ACTIVE = false;
const float EAT_RADIUS = CALLING_RANGE / 8;
const float EAT_RADIUS_SQ = EAT_RADIUS * EAT_RADIUS;
const float EAT_BONUS = 1.0;


// Types
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

//enum agent_type {
//	hyena, lion
//};
typedef bool agent_type;
const agent_type hyena = true;
const agent_type lion = false;

// Global functions
inline float dist(float x, float y){  // 'distance' is a built-in function
	return sqrt((x * x) + (y * y));
}

inline float distance_sq(float x, float y){
	return x * x + y * y;
}

#endif
