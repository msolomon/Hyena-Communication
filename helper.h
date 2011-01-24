#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPoint>
#include <QQueue>

#include "globals.h"

class QPainter;
class QPaintEvent;

class Helper : QObject{
	Q_OBJECT
public:
	Helper();

public:
	void paint(QPainter *painter, QPaintEvent *event, int elapsed);
	QQueue<QPoint> hyenas[NUM_HYENAS];
	QQueue<QPoint> lions[NUM_LIONS];
	QQueue<QPoint> zebras[1];

private:
	QBrush background;
	QBrush hyenaColor;
	QBrush lionColor;
	QBrush zebraColor;
	QFont textFont;
	QPen circlePen;
	QPen textPen;
};

#endif
