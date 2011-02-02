#include "helper.h"

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

void Helper::updateGui(){

	disp_timestep(QString::number(timestep + 1));

	const int total_steps = TIME_STEPS * NUM_TESTS;

	disp_timestep_total(QString::number(total_steps));

	int curr_iteration = iter.dequeue();
	disp_iteration(QString::number(curr_iteration + EVALUATE_EVERY));
	disp_iteration_total(QString::number(ITERATIONS));

	disp_percent(curr_iteration * total_steps * 2 + timestep * EVALUATE_EVERY);
	disp_percent_total((ITERATIONS) * total_steps * 2 - EVALUATE_EVERY);

	timestep++;
	timestep = timestep % (total_steps * 2);
}

void Helper::paint(QPainter *painter, QPaintEvent *event) {
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
