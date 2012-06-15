#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef QT_NO_DEBUG // qmake building in release mode
#define NDEBUG // disable assert statements
#endif

#include <cmath>
#include <cfloat>
#include <climits>
#include <cassert>

// include fast random library (randomlib.sourceforge.net)
#define RANDOMLIB_DEFAULT_GENERATOR SRandomGenerator64
#include <RandomLib/Random.hpp>
using RandomLib::Random;

// include AMD Core Math Library (developer.amd.com/libraries/acml)
#include <acml/acml.h> // only used in indiv_nn class

#include "types.h"
class indiv_nn;

//// Settings
const int GENERATIONS = 1500;
const int POP_SIZE = 100;
const int START_LIONS = 1; // number of lions to start, then move up ~linearly
const int NUM_LIONS = 2; // maximum and final number of lions >= START_LIONS
const int NUM_HYENAS = 14;
const int TIME_STEPS = 100;
const int NUM_TESTS = 5; // times to repeat tests to prevent luck
const int NUM_HYENA_INPUTS = 0; // 0 to disable, otherwise first N
const bool VEC_CALLING_ONLY = true; // vectors to all calling, or all period?
const int FINAL_TESTS = 2000; // number of times to run best hyena of last trial
const int KNOCKOUT_TESTS = 2000; // as above, but with given inputs disabled
const bool LIONS_RETURN = false; // lions return to kill if close and few hyenas
const double PARSIMONY_COEFF = 0.001;
const ops DISABLED_OPS[] = {landmark};
const ops KNOCKOUT_OPS[] = {};
const selection_method SELECTION_METHOD = mean; // mean, median, minimum, maximum
const bool FINAL_TEST_MEAN = false; // force mean fitness to pick final best team
// 0 to disable, else start hyenas within X units: exactly 1 non-named inside
// the calling radius
const double RADIUS_START = 16;

// Selection, crossover, mutation, initial trees
const int TOURNAMENT_SIZE = 3;
const double MUTATION_CHANCE = 5.0; // flat % chance of mutation
   // NUM_OVER... overrides above if nonzero. gives X/size chance mut. per node
const double NUM_OVER_SIZE_MUTATION = 0; // mean number of mutations/iteration
// Vector expression trees only
const bool SPECIALIZED_CONST_MUT = true;
const double CONST_MUT_MAG_SIGMA = 1.0;
const double CONST_MUT_DIR_SIGMA = 1.0;
// ANNs only
const double MUTATION_SIGMA = 0.1;

// Vector expression trees or artificial neural networks
const bool USE_ANN = true;  // true: ANN, false: vector expression trees
// ANN only
const bool LEARN_CALLING = true;
const int NETWORK_NUM_INPUT = 2*NUM_HYENAS + 24; // # of input nodes
const int NETWORK_NUM_OUTPUT = 3; // # of output nodes: 2+, 3+ if LEARN_CALLING
const int NETWORK[] = {NETWORK_NUM_INPUT, // input layer
                       // # of nodes in each hidden layer, e.g. 3, 2, 2
                       NETWORK_NUM_INPUT / 2,
                       NETWORK_NUM_OUTPUT}; // output layer
const int NETWORK_LAYERS = sizeof(NETWORK)/sizeof(int);
// Vector expression trees only
const bool USE_90_10_XOVER = true;
const bool ALLOW_INTERNAL_MUTATION = true;
const bool FULL = true; // false = GROW (for initial trees)
const int GROW_DEPTH = 4;
const int TREE_MAX_SIZE = INT_MAX; // size, not depth: INT_MAX for unlimited

// Only pick one method below
const bool OET_GENERATIONAL = false; // 50% team, 50% island (generational)
const bool TEAM_GENERATIONAL = false; // 100% team generational
const bool INDIV_GENERATIONAL = false; // 100% island generational
const bool ISLAND_STEADY = false;
const bool ALTERNATE_TEAM_INDIV = true; // alternate by generation

