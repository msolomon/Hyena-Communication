#include <QApplication>

#include <ctime>
#include <iostream>
#include <fstream>

#include "qthyena.h"
#include "globals.h"

// includes and definitions needed to get process id
#ifdef _WIN32
#include <process.h>
#define getpid _getpid
#else
#include <sys/types.h>
#endif

using namespace std;
unsigned long mix(unsigned long, unsigned long, unsigned long);

int main(int argc, char *argv[]) {
	unsigned long seed = mix(time(NULL), getpid(), clock());
	//    seed = 1206369581;
	ofstream outseed;
	if(argc > 1){
		char *name = (char*) malloc((20+strlen(argv[1]))*sizeof(char));
		sprintf(name, "seed_%s.txt", argv[1]);
		outseed.open(name);
		free(name);
	} else{
		outseed.open("seed.txt");
	}
	outseed << seed << endl;
	outseed.close();
	srand(seed);

	if(GUI){
		QApplication app(argc, argv);
		qthyena ui;
		ui.show();
		return app.exec();
	} else{
		pop p;
		DrawHelper h;
		p.helper = &h;
		if(argc > 1)
			p.evolve_repeat(atoi(argv[1]));
		else
			p.evolve_repeat();
		return 0;
	}
}

// Mixing to help the random number be safe for multiple launches
// per second, via
// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
	a=a-b;  a=a-c;  a=a^(c >> 13);
	b=b-c;  b=b-a;  b=b^(a << 8);
	c=c-a;  c=c-b;  c=c^(b >> 13);
	a=a-b;  a=a-c;  a=a^(c >> 12);
	b=b-c;  b=b-a;  b=b^(a << 16);
	c=c-a;  c=c-b;  c=c^(b >> 5);
	a=a-b;  a=a-c;  a=a^(c >> 3);
	b=b-c;  b=b-a;  b=b^(a << 10);
	c=c-a;  c=c-b;  c=c^(b >> 15);
	return c;
}
