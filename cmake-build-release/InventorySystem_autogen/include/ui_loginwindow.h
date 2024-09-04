/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginwindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *connectButton;
    QLineEdit *passwordLine;
    QLineEdit *usernameLine;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *urlLine;
    QLabel *label_2;
    QLabel *statusLabel;

    void setupUi(QWidget *loginwindow)
    {
        if (loginwindow->objectName().isEmpty())
            loginwindow->setObjectName(QString::fromUtf8("loginwindow"));
        loginwindow->resize(400, 300);
        horizontalLayoutWidget = new QWidget(loginwindow);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 230, 401, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        connectButton = new QPushButton(horizontalLayoutWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout->addWidget(connectButton);

        passwordLine = new QLineEdit(loginwindow);
        passwordLine->setObjectName(QString::fromUtf8("passwordLine"));
        passwordLine->setGeometry(QRect(100, 90, 200, 20));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(passwordLine->sizePolicy().hasHeightForWidth());
        passwordLine->setSizePolicy(sizePolicy);
        passwordLine->setEchoMode(QLineEdit::Password);
        usernameLine = new QLineEdit(loginwindow);
        usernameLine->setObjectName(QString::fromUtf8("usernameLine"));
        usernameLine->setGeometry(QRect(100, 30, 200, 20));
        label = new QLabel(loginwindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 150, 69, 21));
        label_3 = new QLabel(loginwindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 30, 69, 21));
        urlLine = new QLineEdit(loginwindow);
        urlLine->setObjectName(QString::fromUtf8("urlLine"));
        urlLine->setGeometry(QRect(100, 150, 200, 21));
        label_2 = new QLabel(loginwindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 90, 69, 21));
        statusLabel = new QLabel(loginwindow);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(40, 200, 311, 20));
        statusLabel->setAlignment(Qt::AlignCenter);
        QWidget::setTabOrder(usernameLine, passwordLine);
        QWidget::setTabOrder(passwordLine, urlLine);
        QWidget::setTabOrder(urlLine, cancelButton);
        QWidget::setTabOrder(cancelButton, connectButton);

        retranslateUi(loginwindow);

        QMetaObject::connectSlotsByName(loginwindow);
    } // setupUi

    void retranslateUi(QWidget *loginwindow)
    {
        loginwindow->setWindowTitle(QCoreApplication::translate("loginwindow", "Login", nullptr));
        cancelButton->setText(QCoreApplication::translate("loginwindow", "Cancel", nullptr));
        connectButton->setText(QCoreApplication::translate("loginwindow", "Connect", nullptr));
        label->setText(QCoreApplication::translate("loginwindow", "URL:", nullptr));
        label_3->setText(QCoreApplication::translate("loginwindow", "Username: ", nullptr));
        label_2->setText(QCoreApplication::translate("loginwindow", "Password: ", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginwindow: public Ui_loginwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
