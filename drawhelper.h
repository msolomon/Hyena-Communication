#ifndef DRAWHELPER_H
#define DRAWHELPER_H

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

class DrawHelper : public QObject{
	Q_OBJECT
public:
	DrawHelper();

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
	int it;

signals:
	void disp_timestep(QString);
	void disp_timestep_total(QString);
	void disp_iteration(QString);
	void disp_iteration_total(QString);
	void disp_trial(QString);
	void disp_trial_total(QString);
	void disp_iter_percent(int);
	void disp_iter_percent_total(int);
	void disp_trial_percent(int);
	void disp_trial_percent_total(int);
};

#endif
