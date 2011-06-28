#include "drawhelper.h"

const float hyenaSize = .8;

DrawHelper::DrawHelper() {
	backgroundBrush = QBrush(QColor(180, 240, 150));
	QColor hyenaColor = QColor(139, 69, 19);
	QColor lionColor = QColor(220, 220, 20);
	QColor zebraColor = QColor(220, 20, 20);

	zeb = QPointF(ZEBRAX, ZEBRAY);
	hyenaPen = QPen(QBrush(hyenaColor), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	hmarkerPen = QPen(QBrush(hyenaColor), .1, Qt::SolidLine, Qt::RoundCap);
	lionPen = QPen(QBrush(lionColor), 1.5, Qt::SolidLine, Qt::RoundCap);
	// 2 * b/c width is twice the radius
	lionRadPen = QPen(QBrush(lionColor), 2*LION_ATTACK_RADIUS, Qt::SolidLine, Qt::RoundCap);
	zebraPen = QPen(QBrush(zebraColor), 2*EAT_RADIUS, Qt::SolidLine, Qt::RoundCap);
	callRadPen = QPen(QBrush(zebraColor), 2*CALLING_RANGE, Qt::SolidLine, Qt::RoundCap);

	timestep = 0;
	it = -1;
}

//#include <iostream>
//using namespace std;

void DrawHelper::updateGui(){
	disp_timestep(QString::number(timestep + 1));

	const int total_steps = TIME_STEPS * NUM_TESTS;
	if(!iter.isEmpty()){
		disp_timestep_total(QString::number(total_steps));

		int curr_iteration = iter.dequeue() + 1;
		disp_iteration(QString::number(curr_iteration));
		disp_iteration_total(QString::number(GENERATIONS));

		if(it == -1)
			disp_trial_total(QString::number(TRIALS));
		if(curr_iteration == 0 && timestep == 0){
			it++;
			disp_trial(QString::number(it + 1));
		}

		const int full_trial = (GENERATIONS) * total_steps;
		int this_it = curr_iteration * total_steps + timestep;
		// cout << full_trial << " " << this_it << endl;
		disp_iter_percent(this_it);
		disp_iter_percent_total(full_trial);
	}
	timestep++;
	timestep = timestep % (total_steps);
}

void DrawHelper::paint(QPainter *painter, QPaintEvent *event) {
	const float zebraOpacity = 1;
	const float radiusOpacity = .3;
	const float animalOpacity = .7;
	painter->fillRect(event->rect(), backgroundBrush);

	painter->setOpacity(zebraOpacity);
	painter->setPen(zebraPen);
	painter->drawPoint(zeb);
	painter->setPen(callRadPen);
	painter->setOpacity(radiusOpacity);
	painter->drawPoint(zeb);
	painter->setOpacity(animalOpacity);


	painter->setPen(lionPen);
	for (int i = 0; i < NUM_LIONS; i++) {
		if(!lions[i].isEmpty()){
			QPointF l = lions[i].dequeue();
			painter->setPen(lionPen);
			painter->drawPoint(l);
			painter->setPen(lionRadPen);
			painter->setOpacity(radiusOpacity);
			painter->drawPoint(l);
			painter->setOpacity(animalOpacity);
		}
	}

	painter->setPen(hyenaPen);
	for (int i = 0; i < NUM_HYENAS; i++) {
		if(!hyenas[i].isEmpty()){
			QPointF h = hyenas[i].dequeue();
			if(HYENA_MARKERS){
				const float increment = (360*16)/((float)NUM_HYENAS);
				QRectF rect = QRectF(h.x()-hyenaSize,
									 h.y()-hyenaSize,
									 2*hyenaSize,
									 2*hyenaSize);
				painter->setPen(hmarkerPen);
				painter->drawPie(rect, (i*increment), 0);
				painter->setPen(hyenaPen);
			}
			painter->drawPoint(h);
		}
	}
}
