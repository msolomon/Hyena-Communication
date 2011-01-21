#include "cell.h"

//void cell::draw(HWND hwnd, int x, int y){     
////   glClearColor(1.0, 0.0, 0.0, 0.0);
////   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//   glOrtho(0,0, X*BOX,Y*BOX, -1.0, 1.0);
//   if(interest == 0)
//         glColor3f(0.0, 1.0, 0.0);
//   else if(interest == 1)
//         glColor3f(1.0, 0.0, 0.0);
//   else if(interest == 2)
//         glColor3f(0.0, 0.5, 0.0);
// 
//   glBegin(GL_POLYGON);
//      glVertex3f((x*BOX+BOX/3),y*BOX+BOX/3,0);
//      glVertex3f(x*BOX+BOX/3,y*BOX+2*BOX/3,0);
//      glVertex3f(x*BOX+2*BOX/3,y*BOX+2*BOX/3,0);
//      glVertex3f(x*BOX+BOX/3,y*BOX+2*BOX/3,0);
//   glEnd();
////   SwapBuffers (hDc);
//
//}

void cell::reset(void) {
	interest = 0;
	if (rand() % 100 < INTEREST_PERCENT)
		interest = 1;
}

cell::cell(void) {
	reset();
}
