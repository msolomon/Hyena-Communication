#include <QtGui>
#include "helper.h"
#include <QList>
#include <QPoint>
#include <assert.h>
Helper::Helper() {
	background = QBrush(QColor(20, 155, 20));
	hyenaColor = QBrush(QColor(139, 69, 19));
	lionColor = QBrush(QColor(220, 220, 20));
	zebraColor = QBrush(QColor(220, 20, 20));

	textPen = QPen(Qt::white);
	textFont.setPixelSize(50);
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed) {
	painter->fillRect(event->rect(), background);

	painter->setBrush(zebraColor);
	for (int i = 0; i < 1; i++) {
		if( !zebras[i].isEmpty()){
			painter->drawEllipse(zebras[i].dequeue(), 12, 12);
		}

	}

	painter->setBrush(lionColor);
	for (int i = 0; i < NUM_LIONS; i++) {
		if(!lions[i].isEmpty()){
			painter->drawEllipse(lions[i].dequeue(), 10, 10);
		}
	}

	painter->setBrush(hyenaColor);
	for (int i = 0; i < NUM_HYENAS; i++) {
		if(!hyenas[i].isEmpty()){
			painter->drawEllipse(hyenas[i].dequeue(), 8, 8);
		}
	}
}
