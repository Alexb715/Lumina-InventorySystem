#include <QApplication>
#include <QPushButton>
#include "DatabaseController.h"
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
