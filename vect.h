#ifndef VECT_H
#define VECT_H
class vect{
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
