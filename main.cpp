#include <QApplication>

#include <ctime>
#include <iostream>
#include <fstream>

#include "qthyena.h"
#include "globals.h"

using namespace std;

int main(int argc, char *argv[]) {
	int seed = int(time(NULL));
	//    seed = 1206369581;
	ofstream outseed;
	outseed.open("seed.txt");
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
		p.generate(&h);
		p.evolve_repeat();
		return 0;
	}
}
