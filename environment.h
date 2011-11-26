#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QPoint>
#include <QSet>

#include <cmath>
#include <string>
#include <vector>

#include "team.h"
#include "drawhelper.h"
#include "globals.h"

class environment {
public:
	environment();
	void update_vectors(void);
	void draw(DrawHelper*, int, int);
	void rand_move(void);
	void move(void);
	void evaluate(int);
	void set_up(team *);
	char *fname;
	void generate_positions();
	void place_agents(int);
    void knockout_genes(const ops disabled[], int disabled_len);
	void update_leadership();
	float landmarkcoord[NUM_TESTS][2];
	float hyenacoord[NUM_TESTS][NUM_HYENAS][2];
	float lioncoord[NUM_TESTS][NUM_LIONS][2];
	int leadership[NUM_HYENAS];
private:
	team *agents;
	float landmarkx;
	float landmarky;
	QSet<int> unmoved;
	QSet<int> uncalled;
	QSet<int> just_moved;
	QSet<int> just_called;
};

#endif
