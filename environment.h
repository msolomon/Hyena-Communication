#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QPoint>
#include <QPointer>

#include <cmath>

#include "glwidget.h"
#include "team.h"


class environment{
public:
	environment(void);
	void update_vectors(void);
	void draw(QPointer<GLWidget>);
	void rand_move(void);
	void move(void);
	void evaluate();
	void set_up(team *);
private:
	team *agents;
};


#endif
