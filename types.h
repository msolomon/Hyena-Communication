#ifndef TYPES_H
#define TYPES_H

#include "vect.h"

//// Types
enum ops {
	// Terminals
	zebra, // to zebra, only if hyena within CALLING_RADIUS
	nearest_hyena, // nearest hyena, if within HYENA_HYENA_RADIUS
	nearest_lion, // nearest lion, if within LION_HYENA_RADIUS
	nearest_calling, // nearest calling hyena, unlimited range, else (0,0)
	north, // always (mag=1, dir=0)
	randm, // an ever-randomized vect, ( mag=[0,X], dir=[-PI,PI) )
	last_move, // a copy of the last move made or (0,0) at start
    constant, // a once-randomized vect, otherwise as randm *(VET only)*
	number_calling, // dir=0, mag=(number of calling hyenas), unlimited range
	mirror_nearest, // the previous action of the nearest hyena (if seen)
	last_pen, // mag=absolute value of penalty from last timestep, dir=0
	named, // only get vector if named hyena calls, unlimited range: flag-bearer
	landmark, // a vector to a landmark, unlimited range

	// Non-terminals
	sum, // sum of 2 inputs
    subtract, // subtract two inputs
	compare, // mag=(distance between two points) dir=(|angle between vectors|)
    invert, // invert 1 input (add PI to direction)
	iflteMAG, // if input 1 <= input 2, return input 3 else return input 4 (mag)
	iflteCLOCKWISE, // if input 1 <= input 2, return in. 3 else in. 4 (dir)
	ifVectorZero // if mag of input 1 == 0 return input 2 else input 3
	// More terminal "ops" are used during runtime, but not listed here
};

// names of ops used for serialization (manually keep in sync with above)
const char* const ops_names[] = {
	"zebra",
	"nearest_hyena",
	"nearest_lion",
	"nearest_calling",
	"north",
	"randm",
	"last_move",
	"constant",
	"number_calling",
	"mirror_nearest",
	"last_pen",
	"named",
	"landmark",
	"sum",
	"subtract",
	"compare",
	"invert",
	"iflteMAG",
	"iflteCLOCKWISE",
	"ifVectorZero"
};

const int NUM_TERMS = 13;
const int NUM_NON_TERMS = 7;
const int NUM_UNIQUE_OPS = NUM_TERMS + NUM_NON_TERMS;

// how to combine results from retesting, at both the individual and team levels
enum combine_method {
	mean, // O(n)
	median, // selection sort. good if n < ~20
	minimum, // O(n)
	maximum // O(n)
};

enum gene_type {
    vet,       // vector expression trees (no calling learning)
    hybrid,    // vet for movement, ann for learning calling behavior
    ann_fixed, // artificial neural network (no calling learning)
    ann_learn // artificial neural network with calling learning
};

enum selection {
    indiv_sel,  // 100% individual generational selection
    team_sel,   // 100% team generational selection
    oet_sel,    // 50% team selection, 50% ind selection
    alt_sel,    // alternate between team/ind selection each generation
    island_sel  // 100% steady-state island model
};

enum agent_type {
	hyena, lion
};

#endif // TYPES_H
