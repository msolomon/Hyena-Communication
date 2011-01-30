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
    void connectAll();

};

#endif // QTHYENA_H
