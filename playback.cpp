#include "playback.h"
#include "ui_playback.h"

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


void Playback::on_but_play_clicked()
{
	ifstream f;
	try{
		f.open(ui->txt_file->text().toStdString().c_str());
		cout << "Test" << endl;
		f.close();
	} catch(int e) {
		return;
	}
}

void Playback::on_but_browse_clicked()
{
	QString::QString fd = QFileDialog::getOpenFileName(this, "Video to play...");
	if(fd.length() > 0)
		ui->txt_file->setText(fd);
}