// Model
const int TRIALS = 1; // leaks memory; do via script
const int X = 32;
const int Y = X;
const double ZEBRAX = X / 2.0;
const double ZEBRAY = Y / 2.0;
const bool CALLING_ENABLED = true;
const double CALLING_RANGE = 8; // hyenas call when close to zebra
const bool START_ONE_INSIDE = true; // at least one hyena inside calling radius
const bool START_OUTSIDE_ZEBRA = false; // doesn't apply to radius placement
const double BASE_IMPORTANCE = 5000.0; // scales measure of ops usefulness
const double LION_ATTACK_RADIUS = 3;
const double LION_ATTACK_PENALTY = 3;
const double LION_LION_RADIUS = 5;
const double LION_HYENA_RADIUS = 5; // both ways
const double HYENA_HYENA_RADIUS = 10;
const double HYENA_LION_FEAR_RATIO = 3; // greater than
const double LION_SEES_ZEBRA = CALLING_RANGE;
const double LION_NEAR_ZEBRA = 1;
const int NUM_OPS = NUM_UNIQUE_OPS + NUM_HYENA_INPUTS;
const double MAX_HYENA_MOVE = 1.0;
const double LION_MOVE = 1.0; // distance
// Squared versions of constants (for performance)
const double LION_ATTACK_RADIUS_SQ = LION_ATTACK_RADIUS * LION_ATTACK_RADIUS;
const double LION_LION_RADIUS_SQ = LION_LION_RADIUS * LION_LION_RADIUS;
const double LION_HYENA_RADIUS_SQ = LION_HYENA_RADIUS * LION_HYENA_RADIUS;
const double HYENA_HYENA_RADIUS_SQ = HYENA_HYENA_RADIUS * HYENA_HYENA_RADIUS;
const double CALLING_RANGE_SQ = CALLING_RANGE * CALLING_RANGE;
// General constants
const double PI = 3.1415926535897932384626433832795028842;

//// GUI/Drawing settings
// Set GUI to true to enable visualizer; set to false for running simulations
const bool GUI = false;
const bool DRAW = true; // if false, videos are unavailable
const bool COLOR_HYENAS = true; // if false, all hyenas are brown
const bool MARK_CALLING = true; // mark calling hyenas
const int DRAW_EVERY = 10; // draw every X generations
const bool ANTIALIAS = true; // antialias GUI drawing
const bool HYENA_MARKERS = false; // draw short line to ID different hyenas
const bool SMEAR_DRAW = true; // don't erase background between timesteps
const int SMEAR_LAST = 20; // erase timesteps older than this; 0 for never
const bool FADE_DRAW = false; // hyenas less opaque toward end (more overlap)
const bool FADE_OUT = true; // older positions fade with time
const double ANIMAL_MAX_OPACITY = 0.8;
const double ANIMAL_MIN_OPACITY = 0.2;

//// Output file paths
// Use %1 for trial number
const char* const VIDEO_TEMPLATE = "video_%1.txt"; // video output
const char* const DATA_TEMPLATE = "data_%1.txt"; // data output
const char* const GRAPHVIZ_TEMPLATE = "hyena_%1.gv"; // graphviz output
const char* const FINAL_TEMPLATE = "final_%1.txt"; // last gen. data output
const char* const FINAL_VIDEO_TEMPLATE = "finalvideo_%1.txt"; // l.g. video out
const char* const KNOCKOUT_TEMPLATE = "knockout_%1.txt"; // knockout data out
const char* const KNOCKOUT_VIDEO_TEMPLATE = "knockoutvideo_%1.txt"; // k.o. video out
const char* const BEST_TEAM_TEMPLATE = "bestteam_%1.txt"; // best team output
// set RETEST_GIVEN path for input team (dumped by BEST_TEAM_TEMPLATE)
const char* const RETEST_GIVEN = NULL; // NULL to disable, else filename
// seed output is "seed_%s.txt" where %s is argv[1]

//// End of settings

//// Global functions
inline double dist(double x, double y){  // 'distance' is a built-in function
	return sqrt((x * x) + (y * y));
}

inline double distance_sq(double x, double y){
	return x * x + y * y;
}

inline bool is_disabled(ops op){
	for(unsigned int i = 0; i < (sizeof(DISABLED_OPS) / sizeof(ops)); i++)
		if(op == DISABLED_OPS[i]) return true;
	return false;
}

inline ops get_rand_terminal(ops except=(ops)255){
	ops op;
	do op = (ops) Random::Global.Integer(NUM_TERMS + NUM_HYENA_INPUTS);
	while(is_disabled(op) || op == except);
	if(op >= NUM_TERMS)
		op = (ops) (op + NUM_NON_TERMS); // hyena inputs come after both
	return op;
}

inline ops get_rand_nonterminal(ops except=(ops)255){
	ops op;
	do op = (ops) (NUM_TERMS + Random::Global.Integer(NUM_NON_TERMS));
	while(is_disabled(op) || op == except);
	return op;
}

inline ops get_rand_op(){
	ops op;
	do op = (ops) (Random::Global.Integer(NUM_OPS));
	while(is_disabled(op));
	return op;
}

// Prototypes
double select_from_numtests(double fitnesses[NUM_TESTS]);
int poisson_sample(double lambda);
double normal_sample(double mu, double sigma);

#endif
