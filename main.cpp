/*#include "qth.h"
 #include <QtGui/QApplication>

 int main(int argc, char *argv[])
 {
 QApplication a(argc, argv);
 qth w;
 w.show();
 return a.exec();
 }
 */

#include <QApplication>

#include <ctime>
#include <iostream>
#include <fstream>

#include "window.h"
#include "globals.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Window window;

	int seed = int(time(NULL));
	//    seed = 1206369581;
	std::ofstream outseed;
	outseed.open("seed.txt");
	outseed << seed << std::endl;
	outseed.close();
	srand(seed);
	for (int t = 0; t < TRIALS; t++) {
		//p.generate();
		//p.evolve(t);
	}
	window.show();

	return app.exec();
}
