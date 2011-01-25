#ifndef QTHYENA_H
#define QTHYENA_H

#include <QtGui/QMainWindow>
#include "ui_qthyena.h"

class qthyena : public QMainWindow
{
    Q_OBJECT

public:
    qthyena(QWidget *parent = 0);
    ~qthyena();

private:
    Ui::qthyenaClass ui;

};

#endif // QTHYENA_H
