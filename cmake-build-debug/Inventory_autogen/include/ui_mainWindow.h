/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QAction *actionConnect;
    QWidget *centralwidget;
    QPushButton *checkinButton;
    QPushButton *checkoutButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *zone8;
    QCheckBox *zone3;
    QCheckBox *zone2;
    QCheckBox *zone5;
    QCheckBox *zone6;
    QCheckBox *zone4;
    QCheckBox *zone7;
    QCheckBox *zone9;
    QCheckBox *zone1;
    QCheckBox *zone0;
    QCheckBox *zone10;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(600, 500);
        actionConnect = new QAction(mainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        checkinButton = new QPushButton(centralwidget);
        checkinButton->setObjectName(QString::fromUtf8("checkinButton"));
        checkinButton->setGeometry(QRect(50, 360, 200, 32));
        checkoutButton = new QPushButton(centralwidget);
        checkoutButton->setObjectName(QString::fromUtf8("checkoutButton"));
        checkoutButton->setGeometry(QRect(350, 360, 200, 32));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 591, 251));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        zone8 = new QCheckBox(gridLayoutWidget);
        zone8->setObjectName(QString::fromUtf8("zone8"));

        gridLayout->addWidget(zone8, 2, 1, 1, 1);

        zone3 = new QCheckBox(gridLayoutWidget);
        zone3->setObjectName(QString::fromUtf8("zone3"));

        gridLayout->addWidget(zone3, 0, 2, 1, 1);

        zone2 = new QCheckBox(gridLayoutWidget);
        zone2->setObjectName(QString::fromUtf8("zone2"));

        gridLayout->addWidget(zone2, 0, 1, 1, 1);

        zone5 = new QCheckBox(gridLayoutWidget);
        zone5->setObjectName(QString::fromUtf8("zone5"));

        gridLayout->addWidget(zone5, 1, 1, 1, 1);

        zone6 = new QCheckBox(gridLayoutWidget);
        zone6->setObjectName(QString::fromUtf8("zone6"));

        gridLayout->addWidget(zone6, 1, 2, 1, 1);

        zone4 = new QCheckBox(gridLayoutWidget);
        zone4->setObjectName(QString::fromUtf8("zone4"));

        gridLayout->addWidget(zone4, 1, 0, 1, 1);

        zone7 = new QCheckBox(gridLayoutWidget);
        zone7->setObjectName(QString::fromUtf8("zone7"));

        gridLayout->addWidget(zone7, 2, 0, 1, 1);

        zone9 = new QCheckBox(gridLayoutWidget);
        zone9->setObjectName(QString::fromUtf8("zone9"));

        gridLayout->addWidget(zone9, 2, 2, 1, 1);

        zone1 = new QCheckBox(gridLayoutWidget);
        zone1->setObjectName(QString::fromUtf8("zone1"));

        gridLayout->addWidget(zone1, 0, 0, 1, 1);

        zone0 = new QCheckBox(gridLayoutWidget);
        zone0->setObjectName(QString::fromUtf8("zone0"));

        gridLayout->addWidget(zone0, 3, 0, 1, 1);

        zone10 = new QCheckBox(centralwidget);
        zone10->setObjectName(QString::fromUtf8("zone10"));
        zone10->setGeometry(QRect(0, 270, 85, 20));
        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 24));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(zone1, zone2);
        QWidget::setTabOrder(zone2, zone3);
        QWidget::setTabOrder(zone3, zone4);
        QWidget::setTabOrder(zone4, zone5);
        QWidget::setTabOrder(zone5, zone6);
        QWidget::setTabOrder(zone6, zone7);
        QWidget::setTabOrder(zone7, zone8);
        QWidget::setTabOrder(zone8, zone9);
        QWidget::setTabOrder(zone9, zone10);
        QWidget::setTabOrder(zone10, checkinButton);
        QWidget::setTabOrder(checkinButton, checkoutButton);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionConnect);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "Inventory Control System", nullptr));
        actionConnect->setText(QCoreApplication::translate("mainWindow", "Connect To Database", nullptr));
        checkinButton->setText(QCoreApplication::translate("mainWindow", "CheckIn", nullptr));
        checkoutButton->setText(QCoreApplication::translate("mainWindow", "CheckOut", nullptr));
        zone8->setText(QCoreApplication::translate("mainWindow", "Zone8", nullptr));
        zone3->setText(QCoreApplication::translate("mainWindow", "Zone3", nullptr));
        zone2->setText(QCoreApplication::translate("mainWindow", "Zone2", nullptr));
        zone5->setText(QCoreApplication::translate("mainWindow", "Zone5", nullptr));
        zone6->setText(QCoreApplication::translate("mainWindow", "Zone6", nullptr));
        zone4->setText(QCoreApplication::translate("mainWindow", "Zone4", nullptr));
        zone7->setText(QCoreApplication::translate("mainWindow", "Zone7", nullptr));
        zone9->setText(QCoreApplication::translate("mainWindow", "Zone9", nullptr));
        zone1->setText(QCoreApplication::translate("mainWindow", "Zone1", nullptr));
        zone0->setText(QCoreApplication::translate("mainWindow", "Zone0", nullptr));
        zone10->setText(QCoreApplication::translate("mainWindow", "All Zones", nullptr));
        menuFile->setTitle(QCoreApplication::translate("mainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
