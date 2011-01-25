#include <QtGui>
#include "helper.h"
#include <QList>
#include <QPoint>

Helper::Helper() {
	backgroundBrush = QBrush(QColor(20, 155, 20));
	QColor hyenaColor = QColor(139, 69, 19);
	QColor lionColor = QColor(220, 220, 20);
	QColor zebraColor = QColor(220, 20, 20);

	hyenaPen = QPen(QBrush(hyenaColor), .5, Qt::SolidLine, Qt::RoundCap);
	lionPen = QPen(QBrush(lionColor), 1, Qt::SolidLine, Qt::RoundCap);
	zebraPen = QPen(QBrush(zebraColor), 1.5, Qt::SolidLine, Qt::RoundCap);

	timestep = 0;
}
#include <iostream>
using namespace std;
void Helper::updateGui(){

	disp_timestep(QString::number(timestep + 1));
	timestep++;
	timestep = timestep % 25;

	disp_timestep_total(QString::number(TIME_STEPS * TIME_STEPS));

	disp_iteration(QString::number(iter.dequeue() + EVALUATE_EVERY));
	disp_iteration_total(QString::number(ITERATIONS));


}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed) {
	painter->fillRect(event->rect(), backgroundBrush);

	painter->setPen(zebraPen);
	for (int i = 0; i < 1; i++) {
		if( !zebras[i].isEmpty()){
			QPoint z = zebras[i].dequeue();
			painter->drawPoint(z);
		}

	}

	painter->setPen(lionPen);
	for (int i = 0; i < NUM_LIONS; i++) {
		if(!lions[i].isEmpty()){
			QPoint l = lions[i].dequeue();
			painter->drawPoint(l);
		}
	}

	painter->setPen(hyenaPen);
	for (int i = 0; i < NUM_HYENAS; i++) {
		if(!hyenas[i].isEmpty()){
			QPoint h = hyenas[i].dequeue();
			painter->drawPoint(h);
		}
	}
}
