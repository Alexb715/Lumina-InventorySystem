//
// Created by Alexandre Beaulieu on 2024-08-28.
//

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "constants.h"
#include <QTimer>
#include <QDebug>

loginwindow::loginwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::loginwindow) {
    ui->setupUi(this);
    ui->usernameLine->setFocus();
}

loginwindow::~loginwindow() {
    delete ui;
}

void loginwindow::receiveDB(DBController *DataB) {
    this->DB = DataB;
}

void loginwindow::on_connectButton_clicked() {
    const auto username = ui->usernameLine->text().toStdString();
    const auto password = ui->passwordLine->text().toStdString();
    const auto ip = ui->urlLine->text().toStdString();

    if (DB->connect(ip, username, password, InventoryConstants::DEFAULT_DATABASE_NAME)) {
        ui->statusLabel->setText("Connected successfully");
        ui->statusLabel->setStyleSheet("color: #a6e3a1;");
        ui->connectButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);

        QTimer::singleShot(1500, this, [this]() {
            emit loginClosed();
            this->close();
        });
    } else {
        ui->statusLabel->setText("Incorrect credentials. Please try again.");
        ui->statusLabel->setStyleSheet("color: #f38ba8;");
    }
}

void loginwindow::on_cancelButton_clicked() {
    emit loginClosed();
    this->close();
}
