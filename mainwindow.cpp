//
// Created by Alexandre Beaulieu on 2024-08-28.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include <QDebug>

using namespace InventoryConstants;

mainWindow::mainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::mainWindow),
        database(std::make_unique<DBController>()) {
    ui->setupUi(this);
    setWindowTitle("Lumina Inventory System");
    ui->statusbar->showMessage("Disconnected");
    ui->checkinButton->setEnabled(false);
    ui->checkoutButton->setEnabled(false);
    connectZoneCheckboxes();
}

mainWindow::~mainWindow() {
    delete ui;
}

void mainWindow::connectZoneCheckboxes() {
    for (const auto &zone : ZONES) {
        auto *cb = findChild<QCheckBox *>(zone.widgetName);
        if (!cb) continue;
        int idx = zone.index;
        connect(cb, &QCheckBox::toggled, this, [this, idx](bool checked) {
            m_zoneSelected[idx] = checked;
        });
    }
}

void mainWindow::on_actionConnect_triggered() {
    if (login) return;

    login = new loginwindow(nullptr);
    connect(this, &mainWindow::SendDb, login, &loginwindow::receiveDB);
    connect(login, &loginwindow::loginClosed, this, &mainWindow::on_loginClosed);
    emit SendDb(database.get());
    login->show();
}

void mainWindow::on_loginClosed() {
    disconnect(this, &mainWindow::SendDb, login, &loginwindow::receiveDB);
    disconnect(login, &loginwindow::loginClosed, this, &mainWindow::on_loginClosed);
    qDebug() << "Login window closed";
    login->deleteLater();
    login = nullptr;

    if (database->connected()) {
        ui->statusbar->showMessage("Connected");
        ui->checkinButton->setEnabled(true);
        ui->checkoutButton->setEnabled(true);
        setWindowTitle("Lumina Inventory System - Connected");
    }
}

void mainWindow::on_zone10_toggled(bool checked) {
    for (const auto &zone : ZONES) {
        if (auto *cb = findChild<QCheckBox *>(zone.widgetName)) {
            cb->setChecked(checked);
        }
    }
}

void mainWindow::on_checkinButton_clicked() {
    if (!database->connected()) {
        ui->statusbar->showMessage("Error: Not connected to database");
        return;
    }

    for (const auto &zone : ZONES) {
        if (!m_zoneSelected[zone.index]) continue;

        database->prepareStatement(SQL_CHECKIN_CLEAR);
        database->prepareBind({zone.dbValue});
        database->executeStatement();

        database->prepareStatement(SQL_CHECKIN_STATUS);
        database->prepareBind({zone.dbValue});
        database->executeStatement();
    }

    ui->statusbar->showMessage("Check-in completed", 5000);
}

void mainWindow::on_checkoutButton_clicked() {
    if (!database->connected()) {
        ui->statusbar->showMessage("Error: Not connected to database");
        return;
    }

    bool first = true;
    for (const auto &zone : ZONES) {
        if (!m_zoneSelected[zone.index]) continue;

        std::string locId = std::to_string(zone.locationId);

        database->prepareStatement(SQL_CHECKOUT_ASSIGN);
        database->prepareBind({locId, locId, zone.dbValue});
        database->executeStatement();

        database->prepareStatement(SQL_CHECKOUT_STATUS);
        database->prepareBind({zone.dbValue});
        database->executeStatement();

        // Workaround: first zone checkout must execute twice due to a known bug
        // where the first prepared statement execution doesn't take effect
        if (first) {
            database->prepareStatement(SQL_CHECKOUT_ASSIGN);
            database->prepareBind({locId, locId, zone.dbValue});
            database->executeStatement();

            database->prepareStatement(SQL_CHECKOUT_STATUS);
            database->prepareBind({zone.dbValue});
            database->executeStatement();
        }
        first = false;
    }

    ui->statusbar->showMessage("Check-out completed", 5000);
}
