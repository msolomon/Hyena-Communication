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
private:
	team *agents;
};

#endif
