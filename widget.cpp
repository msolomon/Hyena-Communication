#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent){
}

void Widget::runTrial(){
      p.generate(&helper);
      if(DRAW){
          timer.start(DRAW_MS);
      }
      connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));
      QtConcurrent::run(&p, &pop::evolve_repeat);
}

void Widget::animate() {
		if(!helper.hyenas[0].isEmpty()){
			helper.updateGui();
			repaint();
	}
}

void Widget::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(this);
	painter.setWindow(0, 0, X, Y);
	painter.setRenderHint(QPainter::Antialiasing);
	helper.paint(&painter, event);
	painter.end();
}

void Widget::resizeEvent(QResizeEvent *event){
	Q_UNUSED(event); // ignore the fact that we ignore the resize event
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

