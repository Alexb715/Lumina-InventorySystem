//
// Created by Alexandre Beaulieu on 2024-08-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_loginwindow.h" resolved

#include <QTime>
#include "loginwindow.h"
#include "ui_loginwindow.h"

//initial setup
loginwindow::loginwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::loginwindow) {
    ui->setupUi(this);
    ui->usernameLine->setFocus();

}
//destructor
loginwindow::~loginwindow() {
    delete ui;

}
//receives pointer to database object
void loginwindow::receiveDB(DBController* DataB) {
    this->DB = DataB;
}
//logins after buttons is clicked
void loginwindow::on_connectButton_clicked() {
    std::string username, password, ip;
    //turns text into string for login
    username = ui->usernameLine->text().toStdString();
    password = ui->passwordLine->text().toStdString();
    ip = ui->urlLine->text().toStdString();
    //if connects successfully waits 1.5 seconds and sends signal that the window is closed for proper deletion in MainWindow function
    if(DB->connect(ip,username,password,"snipeit_db")){
        ui->statusLabel->setText("Connected Successfully");
        delay(1.5);
        emit loginClosed();
        this->close();
    } else{
        //teels user incorrect Inputs
        ui->statusLabel->setText("Incorrect Credentials. Please Try Again");
    }
}

//fonction to pause thing while still allowing ui updates
void loginwindow::delay(float n) {
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}
//if canceled tells main windows that this window is closed
void loginwindow::on_cancelButton_clicked() {
    emit loginClosed();
    this->close();

}


