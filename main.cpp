#include <QApplication>

#include <ctime>
#include <iostream>
#include <fstream>
#include <process.h>

#include "qthyena.h"
#include "globals.h"

using namespace std;

int main(int argc, char *argv[]) {
	int seed = int(time(NULL)) * _getpid() + clock();
	//    seed = 1206369581;
	ofstream outseed;
	if(argc > 1){
		char *name = (char*) malloc(128 * sizeof(char));
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
