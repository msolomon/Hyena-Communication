#ifndef AGENT_INFO_H
#define AGENT_INFO_H

#include "globals.h"

typedef struct {
	vect zebra;
	vect nearest_hyena;
	vect nearest_lion;
	vect last_move;
	vect mirrored;
	vect nearest_calling;
	vect named;
	vect landmark;
	vect hyenas[NUM_HYENAS];
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
	bool moved_yet;
} agent_info;

#endif // AGENT_INFO_H
