#include <cmath>
#include <cstdlib>

#include "vect.h"
#include "globals.h"

vect::vect() {
	magnitude = 0;
	direction = 0;
}

vect vect::operator=(const vect v2) {
	vect answer;
	answer.magnitude = v2.magnitude;
	answer.direction = v2.direction;
	return answer;
}

vect vect::operator+(const vect v2) const {
	vect answer;
	float x1, x2, y1, y2;
	sincosf(direction, &x1, &y1);
	x1 *= magnitude;
	y1 *= magnitude;
	sincosf(v2.direction, &x2, &y2);
	x2 *= v2.magnitude;
	y2 *= v2.magnitude;
	answer.magnitude = distance(x1 + x2, y1 + y2);
	answer.direction = atan2(x1 + x2, y1 + y2);
	return answer;
}

void vect::random(void) {
	direction = 2 * rand() % 31417 / 10000.0;
	magnitude = rand() % 100 / 100.0 * 5; // proportion of map
}
