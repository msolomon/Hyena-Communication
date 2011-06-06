#ifndef QTHYENA_H
#define QTHYENA_H

#include <QtGui/QMainWindow>
#include "ui_qthyena.h"
#include "playback.h"

class qthyena : public QMainWindow
{
    Q_OBJECT

public:
    qthyena(QWidget *parent = 0);
    ~qthyena();

private slots:
    void on_but_playback_clicked();

	void on_spinBox_valueChanged(int arg1);

private:
    Ui::qthyenaClass ui;
    Playback pb;
    void connectAll();

};

#endif // QTHYENA_H
