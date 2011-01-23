#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPoint>
#include <QList>

#include "globals.h"

class QPainter;
class QPaintEvent;

class Helper : QObject{
	Q_OBJECT
public:
	Helper();

public:
	void paint(QPainter *painter, QPaintEvent *event, int elapsed);
	QPoint hyenas[NUM_HYENAS];
	QPoint lions[NUM_LIONS];
	QPoint zebras[1];

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
