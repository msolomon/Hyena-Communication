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
	for(int it = 0; it < l->length()/NUM_LIONS; it++){
		for(int i = 0; i < NUM_HYENAS; i++){
			ui->widget->helper.hyenas[i].enqueue(h->at(it * NUM_HYENAS + i));
		}
		for(int i = 0; i < NUM_LIONS; i++){
			ui->widget->helper.lions[i].enqueue(l->at(it * NUM_LIONS + i));
		}
	}

	ui->widget->playVideo();
}

void Playback::on_but_browse_clicked(){
	QString::QString fd = QFileDialog::getOpenFileName(this, "Video to play...");
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
		QString key = "Unnamed iteration";
		while(!t.atEnd()){
			QString s = t.readLine();
			if(s.startsWith("Iteration ")){ // new section
				key = QString("%1").arg(s.right(s.size() - 10), 20, '\0');
			} else if(s.startsWith(" ")){ // hyena section
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

void Playback::on_combo_iterations_currentIndexChanged(const QString &arg1)
{
	on_but_play_clicked();
}

void Playback::on_spin_fps_valueChanged(int fps)
{
	ui->widget->playback_ms = 1000 / fps;
}
