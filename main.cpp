#include <QApplication>
#include <QFile>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/lumina_256.png"));

    QFile styleFile(":/styles/dark_theme.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        a.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    mainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
