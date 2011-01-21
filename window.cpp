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
#include <QtConcurrentRun>
#include "glwidget.h"
#include "widget.h"
#include "window.h"
#include "globals.h"
#include "pop.h"
	pop p;

Window::Window()
	: QWidget()
{
	//Widget *native = new Widget(&helper, this);
	GLWidget *openGL = new GLWidget(&helper, this);
	//QLabel *nativeLabel = new QLabel(tr("Native"));
	//nativeLabel->setAlignment(Qt::AlignHCenter);
	QLabel *openGLLabel = new QLabel(tr("OpenGL"));
	openGLLabel->setAlignment(Qt::AlignHCenter);

	QGridLayout *layout = new QGridLayout;
	//layout->addWidget(native, 0, 0);
	layout->addWidget(openGL, 0, 1);
	//layout->addWidget(nativeLabel, 1, 0);
	layout->addWidget(openGLLabel, 1, 1);
	setLayout(layout);

	p.generate(openGL);
	connect((QObject*) &p, SIGNAL(pop::update()), openGL, SLOT(animate()));
	//p.evolve(0);
	for (int i = 0; i < TRIALS; i++){
		QtConcurrent::run(&p, &pop::evolve, i);
	}
	//QTimer *timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
	//connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
	//timer->start(50);



	setWindowTitle(tr("Hyena Evolution"));
}