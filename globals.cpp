#include <ctime>
void sleep(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}
