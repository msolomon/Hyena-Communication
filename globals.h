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
const int ITERATIONS = 15000;
const int POP_SIZE = 80;
const char NUM_HYENAS = 20;
const char NUM_LIONS = 2;
const int TIME_STEPS = 100;
const int NUM_TESTS = 3; // times to repeat tests to prevent luck
const bool START_ONE_INSIDE = true; // at least one hyena inside calling radius
const bool START_OUTSIDE_ZEBRA = false;
const bool LIONS_RETURN = false; // lions return to kill if close and few hyenas
const int TREE_MAX_SIZE = 500; // size, not depth
const ops DISABLED_OP = none_disabled; // use none_disabled to enable all
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
const int MUTATION_CHANCE = 10; // % chance of mutation
const bool FULL = true; // false = GROW, see S. Luke IEEE 10.1109/4235.873237
const int GROW_DEPTH = 4;
const int TRIALS = 1; // leaks memory; do via script
// Model
const int X = 32; // powers of 2 are best - int division elsewhere
const int Y = X;
const float ZEBRAX = X / 2.0;
const float ZEBRAY = Y / 2.0;
const float CALLING_RANGE = 8; // hyenas call when close to zebra
const float LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5; // both ways
const int HYENA_HYENA_RADIUS = 10;
const int HYENA_LION_FEAR_RATIO = 3;
const int LION_SEES_ZEBRA = CALLING_RANGE;
const int LION_NEAR_ZEBRA = 1;
// Squared versions of constants (for performance)
const float LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const float LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;
const float LION_HYENA_RADIUS_SQ = LION_HYENA_RADIUS * LION_HYENA_RADIUS;
const float HYENA_HYENA_RADIUS_SQ = HYENA_HYENA_RADIUS * HYENA_HYENA_RADIUS;
const float CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;
// reward getting close enough to actually eat
const bool EAT_BONUS_ACTIVE = false;
const float EAT_RADIUS = CALLING_RANGE / 8.0;
const float EAT_RADIUS_SQ = EAT_RADIUS * EAT_RADIUS;
const float EAT_BONUS = 1.0;
// General constants
const float PI = 3.141592654;

//// Global functions
inline float dist(float x, float y){  // 'distance' is a built-in function
	return sqrt((x * x) + (y * y));
}

inline float distance_sq(float x, float y){
	return x * x + y * y;
}

#endif
