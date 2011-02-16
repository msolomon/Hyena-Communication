#include "vect.h"
// Must include here because vect is used in globals.h
#include "globals.h"

vect::vect() {
	magnitude = 0;
	direction = 0;
}

vect vect::operator=(const vect v2) {
	magnitude = v2.magnitude;
	direction = v2.direction;
	return *this;
}

vect vect::operator+(const vect v2) const {
	vect answer;
	float x, y;
	x = sin(direction) * magnitude;
	y = cos(direction) * magnitude;

	x += sin(v2.direction) * v2.magnitude;
	y += cos(v2.direction) * v2.magnitude;

	answer.magnitude = distance(x, y);
	answer.direction = atan2(x, y);
	return answer;
}

void vect::random(void) {
	direction = 2 * rand() % 31417 / 10000.0;
	magnitude = rand() % 100 / 100.0 * 5; // proportion of map
}
