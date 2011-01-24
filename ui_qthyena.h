/********************************************************************************
** Form generated from reading UI file 'qthyena.ui'
**
** Created: Sun Jan 23 20:50:30 2011
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "widget.h"

QT_BEGIN_NAMESPACE

class Ui_qthyenaClass
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    Widget *widget;
    QProgressBar *percentCalculated;
    QPushButton *beginButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qthyenaClass)
    {
        if (qthyenaClass->objectName().isEmpty())
            qthyenaClass->setObjectName(QString::fromUtf8("qthyenaClass"));
        qthyenaClass->resize(902, 734);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qthyenaClass->sizePolicy().hasHeightForWidth());
        qthyenaClass->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(qthyenaClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new Widget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(400, 400));
        widget->setCursor(QCursor(Qt::ArrowCursor));
        widget->setAcceptDrops(true);
        widget->setAutoFillBackground(true);

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        percentCalculated = new QProgressBar(centralwidget);
        percentCalculated->setObjectName(QString::fromUtf8("percentCalculated"));
        percentCalculated->setValue(24);

        gridLayout->addWidget(percentCalculated, 1, 0, 1, 1);

        beginButton = new QPushButton(centralwidget);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(beginButton->sizePolicy().hasHeightForWidth());
        beginButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(beginButton, 1, 1, 1, 1);

        qthyenaClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qthyenaClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 902, 27));
        qthyenaClass->setMenuBar(menubar);
        statusbar = new QStatusBar(qthyenaClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        qthyenaClass->setStatusBar(statusbar);

        retranslateUi(qthyenaClass);
        QObject::connect(beginButton, SIGNAL(clicked()), beginButton, SLOT(close()));
        QObject::connect(beginButton, SIGNAL(clicked()), widget, SLOT(runTrial()));

        QMetaObject::connectSlotsByName(qthyenaClass);
    } // setupUi

    void retranslateUi(QMainWindow *qthyenaClass)
    {
        qthyenaClass->setWindowTitle(QApplication::translate("qthyenaClass", "Hyena Evolution", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        beginButton->setText(QApplication::translate("qthyenaClass", "Begin", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qthyenaClass: public Ui_qthyenaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHYENA_H
