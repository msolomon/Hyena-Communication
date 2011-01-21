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
#include "widget.h"
#include "helper.h"

#include "globals.h"
#include <assert.h>
Widget::Widget(Helper *helper, QWidget *parent) :
	QWidget(parent), helper(helper) {
	elapsed = 0;
	setFixedSize(FIELDX, FIELDY);
}

void Widget::animate() {
	//elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
	//bool done = false;
	//while (!done){
	// std::cout << "iteration";
	// done = true;
	// for (int i = 0; i < NUM_HYENAS; i++){
	//	 int currx = helper->currHyenas[i].rx();
	//	 int curry = helper->currHyenas[i].ry();
	//	 int endx = helper->hyenas[i].x();
	//	 int endy = helper->hyenas[i].y();

	//	 if(currx < endx){
	//		 currx++;
	//		 done = false;
	//	 }
	//	 else if (currx > endx){
	//		 currx--;
	//		 done = false;
	//	 }
	//	 if(curry < endy){
	//		 curry++;
	//		 done = false;
	//	 }
	//	 else if (curry > endy){
	//		 curry--;
	//		 done = false;
	//	 }
	// }
	// for (int i = 0; i < NUM_LIONS; i++){
	//	 int currx = helper->currLions[i].rx();
	//	 int curry = helper->currLions[i].ry();
	//	 int endx = helper->lions[i].x();
	//	 int endy = helper->lions[i].y();
	//	 if(currx < endx){
	//		 currx++;
	//		 done = false;
	//	 }
	//	 else if (currx > endx){
	//		 currx--;
	//		 done = false;
	//	 }
	//	 if(curry < endy){
	//		 curry++;
	//		 done = false;
	//	 }
	//	 else if (curry > endy){
	//		 curry--;
	//		 done = false;
	//	 }
	// }

	//   repaint();
	//}

	repaint();
	assert(1 == 2);
}

void Widget::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	helper->paint(&painter, event, elapsed);
	painter.end();
}
