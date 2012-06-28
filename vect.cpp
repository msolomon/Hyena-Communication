#include "vect.h"
#include "globals.h"

vect& vect::operator+=(const vect &v2){
	double x, y;
	x = sin(direction) * magnitude;
	y = cos(direction) * magnitude;

	x += sin(v2.direction) * v2.magnitude;
	y += cos(v2.direction) * v2.magnitude;

	magnitude = dist(x, y);
	direction = atan2(x, y);
	return *this;
}

void vect::random(void) {
	direction = Random::Global.FixedW() * PI;
	magnitude = Random::Global.FixedN() * X; // proportion of map
}
