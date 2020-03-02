/*
 * Copyright 2020 loutremaline79
 *
 * This file is part of QtSkyCharge.
 *
 *  QtSkyCharge is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>
 */
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
