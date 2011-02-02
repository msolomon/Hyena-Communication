#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QGLWidget>
#include <QTimer>
#include <QtGui>
#include <QtConcurrentRun>

#include "globals.h"

#include "helper.h"
#include "pop.h"

class Helper;
class QPaintEvent;

class Widget: public QWidget {
//class Widget: public QGLWidget {
	Q_OBJECT

public:
	Widget(QWidget *parent);
	Helper helper;
	pop p;

public slots:
	void runTrial();
	void animate();

signals:
	void resized(int);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	QTimer timer;
};

#endif
