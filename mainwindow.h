//
// Created by Alexandre Beaulieu on 2024-08-28.
//

#ifndef INVENTORYSYSTEM_MAINWINDOW_H
#define INVENTORYSYSTEM_MAINWINDOW_H

#include <QMainWindow>
#include "DatabaseController.h"
#include "loginwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE
class mainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);

    ~mainWindow() override;

private:
    bool zone0=false;
    bool zone1=false;
    bool zone2=false;
    bool zone3=false;
    bool zone4=false;
    bool zone5=false;
    bool zone6=false;
    bool zone7=false;
    bool zone8=false;
    bool zone9=false;
    int zone[11] = {0};
    Ui::mainWindow *ui;
    loginwindow* login;
    DBController* database= new DBController;
private slots:
    void on_zone0_toggled(bool checked);
    void on_actionConnect_triggered();
    void on_zone1_toggled(bool checked);
    void on_zone2_toggled(bool checked);
    void on_zone3_toggled(bool checked);
    void on_zone4_toggled(bool checked);
    void on_zone45_toggled(bool checked);
    void on_zone5_toggled(bool checked);
    void on_zone6_toggled(bool checked);
    void on_zone7_toggled(bool checked);
    void on_zone8_toggled(bool checked);
    void on_zone9_toggled(bool checked);
    void on_zone10_toggled(bool checked);
    void on_checkinButton_clicked();
    void on_checkoutButton_clicked();

public slots:
    void on_loginClosed();

signals:
    void SendDb(DBController * DB);
};


#endif //INVENTORYSYSTEM_MAINWINDOW_H
