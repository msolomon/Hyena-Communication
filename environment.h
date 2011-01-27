#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QPoint>
#include <QPointer>

#include <cmath>

#include "team.h"
#include "helper.h"
#include "globals.h"

class environment {
public:
	environment(void);
	void update_vectors(void);
	void draw(Helper*, int);
	void rand_move(void);
	void move(void);
	void evaluate();
	void set_up(team *);
private:
	team *agents;
};

#endif
