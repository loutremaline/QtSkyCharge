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
        ui->centralwidget->layout()->addWidget(slot1);

        if (    chargerInfo.coreType == "100089" || chargerInfo.coreType == "100097" ||
                chargerInfo.coreType == "100123" || chargerInfo.coreType == "100131" ||
                chargerInfo.coreType == "100125" || chargerInfo.coreType == "100157")
        {
            slot2 = new ChargeSlot(ui->centralwidget, 1);
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
