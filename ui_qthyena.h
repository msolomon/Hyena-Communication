/********************************************************************************
** Form generated from reading UI file 'qthyena.ui'
**
** Created: Sun Jan 23 20:09:28 2011
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
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "widget.h"

QT_BEGIN_NAMESPACE

class Ui_qthyenaClass
{
public:
    QWidget *centralwidget;
    Widget *widget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qthyenaClass)
    {
        if (qthyenaClass->objectName().isEmpty())
            qthyenaClass->setObjectName(QString::fromUtf8("qthyenaClass"));
        qthyenaClass->resize(400, 481);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qthyenaClass->sizePolicy().hasHeightForWidth());
        qthyenaClass->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(qthyenaClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        widget = new Widget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 400, 400));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(400, 400));
        widget->setCursor(QCursor(Qt::ArrowCursor));
        widget->setAcceptDrops(true);
        widget->setAutoFillBackground(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 400, 93, 27));
        qthyenaClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qthyenaClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 27));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        qthyenaClass->setMenuBar(menubar);
        statusbar = new QStatusBar(qthyenaClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        qthyenaClass->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());

        retranslateUi(qthyenaClass);
        QObject::connect(pushButton, SIGNAL(clicked()), widget, SLOT(runTrial()));

        QMetaObject::connectSlotsByName(qthyenaClass);
    } // setupUi

    void retranslateUi(QMainWindow *qthyenaClass)
    {
        qthyenaClass->setWindowTitle(QApplication::translate("qthyenaClass", "MainWindow", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("qthyenaClass", "PushButton", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("qthyenaClass", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qthyenaClass: public Ui_qthyenaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHYENA_H
