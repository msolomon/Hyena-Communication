#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QPoint>
#include <QPointer>

#include <cmath>

#include "glwidget.h"
#include "team.h"
#include "helper.h"

class environment {
public:
	environment(void);
	void update_vectors(void);
	void draw(Helper*);
	void rand_move(void);
	void move(void);
	void evaluate();
	void set_up(team *);
private:
	team *agents;
};

#endif
