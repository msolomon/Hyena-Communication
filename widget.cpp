#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent){
	playback_ms = 33;
}

void Widget::runTrial(){
	p.helper = &helper;
	connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));
	if(DRAW){
		timer.start(playback_ms);
	}
	QtConcurrent::run(&p, &pop::evolve_repeat);
}

void Widget::playVideo(){
	// abusing recursion a bit, but it works
	if(!helper.step.isEmpty()){
		repaint();
		QTimer::singleShot(playback_ms, this, SLOT(playVideo()));
	} else{
		donePlayingBack();
	}

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
	if(ANTIALIAS)
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

