#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QTranslator translator;
    QString localCode = QLocale::system().name().left(2);
    if (localCode == "fr") {
        translator.load(localCode.prepend("QtSkyCharge_"));
        application.installTranslator(&translator);
    }

    MainWindow window;
    window.show();
    return application.exec();
}
