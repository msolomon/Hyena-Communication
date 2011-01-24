/********************************************************************************
** Form generated from reading UI file 'qthyena.ui'
**
** Created: Mon Jan 24 11:37:46 2011
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
    QProgressBar *percentCalculated;
    QPushButton *beginButton;
    QGridLayout *gridLayout_3;
    Widget *widget;
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
        percentCalculated = new QProgressBar(centralwidget);
        percentCalculated->setObjectName(QString::fromUtf8("percentCalculated"));
        percentCalculated->setValue(24);

        gridLayout->addWidget(percentCalculated, 2, 0, 1, 1);

        beginButton = new QPushButton(centralwidget);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(beginButton->sizePolicy().hasHeightForWidth());
        beginButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(beginButton, 2, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new Widget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(100);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setMinimumSize(QSize(400, 400));
        widget->setCursor(QCursor(Qt::ArrowCursor));
        widget->setAcceptDrops(false);
        widget->setAutoFillBackground(true);

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);

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
        beginButton->setText(QApplication::translate("qthyenaClass", "Begin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class qthyenaClass: public Ui_qthyenaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHYENA_H
