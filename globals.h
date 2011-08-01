#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>
#include <cfloat>

// include fast random library (randomlib.sourceforge.net)
#define RANDOMLIB_DEFAULT_GENERATOR SRandomGenerator64
#include <RandomLib/Random.hpp>
using RandomLib::Random;

#include "types.h"

//// Common settings
const int GENERATIONS = 100;
const int POP_SIZE = 80;
const int NUM_HYENAS = 15;
const int NUM_LIONS = 2;
const int TIME_STEPS = 100;
const int NUM_TESTS = 5; // times to repeat tests to prevent luck
const bool FINAL_TEST_MEAN = true; // use mean fitness to pick final best team
const int FINAL_TESTS = 2000; // number of times to run best hyena of last trial
const bool LIONS_RETURN = false; // lions return to kill if close and few hyenas
const int TREE_MAX_SIZE = 5000; // size, not depth
const ops DISABLED_OPS[] = {};
const selection_method SELECTION_METHOD = median;
// 0 to disable, else start hyenas within X units: exactly 1 non-named inside
// the calling radius
const float RADIUS_START = 0;
// Only pick one method below
const bool OET_GENERATIONAL = true;
const bool TEAM_GENERATIONAL = false;
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
const char* const FINAL_TEMPLATE = "final_%1.txt";
const char* const FINAL_VIDEO_TEMPLATE = "finalvideo_%1.txt";

//// Other settings
// Selection and reproduction
const int TOURNAMENT_SIZE = 5;
const float MUTATION_CHANCE = 10; // % chance of mutation
const bool FULL = true; // false = GROW (for initial trees)
const int GROW_DEPTH = 4;
const int TRIALS = 1; // leaks memory; do via script
// Model
const int X = 32;
const int Y = X;
const float ZEBRAX = X / 2.0;
const float ZEBRAY = Y / 2.0;
const bool CALLING_ENABLED = true;
const float CALLING_RANGE = 8; // hyenas call when close to zebra
const bool START_ONE_INSIDE = true; // at least one hyena inside calling radius
const bool START_OUTSIDE_ZEBRA = false;
const double BASE_IMPORTANCE = 5000.0;
const float LION_ATTACK_RADIUS = 3;
const float LION_ATTACK_PENALTY = 3;
const float LION_LION_RADIUS = 5;
const float LION_HYENA_RADIUS = 5; // both ways
const float HYENA_HYENA_RADIUS = 10;
const float HYENA_LION_FEAR_RATIO = 3;
const float LION_SEES_ZEBRA = CALLING_RANGE;
const float LION_NEAR_ZEBRA = 1;
// Squared versions of constants (for performance)
const float LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const float LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;
const float LION_HYENA_RADIUS_SQ = LION_HYENA_RADIUS * LION_HYENA_RADIUS;
const float HYENA_HYENA_RADIUS_SQ = HYENA_HYENA_RADIUS * HYENA_HYENA_RADIUS;
const float CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;
// General constants
const float PI = 3.141592654;

//// Global functions
inline float dist(float x, float y){  // 'distance' is a built-in function
	return sqrt((x * x) + (y * y));
}

inline float distance_sq(float x, float y){
	return x * x + y * y;
}

inline bool is_disabled(ops op){
	for(unsigned int i = 0; i < (sizeof(DISABLED_OPS) / sizeof(ops)); i++)
		if(op == DISABLED_OPS[i]) return true;
	return false;
}

// Prototypes
float select_from_numtests(float fitnesses[NUM_TESTS]);

#endif
