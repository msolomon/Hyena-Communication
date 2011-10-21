#include "playback.h"
#include "ui_playback.h"

#include <QFile>
#include <QString>
#include <QQueue>

#include <iostream>
#include <fstream>

using namespace std;

Playback::Playback(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::Playback)
{
    ui->setupUi(this);
}

Playback::~Playback()
{
    delete ui;
}


void Playback::on_but_play_clicked(){
//	QString key = ui->combo_iterations->
//			currentText().split(QChar('\0'), QString::SkipEmptyParts)[0];
	QString key = ui->combo_iterations->currentText();
	QQueue<QPointF>* h = &hyenas[key];
	QQueue<QPointF>* l = &lions[key];

	// TODO: make this not depend on compile-time constant num of animals
	QPointF landmark = landmarks[key];
	for(int it = 0; it < l->length()/NUM_LIONS; it++){
		ui->widget->helper.landmarks.clear();
		ui->widget->helper.step.clear();
		for(int i = 0; i < NUM_HYENAS; i++)
			ui->widget->helper.hyenas[i].clear();
		for(int i = 0; i < NUM_LIONS; i++)
			ui->widget->helper.lions[i].clear();
	}
	for(int it = 0; it < l->length()/NUM_LIONS; it++){
		ui->widget->helper.landmarks.enqueue(landmark);
		for(int i = 0; i < NUM_HYENAS; i++){
			ui->widget->helper.hyenas[i].append(h->at(it * NUM_HYENAS + i));
		}
		for(int i = 0; i < NUM_LIONS; i++){
			ui->widget->helper.lions[i].append(l->at(it * NUM_LIONS + i));
		}
		ui->widget->helper.step.enqueue(it);
	}

	ui->widget->playVideo();
}

void Playback::on_but_browse_clicked(){
	QString fd = QFileDialog::getOpenFileName(this, "Video to play...");
	if(fd.length() > 0){
		ui->txt_file->setText(fd);
		lions.clear();
		hyenas.clear();
		ui->combo_iterations->clear();
		parse_video();
	}
}

void Playback::parse_video(){
	QFile f(ui->txt_file->text());
	if(f.open(QIODevice::ReadOnly)){
		QTextStream t(&f);
		QString key = "Unnamed generation";
		while(!t.atEnd()){
			QString s = t.readLine();
			if(s.startsWith("generation ")){ // new section
				key = QString("%1").arg(s.right(s.size() - 10), 20, '\0');
			} else if(s.startsWith("l")){ // landmark
				QList<QString> coords = s.split(" ", QString::SkipEmptyParts);
				coords.removeFirst(); // ditch the "l"
				landmarks[key] = QPointF(coords.takeFirst().toFloat(),
										 coords.takeFirst().toFloat());
			} else if(s.startsWith("  ")){ // hyena section
				QList<QString> coords = s.split(" ", QString::SkipEmptyParts);
				while(!coords.isEmpty()){
					float x = coords.takeFirst().toFloat();
					float y = coords.takeFirst().toFloat();
					hyenas[key].append(QPointF(x, y));
				}
			} else { // lion section
				QList<QString> coords = s.split(" ", QString::SkipEmptyParts);
				while(!coords.isEmpty()){
					float x = coords.takeFirst().toFloat();
					float y = coords.takeFirst().toFloat();
					lions[key].append(QPointF(x, y));
				}
			}
		}
		f.close();
		ui->combo_iterations->addItems(hyenas.keys());
	} else return;
}

void Playback::on_combo_iterations_currentIndexChanged(const QString &arg1){
	Q_UNUSED(arg1); // ignore the fact that we ignore arg1
	on_but_play_clicked();
}

void Playback::on_spin_fps_valueChanged(int fps){
	ui->widget->playback_ms = 1000 / fps;
}

void Playback::advance_video(){
	int idx = ui->combo_iterations->currentIndex();
	// stop after the last one (don't loop back to beginning)
	if(idx == ui->combo_iterations->count() - 1){
		return;
	}

	ui->combo_iterations->setCurrentIndex(idx + 1);
}

void Playback::on_check_sequence_toggled(bool checked){
	if(checked){
		connect(ui->widget, SIGNAL(donePlayingBack()),
				this, SLOT(advance_video()));
	} else{
		disconnect(ui->widget, SIGNAL(donePlayingBack()), 0, 0);
	}
}
