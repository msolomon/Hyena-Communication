#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>

#include "vect.h"
#include "limits.h"
#include "float.h"

// include fast random libraries
#include <RandomLib/Random.hpp>
static RandomLib::Random r;        // create random number object

//// Common settings
const int ITERATIONS = 5000;
const int POP_SIZE = 80;
const char NUM_HYENAS = 20;
const char NUM_LIONS = 2;
const int TIME_STEPS = 100;
const int NUM_TESTS = 2; // times to repeat tests to prevent luck
const bool START_ONE_INSIDE = true; // at least one hyena inside calling radius
const bool START_OUTSIDE_ZEBRA = false;
const bool LIONS_RETURN = false; // lions return to kill if close and few hyenas
const bool FULL = false; // false = GROW, see S. Luke IEEE 10.1109/4235.873237
const int TREE_MAX_SIZE = 500; // if tree size > this, won't reproduce
// Only pick one method below
const bool TEAM_GENERATIONAL = false;
const bool OET_GENERATIONAL = true;
const bool ISLAND_GENERATIONAL = false;
const bool ISLAND_STEADY = false;
// GUI/Drawing settings
const bool GUI = false;
const bool DRAW = true; // if false, videos are unavailable
const int DRAW_EVERY = 10; // draw every X generations
const bool ANTIALIAS = true; // antialias GUI drawing
const bool HYENA_MARKERS = true; // draw short line to ID different hyenas

// Use %1 for trial number
const char* const VIDEO_TEMPLATE = "video_%1.txt";
const char* const DATA_TEMPLATE = "data_%1.txt";
const char* const GRAPHVIZ_TEMPLATE = "hyena_%1.gv";

//// Other settings
// Selection and reproduction
const int TOURNAMENT_SIZE = 5;
const int GROW_DEPTH = 4;
const int MUTATION_CHANCE = 10; // % chance of mutation
const int TRIALS = 1; // leaks memory; do via script
// Model
const int X = 32; // powers of 2 are best - int division elsewhere
const int Y = X;
const float ZEBRAX = X / 2.0;
const float ZEBRAY = Y / 2.0;
const float CALLING_RANGE = 8; // hyenas call when close to zebra
//const int HEAR_CALLING_RADIUS = (int) sqrt(INT_MAX);
const float LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5; // both ways
const int HYENA_HYENA_RADIUS = 10;
const int HYENA_LION_FEAR_RATIO = 3;
const int LION_SEES_ZEBRA = CALLING_RANGE;
const int LION_NEAR_ZEBRA = 1;
// Squared versions of constants (for performance)
//const int HEAR_CALLING_RADIUS_SQ = INT_MAX;
const float LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const float LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;
const float LION_HYENA_RADIUS_SQ = LION_HYENA_RADIUS * LION_HYENA_RADIUS;
const float HYENA_HYENA_RADIUS_SQ = HYENA_HYENA_RADIUS * HYENA_HYENA_RADIUS;
const float CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;
// reward getting close enough to actually eat
const bool EAT_BONUS_ACTIVE = false;
const float EAT_RADIUS = CALLING_RANGE / 8;
const float EAT_RADIUS_SQ = EAT_RADIUS * EAT_RADIUS;
const float EAT_BONUS = 1.0;
// General constants
const float PI = 3.141592654;


//// Types
enum ops {
	zebra,
	nearest_hyena,
	nearest_lion,
	nearest_calling,
	north,
	randm,
	last_move,
	constant,
	number_hyenas,
	mirror_nearest, // repeat the previous action of the nearest hyena
	delta_fitness,
	sum,
	invert,
	iflteMAG,
	iflteCLOCKWISE,
	ifVectorZero
};

const int NUM_TERMS = 11;
const int NUM_NON_TERMS = 5;

typedef struct {
	vect zebra;
	vect nearest_hyena;
	vect nearest_lion;
	vect last_move;
	vect mirrored;
	vect nearest_calling;
	char num_lions;
	char num_hyenas;
	float last_fitness;
	float curr_fitness;
	int uses[NUM_TERMS + NUM_NON_TERMS];
} agent_info;

//enum agent_type {
//	hyena, lion
//};
typedef bool agent_type;
const agent_type hyena = true;
const agent_type lion = false;

/*
// This probably won't save much (still uses a word)
typedef char ops;
const ops zebra = 0;
const ops nearest_hyena = 1;
const ops nearest_lion = 2;
const ops nearest_calling = 3;
const ops north = 4;
const ops randm = 5;
const ops last_move = 6;
const ops constant = 7;
const ops num_hyenas = 8;
const ops mirror_nearest = 9; // repeat the previous action of the nearest hyena
const ops delta_fitness = 10;
const ops sum = 11;
const ops invert = 12;
const ops iflteMAG = 13;
const ops iflteCLOCKWISE = 14;
const ops ifVectorZero = 15;
*/

// Global functions
inline float dist(float x, float y){  // 'distance' is a built-in function
	return sqrt((x * x) + (y * y));
}

inline float distance_sq(float x, float y){
	return x * x + y * y;
}

#endif
