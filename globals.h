#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>
#include <cfloat>
#include <climits>

// include fast random library (randomlib.sourceforge.net)
#define RANDOMLIB_DEFAULT_GENERATOR SRandomGenerator64
#include <RandomLib/Random.hpp>
using RandomLib::Random;

#include "types.h"

//// Common settings
const int GENERATIONS = 1500;
const int POP_SIZE = 80;
const int NUM_HYENAS = 15;
const int NUM_HYENA_INPUTS = NUM_HYENAS; // 0 to disable, otherwise first N
const bool VEC_CALLING_ONLY = false; // vectors to all calling, or all period?
const int NUM_LIONS = 2;
const int TIME_STEPS = 100;
const int NUM_TESTS = 5; // times to repeat tests to prevent luck
const bool FINAL_TEST_MEAN = false; // force mean fitness to pick final best team
const int FINAL_TESTS = 2000; // number of times to run best hyena of last trial
const int KNOCKOUT_TESTS = 2000; // as above, but with a given inputs disabled
const bool LIONS_RETURN = false; // lions return to kill if close and few hyenas
const float PARSIMONY_COEFF = 0.001;
const ops DISABLED_OPS[] = {};
const ops KNOCKOUT_OPS[] = {};
const selection_method SELECTION_METHOD = mean;
const char* const RETEST_GIVEN = NULL; // NULL to disable, else filename
// 0 to disable, else start hyenas within X units: exactly 1 non-named inside
// the calling radius
const float RADIUS_START = 0;
// Only pick one method below
const bool OET_GENERATIONAL = true; // 50% team gen., 50% island gen.
const bool TEAM_GENERATIONAL = false; // 100% team generational
const bool INDIV_GENERATIONAL = false; // 100% island generational
const bool ISLAND_STEADY = false;
// GUI/Drawing settings
const bool GUI = false;
const bool DRAW = true; // if false, videos are unavailable
const int DRAW_EVERY = 10; // draw every X generations
const bool ANTIALIAS = true; // antialias GUI drawing
const bool HYENA_MARKERS = false; // draw short line to ID different hyenas
const bool SMEAR_DRAW = true; // don't erase background between timesteps
const int SMEAR_LAST = 10; // erase timesteps older than this; 0 for never
const bool FADE_DRAW = true; // hyenas less opaque toward end (more overlap)
const bool FADE_OUT = false; // older positions fade with time
const float ANIMAL_MAX_OPACITY = 0.6;
const float ANIMAL_MIN_OPACITY = 0.1;

// Use %1 for trial number
const char* const VIDEO_TEMPLATE = "video_%1.txt";
const char* const DATA_TEMPLATE = "data_%1.txt";
const char* const GRAPHVIZ_TEMPLATE = "hyena_%1.gv";
const char* const FINAL_TEMPLATE = "final_%1.txt";
const char* const FINAL_VIDEO_TEMPLATE = "finalvideo_%1.txt";
const char* const KNOCKOUT_TEMPLATE = "knockout_%1.txt";
const char* const KNOCKOUT_VIDEO_TEMPLATE = "knockoutvideo_%1.txt";
const char* const BEST_TEAM_TEMPLATE = "bestteam_%1.txt";

//// Other settings
// Selection and reproduction
const int TOURNAMENT_SIZE = 5;
const float MUTATION_CHANCE = 10; // % chance of mutation
const bool FULL = true; // false = GROW (for initial trees)
const int GROW_DEPTH = 4;
const int TRIALS = 1; // leaks memory; do via script
const int TREE_MAX_SIZE = INT_MAX; // size, not depth
// Model
const int X = 32;
const int Y = X;
const float ZEBRAX = X / 2.0;
const float ZEBRAY = Y / 2.0;
const bool CALLING_ENABLED = true;
const float CALLING_RANGE = 8; // hyenas call when close to zebra
const bool START_ONE_INSIDE = true; // at least one hyena inside calling radius
const bool START_OUTSIDE_ZEBRA = false; // doesn't apply to radius placement
const double BASE_IMPORTANCE = 5000.0;
const float LION_ATTACK_RADIUS = 3;
const float LION_ATTACK_PENALTY = 3;
const float LION_LION_RADIUS = 5;
const float LION_HYENA_RADIUS = 5; // both ways
const float HYENA_HYENA_RADIUS = 10;
const float HYENA_LION_FEAR_RATIO = 3; // greater than
const float LION_SEES_ZEBRA = CALLING_RANGE;
const float LION_NEAR_ZEBRA = 1;
const int NUM_OPS = NUM_UNIQUE_OPS + NUM_HYENA_INPUTS;
const float MAX_HYENA_MOVE = 1.0;
const float MAX_LION_MOVE = 1.0;
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

inline ops get_rand_terminal(){
	ops op;
	do op = (ops) Random::Global.Integer(NUM_TERMS + NUM_HYENA_INPUTS);
	while(is_disabled(op));
	if(op >= NUM_TERMS)
		op = (ops) (op + NUM_NON_TERMS); // hyena inputs come after both
	return op;
}

inline ops get_rand_nonterminal(){
	ops op;
	do op = (ops) (NUM_TERMS + Random::Global.Integer(NUM_NON_TERMS));
	while(is_disabled(op));
	return op;
}

inline ops get_rand_op(){
	ops op;
	do op = (ops) (Random::Global.Integer(NUM_OPS));
	while(is_disabled(op));
	return op;
}

// Prototypes
float select_from_numtests(float fitnesses[NUM_TESTS]);

#endif
