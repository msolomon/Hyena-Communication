#ifndef VECT_H
#define VECT_H

#include <cmath>
#include <cstdlib>

#ifndef PI_DEF
#define PI_DEF
const double PI = 3.1415926535897932384626433832795028842;
#endif

class vect {
public:
    inline vect(){
        reset();
    }
    inline void reset(){
        direction = 0;
        magnitude = 0;
    }
    inline vect& operator=(const vect& v2){
        magnitude = v2.magnitude;
        direction = v2.direction;
        return *this;
    }
    inline const vect operator+(const vect& v2) const{
        vect answer = *this;
        answer += v2;
        return answer;
    }
    inline void invert(){
        if(direction > 0)
            direction -= PI;
        else
            direction += PI;
    }
    void random(void);
    vect& operator+=(const vect& v2);
    double direction;
    double magnitude;
};

#endif
