#ifndef VECT_H
#define VECT_H

#include <cmath>
#include <cstdlib>

class vect {
public:
	vect();
	void random(void);
	float direction;
	float magnitude;
	vect operator=(const vect);
	vect operator+(const vect) const;
private:
};

#endif
