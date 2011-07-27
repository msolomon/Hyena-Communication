#include "vect.h"
#include "globals.h"

vect::vect() {
	magnitude = 0;
	direction = 0;
}

vect& vect::operator=(const vect &v2) {
	magnitude = v2.magnitude;
	direction = v2.direction;
	return *this;
}

vect& vect::operator+=(const vect &v2){
	float x, y;
	x = sin(direction) * magnitude;
	y = cos(direction) * magnitude;

	x += sin(v2.direction) * v2.magnitude;
	y += cos(v2.direction) * v2.magnitude;

	magnitude = dist(x, y);
	direction = atan2(x, y);
	return *this;
}

const vect vect::operator+(const vect& v2) const {
	vect answer = *this;
	answer += v2;
	return answer;
}

void vect::random(void) {
	direction = (Random::Global() / ((Random::max) / (2.0 * PI))) - PI;
	magnitude = Random::Global() / (Random::max / (float) X); // proportion of map
}

void vect::reset(){
	direction = 0;
	magnitude = 0;
}
