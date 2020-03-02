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
#ifndef CHARGESLOT_H
#define CHARGESLOT_H

#include <QWidget>
#include <QtCharts>
#include "chargeInfo.h"

namespace Ui {
    class ChargeSlot;
}

class ChargeSlot : public QWidget
{
    Q_OBJECT

public:
    explicit ChargeSlot(QWidget *parent = nullptr, unsigned char slotNumber = 0);
    ~ChargeSlot();

private slots:
    void on_btnSurveiller_clicked();
    void on_btnSettings_clicked();
    void on_chkVoltage_stateChanged(int newState);
    void on_chkCurrent_stateChanged(int newState);
    void on_chkCapacity_stateChanged(int newState);
    void on_chkTemperature_stateChanged(int newState);
    void on_lstBatteryType_currentIndexChanged(int index);
    void on_btnStart_clicked();
    void on_sldCells_valueChanged(int value);
    void on_lstChargingMode_currentIndexChanged(int index);
    void monitoringTimer_timeout();
    void delayStartMonitorTimer_timeout();


private:
    Ui::ChargeSlot *ui;

    QChart chart1;
    QLineSeries serieVoltage, serieTemperature, serieCapacity, serieCurrent;
    QValueAxis axisTime, axisVoltage, axisTemperature, axisCapacity, axisCurrent;

    QTimer monitoringTimer, delayStartMonitorTimer;

    unsigned char m_slotNumber;
    bool isMonitoring = false;
    bool isStarting = true;
    qreal minTime, maxTime, minVoltage, maxVoltage, minTemp, maxTemp, minCapacity, maxCapacity, minCurrent, maxCurrent;

    void refreshCurrentActionInfo(ChargeInfo info);
    void showHideSerie(int newState, QLineSeries *serie, QValueAxis *yAxis, Qt::AlignmentFlag align);
    void startMonitoring();
    void stopMonitoring();
    void freezeUnfreezeCommand();

};

#endif // CHARGESLOT_H
