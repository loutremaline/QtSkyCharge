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
#include "ui_mainwindow.h"
#include "chargerDevice.h"
#include "chargeslot.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&initTimer, SIGNAL(timeout()), this, SLOT(initTimer_timeout()));
    initTimer.start(750);
}

MainWindow::~MainWindow()
{
    delete ui;
    destroy(slot1);
    destroy(slot2);
}

void MainWindow::initTimer_timeout()
{
    try {
        ChargerDevice chargerDevice;
        ChargerInfo chargerInfo = chargerDevice.getDeviceInfo();

        QString qs;
        qs.sprintf(" %u.%02u", chargerInfo.softwareVersion[0], chargerInfo.softwareVersion[1]);
        ui->statusbar->showMessage(qs.prepend(tr("Software version:")));

        slot1 = new ChargeSlot(ui->centralwidget, 0);
        slot1->sizePolicy().setVerticalStretch(1);
        ui->centralwidget->layout()->addWidget(slot1);

        if (    chargerInfo.coreType == "100089" || chargerInfo.coreType == "100097" ||
                chargerInfo.coreType == "100123" || chargerInfo.coreType == "100131" ||
                chargerInfo.coreType == "100125" || chargerInfo.coreType == "100157")
        {
            slot2 = new ChargeSlot(ui->centralwidget, 1);
            slot2->sizePolicy().setVerticalStretch(1);
            ui->centralwidget->layout()->addWidget(slot2);
        }
        else
        {
            ui->statusbar->showMessage(tr("Be careful, QtSkyCharge not tested for this device."));
        }

        ui->lblMessage->hide();
        initTimer.stop();

    } catch (HidException hidex) {
        // Nothing todo.
    }
}
