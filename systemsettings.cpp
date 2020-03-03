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
#include "systemsettings.h"
#include "ui_systemsettings.h"
#include "chargerDevice.h"

SystemSettings::SystemSettings(QWidget *parent, unsigned char slot) :
    QDialog(parent),
    ui(new Ui::SystemSettings)
{
    ui->setupUi(this);
    m_slot = slot;
    connect(&m_initTimer, SIGNAL(timeout()), this, SLOT(initTimer_timeout()));
    m_initTimer.start(1000);
}

SystemSettings::~SystemSettings()
{
    m_initTimer.stop();
    delete ui;
}

void SystemSettings::on_chkTimeCut_stateChanged(int state)
{
    ui->spnTimeLimit->setEnabled(state);
}

void SystemSettings::on_chkCapacityCut_stateChanged(int state)
{
    ui->spnCapacityLimit->setEnabled(state);
}

void SystemSettings::on_chkTempCut_stateChanged(int state)
{
    ui->spnTempLimit->setEnabled(state);
}

void SystemSettings::initTimer_timeout()
{
    try
    {
        ChargerDevice charger;
        m_sysInfo = charger.getSystemInfo(m_slot);

        ui->chkSystemBuzzer->setChecked(m_sysInfo.buzzer);
        ui->chkKeyBuzzer->setChecked(m_sysInfo.keyBeep);
        ui->chkTimeCut->setChecked(m_sysInfo.timeCut);
        ui->spnTimeLimit->setValue(m_sysInfo.timeLimit);
        ui->chkCapacityCut->setChecked(m_sysInfo.capacityCut);
        ui->spnCapacityLimit->setValue(m_sysInfo.capacityLimit);
        ui->chkTempCut->setChecked(m_sysInfo.tempCut);
        ui->spnTempLimit->setValue(m_sysInfo.tempLimit);
        ui->spnDPNiCd->setValue(m_sysInfo.sensitivityNiCd);
        ui->spnDPNiMH->setValue(m_sysInfo.sensitivityNiMH);

        m_initTimer.stop();
        ui->lblMessage->clear();
        ui->btnSave->setEnabled(true);

    } catch (HidException hidex) {
        // Nothing to do, retry in 1s.
    }
}


void SystemSettings::on_btnSave_clicked()
{
    m_sysInfo.buzzer = ui->chkSystemBuzzer->isChecked();
    m_sysInfo.keyBeep = ui->chkKeyBuzzer->isChecked();
    m_sysInfo.timeCut = ui->chkTimeCut->isChecked();
    m_sysInfo.timeLimit = ui->spnTimeLimit->value();
    m_sysInfo.capacityCut = ui->chkCapacityCut->isChecked();
    m_sysInfo.capacityLimit = ui->spnCapacityLimit->value();
    m_sysInfo.tempCut = ui->chkTempCut->isChecked();
    m_sysInfo.tempLimit = ui->spnTempLimit->value();
    m_sysInfo.sensitivityNiCd = ui->spnDPNiCd->value();
    m_sysInfo.sensitivityNiMH = ui->spnDPNiMH->value();

    try {
        ChargerDevice charger;
        charger.saveSystemInfo(m_slot, &m_sysInfo);
        ui->lblMessage->setText(tr("Saved"));

    } catch (HidException hidex) {
        ui->lblMessage->setText(tr("Error :("));
    }
}
