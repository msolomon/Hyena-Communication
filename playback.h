#ifndef PLAYBACK_H
#define PLAYBACK_H

#include <QWidget>
#include <QString>
#include <QFileDialog>

namespace Ui {
    class Playback;
}

class Playback : public QWidget
{
    Q_OBJECT

public:
    explicit Playback(QWidget *parent = 0);
    ~Playback();

private:
    Ui::Playback *ui;

private slots:
	void on_but_browse_clicked();
 void on_but_play_clicked();
};

#endif // PLAYBACK_H
