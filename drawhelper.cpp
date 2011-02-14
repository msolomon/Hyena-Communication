#include "drawhelper.h"

DrawHelper::DrawHelper() {
	backgroundBrush = QBrush(QColor(20, 155, 20));
	QColor hyenaColor = QColor(139, 69, 19);
	QColor lionColor = QColor(220, 220, 20);
	QColor zebraColor = QColor(220, 20, 20);

	hyenaPen = QPen(QBrush(hyenaColor), .5, Qt::SolidLine, Qt::RoundCap);
	lionPen = QPen(QBrush(lionColor), 1, Qt::SolidLine, Qt::RoundCap);
	lionRadPen = QPen(QBrush(lionColor), LION_ATTACK_RADIUS, Qt::SolidLine, Qt::RoundCap);
	zebraPen = QPen(QBrush(zebraColor), 1.5, Qt::SolidLine, Qt::RoundCap);

	timestep = 0;
	it = -1;
}

void DrawHelper::updateGui(){

	disp_timestep(QString::number(timestep + 1));

	const int total_steps = TIME_STEPS * NUM_TESTS;

	disp_timestep_total(QString::number(total_steps));

	int curr_iteration = iter.dequeue();
	disp_iteration(QString::number(curr_iteration + EVALUATE_EVERY));
	disp_iteration_total(QString::number(ITERATIONS));

	if(it == -1)
		disp_trial_total(QString::number(TRIALS));
	if(curr_iteration == 0 && timestep == 0){
		it++;
		disp_trial(QString::number(it + 1));
	}

	const int full_trial = (ITERATIONS) * total_steps * 2 - EVALUATE_EVERY;
	int this_it = curr_iteration * total_steps * 2 + timestep * EVALUATE_EVERY;
	disp_iter_percent(this_it);
	disp_iter_percent_total(full_trial);
	disp_trial_percent((it * full_trial) + this_it);
	disp_trial_percent_total(full_trial * TRIALS);

	timestep++;
	timestep = timestep % (total_steps * 2);
}

void DrawHelper::paint(QPainter *painter, QPaintEvent *event) {
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
			painter->setPen(lionPen);
			painter->drawPoint(l);
			painter->setPen(lionRadPen);
			painter->setOpacity(.2);
			painter->drawPoint(l);
			painter->setOpacity(1);
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
