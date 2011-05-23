#ifndef PLAYBACK_H
#define PLAYBACK_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QQueue>
#include <QMap>
#include <QPointF>

namespace Ui {
    class Playback;
}

class Playback : public QWidget
{
    Q_OBJECT

public:
    explicit Playback(QWidget *parent = 0);
    ~Playback();
	QMap<QString, QQueue<QPointF> > hyenas;
	QMap<QString, QQueue<QPointF> > lions;

private:
    Ui::Playback *ui;
	void parse_video();

private slots:
	void on_but_browse_clicked();
	void on_but_play_clicked();
	void on_combo_iterations_currentIndexChanged(const QString &arg1);
	void on_spin_fps_valueChanged(int arg1);
};

#endif // PLAYBACK_H
