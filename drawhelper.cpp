#include "drawhelper.h"

const float hyenaSize = .8;

DrawHelper::DrawHelper() {
	backgroundBrush = QBrush(QColor(130, 200, 110));
	QColor hyenaColor = QColor(139, 69, 19);
	QColor namedColor = QColor(139, 69, 150);
	QColor lionColor = QColor(220, 220, 20);
	QColor zebraColor = QColor(220, 20, 20);
	QColor landmarkColor = QColor(30, 200, 30);
	QColor radStartColor = QColor(180, 240, 150);

	zeb = QPointF(ZEBRAX, ZEBRAY);
	hyenaPen = QPen(QBrush(hyenaColor), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	namedPen = QPen(QBrush(namedColor), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	hmarkerPen = QPen(QBrush("black"), .1, Qt::SolidLine, Qt::RoundCap);
	lionPen = QPen(QBrush(lionColor), 1.5, Qt::SolidLine, Qt::RoundCap);
	// 2 * b/c width is twice the radius
	lionRadPen = QPen(QBrush(lionColor), 2*LION_ATTACK_RADIUS, Qt::SolidLine, Qt::RoundCap);
    zebraPen = QPen(QBrush(zebraColor), 2*1, Qt::SolidLine, Qt::RoundCap);
	callRadPen = QPen(QBrush(zebraColor), 2*CALLING_RANGE, Qt::SolidLine, Qt::RoundCap);
	radStartPen = QPen(QBrush(radStartColor), 2*RADIUS_START, Qt::SolidLine, Qt::RoundCap);
	landmarkPen = QPen(QBrush(landmarkColor), 2, Qt::SolidLine, Qt::RoundCap);

	coloredPen[0] = new QPen(QBrush(QColor("#191919")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[1] = new QPen(QBrush(QColor("#ffff00")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[2] = new QPen(QBrush(QColor("#4c005c")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[3] = new QPen(QBrush(QColor("#ff5005")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[4] = new QPen(QBrush(QColor("#5ef1f2")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[5] = new QPen(QBrush(QColor("#ff0010")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[6] = new QPen(QBrush(QColor("#ffff80")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[7] = new QPen(QBrush(QColor("#808080")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[8] = new QPen(QBrush(QColor("#2bce48")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[9] = new QPen(QBrush(QColor("#ffa8bb")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[10] = new QPen(QBrush(QColor("#0075dc")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[11] = new QPen(QBrush(QColor("#ffcc99")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[12] = new QPen(QBrush(QColor("#740aff")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[13] = new QPen(QBrush(QColor("#ffa405")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[14] = new QPen(QBrush(QColor("#c20088")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[15] = new QPen(QBrush(QColor("#e0ff66")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[16] = new QPen(QBrush(QColor("#990000")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[17] = new QPen(QBrush(QColor("#9dcc00")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[18] = new QPen(QBrush(QColor("#993f00")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[19] = new QPen(QBrush(QColor("#f0a3ff")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[20] = new QPen(QBrush(QColor("#426600")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[21] = new QPen(QBrush(QColor("#94ffb5")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[22] = new QPen(QBrush(QColor("#003380")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[23] = new QPen(QBrush(QColor("#8f7f00")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[24] = new QPen(QBrush(QColor("#005c31")), hyenaSize, Qt::SolidLine, Qt::RoundCap);
	coloredPen[25] = new QPen(QBrush(QColor("#00998f")), hyenaSize, Qt::SolidLine, Qt::RoundCap);

	timestep = 0;
	it = -1;
}

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
	const float radiusOpacity = .2;
	const float animalOpacity = ANIMAL_MAX_OPACITY;
	const float endOpacity = ANIMAL_MIN_OPACITY;
	QPen *pen;
	painter->fillRect(event->rect(), backgroundBrush);

	painter->setOpacity(zebraOpacity);
	if(!landmarks.isEmpty()){
		painter->setPen(landmarkPen);
		painter->drawPoint(landmarks.dequeue());
	}

	// set up the field
	painter->setOpacity(zebraOpacity);
	painter->setPen(radStartPen);
	painter->drawPoint(zeb);
	painter->setPen(zebraPen);
	painter->drawPoint(zeb);
	painter->setOpacity(radiusOpacity);
	painter->setPen(callRadPen);
	painter->drawPoint(zeb);
	painter->setOpacity(animalOpacity);

	int current_timestep = -1;
	if(!step.isEmpty())
		current_timestep = step.dequeue();
	int start;
	if(SMEAR_DRAW){
		start = 0;
		if((SMEAR_LAST > 0) && (current_timestep - SMEAR_LAST) > 0)
			start = current_timestep - SMEAR_LAST;
	}

	else
		start = current_timestep;

	// draw lions
	painter->setPen(lionPen);
	for(int j = start; j <= current_timestep; j++){
		float modifier = (current_timestep - j) / (current_timestep + 1.0);
		float nowOpacity = (modifier*animalOpacity) + endOpacity;
		if(!FADE_DRAW) nowOpacity = animalOpacity;
		if(FADE_OUT) nowOpacity = ((nowOpacity-endOpacity)*(j+1.0)/(current_timestep + 1.0)) + endOpacity;
		painter->setOpacity(nowOpacity);
		for (int i = 0; i < NUM_LIONS; i++) {
			QPointF l = lions[i][j];
			painter->setPen(lionPen);
			painter->drawPoint(l);
			painter->setPen(lionRadPen);
			if(j == current_timestep){
				painter->setOpacity(radiusOpacity);
				painter->drawPoint(l);
				painter->setOpacity(nowOpacity);
			}
		}
	}
	for(int j = start; j <= current_timestep; j++){
		float modifier = (current_timestep - j) / (current_timestep + 1.0);
		float nowOpacity = (modifier*animalOpacity) + endOpacity;
		if(!FADE_DRAW) nowOpacity = animalOpacity;
		if(FADE_OUT) nowOpacity = ((nowOpacity-endOpacity)*(j+1.0)/(current_timestep + 1.0)) + endOpacity;
		painter->setOpacity(nowOpacity);
		for (int i = 0; i < NUM_HYENAS; i++) {
			QPointF h = hyenas[i][j];
			if(HYENA_MARKERS){
				const float increment = (360*16)/((float)NUM_HYENAS);
				QRectF rect = QRectF(h.x()-hyenaSize,
									 h.y()-hyenaSize,
									 2*hyenaSize,
									 2*hyenaSize);
				painter->setPen(hmarkerPen);
				painter->drawPie(rect, (i*increment), 0);
//				painter->setPen(&getColor(i));
			}

			pen = getColor(i);
			painter->setPen(*pen);
			painter->drawPoint(h);
		}
	}
}

QPen* DrawHelper::getColor(int hyenaNumber){
	if(0 <= hyenaNumber && hyenaNumber < 26){
		return coloredPen[hyenaNumber];
	} else {
		return &hyenaPen;
	}
}
