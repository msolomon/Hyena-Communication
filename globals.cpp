#include "globals.h"

#ifdef _WIN32
void sincosf(float x, float *s, float *c){

    float s1 = sin(x);
    float c1 = cos(x);
    s = &s1;
    c = &c1;
}
#endif
