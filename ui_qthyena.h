/********************************************************************************
** Form generated from reading UI file 'qthyena.ui'
**
** Created: Tue Jan 25 12:52:37 2011
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
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
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
    QGroupBox *calculatingBox;
    QGridLayout *gridLayout_2;
    QProgressBar *calc_percent;
    QLabel *label;
    QGroupBox *statsBox;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLineEdit *calc_trials_curr;
    QLineEdit *calc_trials_total;
    QLabel *label_3;
    QLineEdit *calc_iterations_curr;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *calc_iterations_total;
    QPushButton *beginButton;
    Widget *widget;
    QGroupBox *displayingBox;
    QFormLayout *formLayout;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *disp_percent;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *disp_iteration_curr;
    QLabel *label_5;
    QLineEdit *disp_iteration_total;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *disp_time_curr;
    QLabel *label_4;
    QLineEdit *disp_time_total;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qthyenaClass)
    {
        if (qthyenaClass->objectName().isEmpty())
            qthyenaClass->setObjectName(QString::fromUtf8("qthyenaClass"));
        qthyenaClass->resize(982, 773);
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
        calculatingBox = new QGroupBox(centralwidget);
        calculatingBox->setObjectName(QString::fromUtf8("calculatingBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(calculatingBox->sizePolicy().hasHeightForWidth());
        calculatingBox->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(calculatingBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        calc_percent = new QProgressBar(calculatingBox);
        calc_percent->setObjectName(QString::fromUtf8("calc_percent"));
        calc_percent->setValue(0);

        gridLayout_2->addWidget(calc_percent, 1, 2, 1, 1);

        label = new QLabel(calculatingBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMargin(5);

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        statsBox = new QGroupBox(calculatingBox);
        statsBox->setObjectName(QString::fromUtf8("statsBox"));
        sizePolicy.setHeightForWidth(statsBox->sizePolicy().hasHeightForWidth());
        statsBox->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(statsBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_2 = new QLabel(statsBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMargin(5);

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        calc_trials_curr = new QLineEdit(statsBox);
        calc_trials_curr->setObjectName(QString::fromUtf8("calc_trials_curr"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(calc_trials_curr->sizePolicy().hasHeightForWidth());
        calc_trials_curr->setSizePolicy(sizePolicy2);
        calc_trials_curr->setReadOnly(true);

        gridLayout_4->addWidget(calc_trials_curr, 0, 1, 1, 1);

        calc_trials_total = new QLineEdit(statsBox);
        calc_trials_total->setObjectName(QString::fromUtf8("calc_trials_total"));

        gridLayout_4->addWidget(calc_trials_total, 0, 3, 1, 1);

        label_3 = new QLabel(statsBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMargin(5);

        gridLayout_4->addWidget(label_3, 0, 2, 1, 1);

        calc_iterations_curr = new QLineEdit(statsBox);
        calc_iterations_curr->setObjectName(QString::fromUtf8("calc_iterations_curr"));

        gridLayout_4->addWidget(calc_iterations_curr, 1, 1, 1, 1);

        label_6 = new QLabel(statsBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMargin(5);

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        label_7 = new QLabel(statsBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMargin(5);

        gridLayout_4->addWidget(label_7, 1, 2, 1, 1);

        calc_iterations_total = new QLineEdit(statsBox);
        calc_iterations_total->setObjectName(QString::fromUtf8("calc_iterations_total"));

        gridLayout_4->addWidget(calc_iterations_total, 1, 3, 1, 1);


        gridLayout_2->addWidget(statsBox, 0, 1, 1, 2);

        beginButton = new QPushButton(calculatingBox);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(beginButton->sizePolicy().hasHeightForWidth());
        beginButton->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(beginButton, 0, 0, 1, 1);


        gridLayout->addWidget(calculatingBox, 1, 3, 1, 3);

        widget = new Widget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(100);
        sizePolicy4.setVerticalStretch(100);
        sizePolicy4.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy4);
        widget->setMinimumSize(QSize(400, 400));
        widget->setCursor(QCursor(Qt::ArrowCursor));
        widget->setAcceptDrops(false);
        widget->setAutoFillBackground(true);

        gridLayout->addWidget(widget, 0, 3, 1, 2);

        displayingBox = new QGroupBox(centralwidget);
        displayingBox->setObjectName(QString::fromUtf8("displayingBox"));
        sizePolicy.setHeightForWidth(displayingBox->sizePolicy().hasHeightForWidth());
        displayingBox->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(displayingBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        groupBox_3 = new QGroupBox(displayingBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy5);
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        disp_percent = new QProgressBar(groupBox_3);
        disp_percent->setObjectName(QString::fromUtf8("disp_percent"));
        disp_percent->setMinimum(5);
        disp_percent->setValue(4);

        horizontalLayout_3->addWidget(disp_percent);


        formLayout->setWidget(2, QFormLayout::SpanningRole, groupBox_3);

        groupBox = new QGroupBox(displayingBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        disp_iteration_curr = new QLineEdit(groupBox);
        disp_iteration_curr->setObjectName(QString::fromUtf8("disp_iteration_curr"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(disp_iteration_curr->sizePolicy().hasHeightForWidth());
        disp_iteration_curr->setSizePolicy(sizePolicy6);
        disp_iteration_curr->setReadOnly(true);

        horizontalLayout->addWidget(disp_iteration_curr);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_5);

        disp_iteration_total = new QLineEdit(groupBox);
        disp_iteration_total->setObjectName(QString::fromUtf8("disp_iteration_total"));
        sizePolicy6.setHeightForWidth(disp_iteration_total->sizePolicy().hasHeightForWidth());
        disp_iteration_total->setSizePolicy(sizePolicy6);
        disp_iteration_total->setReadOnly(true);

        horizontalLayout->addWidget(disp_iteration_total);


        formLayout->setWidget(0, QFormLayout::SpanningRole, groupBox);

        groupBox_2 = new QGroupBox(displayingBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        disp_time_curr = new QLineEdit(groupBox_2);
        disp_time_curr->setObjectName(QString::fromUtf8("disp_time_curr"));

        horizontalLayout_2->addWidget(disp_time_curr);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        disp_time_total = new QLineEdit(groupBox_2);
        disp_time_total->setObjectName(QString::fromUtf8("disp_time_total"));

        horizontalLayout_2->addWidget(disp_time_total);


        formLayout->setWidget(1, QFormLayout::SpanningRole, groupBox_2);


        gridLayout->addWidget(displayingBox, 0, 5, 1, 1);

        qthyenaClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qthyenaClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 982, 27));
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
        calculatingBox->setTitle(QApplication::translate("qthyenaClass", "Calculating", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("qthyenaClass", "Percent Calculated:", 0, QApplication::UnicodeUTF8));
        statsBox->setTitle(QApplication::translate("qthyenaClass", "Statistics", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("qthyenaClass", "Trials:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("qthyenaClass", "of", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("qthyenaClass", "Iterations:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("qthyenaClass", "of", 0, QApplication::UnicodeUTF8));
        beginButton->setText(QApplication::translate("qthyenaClass", "Begin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        displayingBox->setTitle(QApplication::translate("qthyenaClass", "Displaying", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("qthyenaClass", "Percent Displayed", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("qthyenaClass", "Iteration", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("qthyenaClass", "of", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("qthyenaClass", "Time Step", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("qthyenaClass", "of", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qthyenaClass: public Ui_qthyenaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHYENA_H
