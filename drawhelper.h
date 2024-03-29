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
	void paint(QPainter *painter, QPaintEvent *event);
	void updateGui();
	QList<QPointF> hyenas[NUM_HYENAS];
    QList<bool> calling[NUM_HYENAS];
	QList<QPointF> lions[NUM_LIONS];
	QQueue<QPointF> landmarks;

	QQueue<int> iter;
	QQueue<int> step;

private:
	QPen hyenaPen;
    QPen callingPen;
	QPen namedPen;
	QPen hmarkerPen;
	QPen lionPen;
	QPen lionRadPen;
	QPen zebraPen;
	QPen callRadPen;
	QPen landmarkPen;
	QPen radStartPen;
	QPen* coloredPen[26]; // 26 most visually distinct colors
	QBrush backgroundBrush;
	QPointF zeb;
	QPen *getColor(int); // return a color given a hyena number
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
