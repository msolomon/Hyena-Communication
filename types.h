#ifndef TYPES_H
#define TYPES_H

#include "vect.h"

//// Types
enum ops {
	zebra, // to zebra, only if hyena within CALLING_RADIUS
	nearest_hyena, // nearest hyena, if within HYENA_HYENA_RADIUS
	nearest_lion, // nearest lion, if within LION_HYENA_RADIUS
	nearest_calling, // nearest calling hyena, unlimited range, else (0,0)
	north, // always (mag=1, dir=0)
	randm, // an ever-randomized vect, ( mag=[0,X], dir=[-PI,PI) )
	last_move, // a copy of the last move made or (0,0) at start
	constant, // a once-randomized vect, otherwise as randm
	number_calling, // dir=0, mag=(number of calling hyenas), unlimited range
	mirror_nearest, // the previous action of the nearest hyena (if seen)
	last_pen, // absolute value of penalty from last timestep
	named, // only get vector if named hyena calls, unlimited range
	landmark, // a vector to a landmark, unlimited range
	sum, // sum of 2 inputs
    subtract, // subtract two inputs
	compare, // mag=(distance between two points) dir=(|angle between vectors|)
    invert, // invert 1 input (add PI to direction)
	iflteMAG, // if input 1 <= input 2, return input 3 else return input 4 (mag)
	iflteCLOCKWISE, // if input 1 <= input 2, return in. 3 else in. 4 (dir)
	ifVectorZero // if mag of input 1 == 0 return input 2 else input 3
};

const int NUM_TERMS = 13;
const int NUM_NON_TERMS = 7;
const int NUM_OPS = NUM_TERMS + NUM_NON_TERMS;

// how to combine results from retesting, at both the individual and team levels
enum selection_method{
	mean, // O(n)
	median, // selection sort. good if n < ~20
	minimum, // O(n)
	maximum // O(n)
};

typedef struct {
	vect zebra;
	vect nearest_hyena;
	vect nearest_lion;
	vect last_move;
	vect mirrored;
	vect nearest_calling;
	vect named;
	vect landmark;
	int num_lions;
	int num_hyenas;
    int hits;
	float last_pen;
//	int uses[NUM_OPS];
	// the rest can be turned off by zeroing out above vectors
	double importance[NUM_OPS];
	bool north_enabled;
	bool constant_enabled;
    bool randm_enabled;
} agent_info;

//enum agent_type {
//	hyena, lion
//};
typedef bool agent_type;
const agent_type hyena = true;
const agent_type lion = false;

#endif // TYPES_H
