#ifndef GLOBALS_H
#define GLOBALS_H

//#include <windows.h>
//#include <gl/gl.h>
//#include <vector>
#include <cmath>
//#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

const float PI = 3.141592654;

//void sleep(unsigned int);

//using namespace std;
/*HDC hDc;
 HGLRC hrc;
 */
const int BOX = 20;
const int SCOUT_SIZE = 10;
const int X = 25;
const int Y = 25;
const int HYENA_SEE_ZEBRA_RADIUS = X / 8;
const int HEAR_CALLING_RADIUS = X;
const int LION_ATTACK_RADIUS = 3;
const int LION_LION_RADIUS = 5;
const int LION_HYENA_RADIUS = 5;
const int LION_SEES_ZEBRA = 5;
const int LION_NEAR_ZEBRA = 1;

//const int INVESTIGATOR_RADIUS = 10;
//const int SCOUT_RADIUS = 20;

const int ZEBRAX = X / 2;
const int ZEBRAY = Y / 2;
// TODO: Figure out how many/where zebras there actually are

const int POP_SIZE = 80;
const int NUM_HYENAS = 20;
const int NUM_LIONS = 2;
const int NUM_AGENTS = NUM_HYENAS + NUM_LIONS;
const int TIME_STEPS = 5; //50;
const int NUM_TESTS = 5;
const int TOURNAMENT_SIZE = 5;
const int ITERATIONS = 51;
const int TEAM_SIZE = 3;
const int TRIALS = 20;
const int GROW_DEPTH = 4;
const float xscale = X * BOX / 2;
const float xshift = X * BOX / (2 * xscale);
const float yscale = Y * BOX / 2;
const float yshift = Y * BOX / (2 * yscale);
const int INTEREST_PERCENT = 0;

const int FIELDX = 400;
const int FIELDY = 400;

#include"vect.h"
typedef struct {
	vect zebra;
	vect nearest_scout;
	vect nearest_invest;
	vect nearest_edge;
	vect last_move;
	vect nearest_calling;
	int num_investigators;
	int num_scouts;
} agent_info;

enum agent_type {
	scout, investigator
};

/*
 #include"node.h"
 #include"indiv.h"
 #include"team.h"
 #include"environment.h"
 #include"pop.h"

 environment ENV;
 pop p;
 */

#endif
