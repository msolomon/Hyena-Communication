/****************************************************************************
 **
 ** Copyright (C) 2006-2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 **
 ** This file is part of the documentation of the Qt Toolkit.
 **
 ** Licensees holding a valid Qt License Agreement may use this file in
 ** accordance with the rights, responsibilities and obligations
 ** contained therein.  Please consult your licensing agreement or
 ** contact qt-sales@nokia.com if any conditions of this licensing
 ** agreement are not clear to you.
 **
 ** Further information about Qt licensing is available at:
 ** http://trolltech.com/products/appdev/licensing
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

#include <QtGui>
#include <qtconcurrentrun.h>
#include "widget.h"
#include "helper.h"

#include "globals.h"
#include <assert.h>

#include <iostream>
using namespace std;

Widget::Widget(QWidget *parent) : QWidget(parent){
	//setFixedSize(FIELDX, FIELDY);
	//connect((QObject*) &p, SIGNAL(update()), this, SLOT(animate()));
}

void Widget::runTrial(){
      p.generate(&helper);
      if(DRAW){
          timer.start(DRAW_MS);
      }
      connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));
      // TODO: make this increment
      QtConcurrent::run(&p, &pop::evolve, 0);
      //p.evolve(0);

}

void Widget::animate() {
		if(!helper.zebras[0].isEmpty()){
			helper.updateGui();
			repaint();
	}
}

void Widget::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(this);
	painter.setWindow(0, 0, X, Y);
	painter.setRenderHint(QPainter::Antialiasing);
	helper.paint(&painter, event, elapsed);
	painter.end();
}

void Widget::resizeEvent(QResizeEvent *event){
	// TODO: do this in a layout. harder than it sounds in QT
	QSize s = size();
	// ensure a proportional widget size
	if(s.width() != s.height()){
		if(s.width() > s.height()){
			resize(s.height(), s.height());
		} else{
			resize(s.width(), s.width());
		}
	}
}

