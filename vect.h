#ifndef VECT_H
#define VECT_H

#include <cmath>
#include <cstdlib>

class vect {
public:
	vect();
	void random(void);
	void reset();
	vect& operator=(const vect&);
	vect& operator+=(const vect&);
	const vect operator+(const vect&) const;
	void invert();
    double direction;
    double magnitude;
};

#endif
