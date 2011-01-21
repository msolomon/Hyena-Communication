/********************************************************************************
 ** Form generated from reading UI file 'qthyena.ui'
 **
 ** Created: Wed Jan 19 19:26:11 2011
 **      by: Qt User Interface Compiler version 4.7.0
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_QTHYENA_H
#define UI_QTHYENA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qthyenaClass {
public:
	QWidget *centralwidget;
	QMenuBar *menubar;
	QStatusBar *statusbar;

	void setupUi(QMainWindow *qthyenaClass) {
		if (qthyenaClass->objectName().isEmpty())
			qthyenaClass->setObjectName(QString::fromUtf8("qthyenaClass"));
		qthyenaClass->resize(800, 600);
		centralwidget = new QWidget(qthyenaClass);
		centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
		qthyenaClass->setCentralWidget(centralwidget);
		menubar = new QMenuBar(qthyenaClass);
		menubar->setObjectName(QString::fromUtf8("menubar"));
		menubar->setGeometry(QRect(0, 0, 800, 21));
		qthyenaClass->setMenuBar(menubar);
		statusbar = new QStatusBar(qthyenaClass);
		statusbar->setObjectName(QString::fromUtf8("statusbar"));
		qthyenaClass->setStatusBar(statusbar);

		retranslateUi(qthyenaClass);

		QMetaObject::connectSlotsByName(qthyenaClass);
	} // setupUi

	void retranslateUi(QMainWindow *qthyenaClass) {
		qthyenaClass->setWindowTitle(QApplication::translate("qthyenaClass",
				"MainWindow", 0, QApplication::UnicodeUTF8));
	} // retranslateUi

};

namespace Ui {
class qthyenaClass: public Ui_qthyenaClass {
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHYENA_H
