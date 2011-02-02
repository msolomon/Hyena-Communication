#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QBrush>
#include <QPen>
#include <QPoint>
#include <QQueue>
#include <QtGui>
#include <QList>

#include "globals.h"

class QPainter;
class QPaintEvent;

class Helper : public QObject{
	Q_OBJECT
public:
	Helper();

public:
	void paint(QPainter *painter, QPaintEvent *event);
	void updateGui();
	QQueue<QPoint> hyenas[NUM_HYENAS];
	QQueue<QPoint> lions[NUM_LIONS];
	QQueue<QPoint> zebras[1];

	QQueue<int> iter;
	QQueue<int> step;

private:
	QPen hyenaPen;
	QPen lionPen;
	QPen zebraPen;
	QBrush backgroundBrush;
	int timestep;

signals:
	void disp_timestep(QString);
	void disp_timestep_total(QString);
	void disp_iteration(QString);
	void disp_iteration_total(QString);
	void disp_percent(int);
	void disp_percent_total(int);
};

#endif
