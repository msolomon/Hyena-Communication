#include <QApplication>

#include <ctime>
#include <iostream>
#include <fstream>

#include "window.h"
#include "qthyena.h"
#include "globals.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	qthyena ui;

	int seed = int(time(NULL));
	//    seed = 1206369581;
	std::ofstream outseed;
	outseed.open("seed.txt");
	outseed << seed << std::endl;
	outseed.close();
	srand(seed);

	ui.show();

	return app.exec();
}
