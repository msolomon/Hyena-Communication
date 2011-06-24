#include <QApplication>

#include <iostream>
#include <fstream>

#include "qthyena.h"
#include "globals.h"

using namespace std;

int main(int argc, char *argv[]) {
	// Dump the seed to file
	ofstream outseed;
	if(argc > 1){
		char *name = (char*) malloc((20+strlen(argv[1]))*sizeof(char));
		sprintf(name, "seed_%s.txt", argv[1]);
		outseed.open(name);
		free(name);
	} else{
		outseed.open("seed.txt");
	}
	// Randomlib uses an unsigned long int vector of size 4 to seed. Print each.
	vector<Random::seed_type> seed = Random::SeedVector();
	for (vector<Random::seed_type>::iterator i = seed.begin(); i != seed.end(); i++)
		outseed << *i << "\n";
	outseed.close();
	Random::Global.Reseed(seed);
	seed.clear();

	// Kick off the application, in either GUI or console mode
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
