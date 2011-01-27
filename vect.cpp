#include <cmath>
#include <cstdlib>

#include "vect.h"
#include "globals.h"

vect::vect() {
	magnitude = 0;
	direction = 0;
}

vect vect::operator=(const vect v2) {
	magnitude = v2.magnitude;
	direction = v2.direction;
	vect answer;
	answer.magnitude = magnitude;
	answer.direction = direction;
	return answer;
}

vect vect::operator+(const vect v2) const {
	vect answer;
	float x1, x2, y1, y2;
	x1 = magnitude * sin(direction);
	y1 = magnitude * cos(direction);
	x2 = v2.magnitude * sin(v2.direction);
	y2 = v2.magnitude * cos(v2.direction);
	answer.magnitude = distance(x1 + x2, y1 + y2);
	answer.direction = atan2(x1 + x2, y1 + y2);
	return answer;
}

void vect::random(void) {
	direction = 2 * rand() % 31417 / 10000.0;
	magnitude = rand() % 100 / 100.0 * 5; // proportion of map
}
