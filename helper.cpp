#include <QtGui>
#include "helper.h"
#include <QList>
#include <QPoint>
#include <assert.h>
Helper::Helper() {
	//QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
	//gradient.setColorAt(-1.0, QColor(200, 255, 200)); //Qt::white);
	//gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));


	background = QBrush(QColor(20, 155, 20));
	//circleBrush = QBrush(gradient);
	hyenaColor = QBrush(QColor(139, 69, 19));
	lionColor = QBrush(QColor(220, 220, 20));
	zebraColor = QBrush(QColor(220, 20, 20));
	//circlePen = QPen(Qt::black);
	//circlePen.setWidth(1);
	textPen = QPen(Qt::white);
	textFont.setPixelSize(50);
	/*
	 hyenas.append(QPoint(20,20));
	 hyenas.append(QPoint(80,80));
	 lions.append(QPoint(100,30));
	 zebras.append(QPoint(80,100));
	 */
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed) {
	painter->fillRect(event->rect(), background);
	//painter->save();
	//painter->setPen(circlePen);
	/*     painter->translate(100, 100);

	 painter->save();
	 painter->rotate(elapsed * 0.030);

	 qreal r = elapsed/1000.0;
	 int n = 30;
	 for (int i = 0; i < n; ++i) {
	 painter->rotate(30);
	 qreal radius = 0 + 120.0*((i+r)/n);
	 qreal circleRadius = 1 + ((i+r)/n)*20;
	 painter->drawEllipse(QRectF(radius, -circleRadius,
	 circleRadius*2, circleRadius*2));
	 }
	 */
	painter->setBrush(zebraColor);
	for (int i = 0; i < 1; i++) {
		painter->drawEllipse(zebras[i], 12, 12);
	}

	painter->setBrush(lionColor);
	for (int i = 0; i < NUM_LIONS; i++) {
		painter->drawEllipse(lions[i], 10, 10);
	}

	painter->setBrush(hyenaColor);
	for (int i = 0; i < NUM_HYENAS; i++) {
		painter->drawEllipse(hyenas[i], 8, 8);
	}

	//assert(5==2);
	//painter->restore();
	/*
	 painter->setPen(textPen);
	 painter->setFont(textFont);
	 painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, "Qt");
	 */
}
