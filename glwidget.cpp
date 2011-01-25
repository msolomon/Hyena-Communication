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
#include "glwidget.h"
#include "helper.h"

GLWidget::GLWidget(Helper *helper, QWidget *parent) :
	QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper) {
	elapsed = 0;
	setFixedSize(600, 600);
	setAutoFillBackground(false);
}

void GLWidget::animate() {
	repaint();
}

void GLWidget::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(this);
	//painter.setRenderHint(QPainter::HighQualityAntialiasing); // seems to look worse
	painter.setRenderHint(QPainter::Antialiasing);
	//painter.setWindow(-300, -300, 600, 600);
	helper->paint(&painter, event, elapsed);
	painter.end();
}
