#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QPoint>
#include <QPointer>

#include <cmath>
#include <string>

#include "team.h"
#include "drawhelper.h"
#include "globals.h"

class environment {
public:
	void update_vectors(void);
	void draw(DrawHelper*, int);
	void rand_move(void);
	void move(void);
	void evaluate();
	void set_up(team *);
	std::string fname;
	void generate_positions();
	void place_agents(int);
	float landmarkcoord[NUM_TESTS][2];
	float hyenacoord[NUM_TESTS][NUM_HYENAS][2];
	float lioncoord[NUM_TESTS][NUM_LIONS][2];
private:
	team *agents;
	float landmarkx;
	float landmarky;
};

#endif
