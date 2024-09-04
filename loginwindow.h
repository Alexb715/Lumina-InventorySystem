//
// Created by Alexandre Beaulieu on 2024-08-28.
//

#ifndef INVENTORYSYSTEM_LOGINWINDOW_H
#define INVENTORYSYSTEM_LOGINWINDOW_H

#include <QWidget>
#include "DatabaseController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class loginwindow; }
QT_END_NAMESPACE

class loginwindow : public QWidget {
Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);

    ~loginwindow() override;

private:
    Ui::loginwindow *ui;
    DBController* DB;
    void delay(float n);
public slots:
    void receiveDB(DBController* DB);
private slots:
    void on_connectButton_clicked();
    void on_cancelButton_clicked();
signals:
    void loginClosed();
};


#endif //INVENTORYSYSTEM_LOGINWINDOW_H
