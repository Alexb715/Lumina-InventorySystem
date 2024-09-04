//
// Created by Alexandre Beaulieu on 2024-08-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_loginwindow.h" resolved

#include <QTime>
#include "loginwindow.h"
#include "ui_loginwindow.h"


loginwindow::loginwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::loginwindow) {
    ui->setupUi(this);
    ui->usernameLine->setFocus();

}

loginwindow::~loginwindow() {
    delete ui;

}

void loginwindow::receiveDB(DBController* DataB) {
    this->DB = DataB;
}

void loginwindow::on_connectButton_clicked() {
    std::string username, password, ip;
    username = ui->usernameLine->text().toStdString();
    password = ui->passwordLine->text().toStdString();
    ip = ui->urlLine->text().toStdString();
    if(DB->connect(ip,username,password,"snipeit_db")){
        ui->statusLabel->setText("Connected Successfully");
        delay(1.5);
        emit loginClosed();
        this->close();
    } else{
        ui->statusLabel->setText("Incorrect Credentials. Please Try Again");
    }
}

void loginwindow::delay(float n) {
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

void loginwindow::on_cancelButton_clicked() {
    emit loginClosed();
    this->close();

}


