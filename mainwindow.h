//
// Created by Alexandre Beaulieu on 2024-08-28.
//

#ifndef INVENTORYSYSTEM_MAINWINDOW_H
#define INVENTORYSYSTEM_MAINWINDOW_H

#include <QMainWindow>
#include <array>
#include <memory>
#include "DatabaseController.h"
#include "loginwindow.h"
#include "updatechecker.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow() override;

private:
    std::array<bool, InventoryConstants::ZONE_COUNT> m_zoneSelected{};
    Ui::mainWindow *ui;
    loginwindow *login = nullptr;
    std::unique_ptr<DBController> database;
    UpdateChecker m_updateChecker;
    QString m_updateUrl;

    void connectZoneCheckboxes();

private slots:
    void on_actionConnect_triggered();
    void on_zone10_toggled(bool checked);
    void on_checkinButton_clicked();
    void on_checkoutButton_clicked();

public slots:
    void on_loginClosed();

signals:
    void SendDb(DBController *DB);
};

#endif //INVENTORYSYSTEM_MAINWINDOW_H
