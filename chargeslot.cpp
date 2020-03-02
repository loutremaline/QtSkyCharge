#include "const.h"
#include "chargeslot.h"
#include "ui_chargeslot.h"
#include "chargerDevice.h"
#include "systemsettings.h"


ChargeSlot::ChargeSlot(QWidget *parent, unsigned char slotNumber) : QWidget(parent), ui(new Ui::ChargeSlot)
{
    ui->setupUi(this);

    m_slotNumber = slotNumber;
    ui->lblMessage->hide();

    delayStartMonitorTimer.setSingleShot(true);
    delayStartMonitorTimer.setInterval(2000);
    connect(&monitoringTimer, SIGNAL(timeout()), this, SLOT(monitoringTimer_timeout()));
    connect(&delayStartMonitorTimer, SIGNAL(timeout()), this, SLOT(delayStartMonitorTimer_timeout()));

    for (int i = BatteryType::LiPo; i <= BatteryType::NiCd; i++)
    {
        ui->lstBatteryType->addItem(batteryTypesLabel[i], i);
    }

    on_sldCells_valueChanged(1);

    chart1.createDefaultAxes();
    chart1.setTitle(m_slotNumber == 0 ? tr("Charge on slot A") : tr("Charge on slot B"));
    ui->chartView1->setChart(&chart1);

    axisTime.setTitleText(tr("min"));
    axisTime.setLabelFormat("%i");
    chart1.addAxis(&axisTime, Qt::AlignBottom);

    chart1.addSeries(&serieVoltage);
    chart1.addSeries(&serieCurrent);
    chart1.addSeries(&serieTemperature);
    chart1.addSeries(&serieCapacity);

    axisVoltage.setTitleText(tr("V"));
    axisVoltage.setLinePen(serieVoltage.pen().color());
    chart1.addAxis(&axisVoltage, Qt::AlignLeft);

    axisCurrent.setTitleText(tr("mA"));
    axisCurrent.setLinePen(serieCurrent.pen().color());
    chart1.addAxis(&axisCurrent, Qt::AlignRight);

    axisTemperature.setTitleText(tr("°C"));
    axisTemperature.setLinePen(serieTemperature.pen().color());
    axisTemperature.setLabelFormat("%i");
    chart1.addAxis(&axisTemperature, Qt::AlignLeft);

    axisCapacity.setTitleText(tr("mAh"));
    axisCapacity.setLinePen(serieCapacity.pen().color());
    axisCapacity.setLabelFormat("%i");
    chart1.addAxis(&axisCapacity, Qt::AlignRight);

    serieVoltage.setName(tr("Voltage"));
    serieVoltage.attachAxis(&axisTime);
    serieVoltage.attachAxis(&axisVoltage);

    serieTemperature.setName(tr("Temperature"));
    serieTemperature.attachAxis(&axisTime);
    serieTemperature.attachAxis(&axisTemperature);

    serieCapacity.setName(tr("Capacity"));
    serieCapacity.attachAxis(&axisTime);
    serieCapacity.attachAxis(&axisCapacity);

    serieCurrent.setName(tr("Current"));
    serieCurrent.attachAxis(&axisTime);
    serieCurrent.attachAxis(&axisCurrent);
}

ChargeSlot::~ChargeSlot()
{
    delete ui;
}




void ChargeSlot::on_btnSurveiller_clicked()
{
    ui->lblMessage->hide();

    if (isMonitoring)
    {
        stopMonitoring();
    }
    else
    {
        startMonitoring();
    }
}

void ChargeSlot::on_btnStart_clicked()
{
    ChargeAction action;
    ChargerDevice chargerDevice;

    ui->lblMessage->hide();

    try {
        if (isMonitoring)
        {
            chargerDevice.stop(m_slotNumber);
        }
        else
        {
            action.type = (BatteryType)ui->lstBatteryType->currentData().value<unsigned char>();
            action.mode = ui->lstChargingMode->currentData().value<unsigned char>();
            action.cells = ui->sldCells->value();
            action.chargeCurrent = static_cast<unsigned short int>(ui->spnChargeCurrent->value() * 1000.0);
            action.dischargeCurrent = static_cast<unsigned short int>(ui->spnDischargeCurrent->value() * 1000.0);

            if (action.type == BatteryType::Pb) {
                ui->lblMessage->show();
                ui->lblMessage->setText(tr("Pb battery not implemented :("));
                return;
            }

            chargerDevice.start(m_slotNumber, &action);

            delayStartMonitorTimer.start();
        }

    } catch (HidException & hidex) {
        ui->lblMessage->show();
        ui->lblMessage->setText(hidex.message());
    }
}

void ChargeSlot::on_btnSettings_clicked()
{
    ui->lblMessage->hide();

    SystemSettings systemSettings(this, m_slotNumber);
    systemSettings.exec();
}


void ChargeSlot::delayStartMonitorTimer_timeout()
{
    startMonitoring();
}

void ChargeSlot::monitoringTimer_timeout()
{
    ChargerDevice chargerDevice;
    ChargeInfo chargeInfo;

    try {
        chargeInfo = chargerDevice.getChargeInfo(m_slotNumber);

    } catch (HidException & hidex) {
        ui->lblMessage->show();
        ui->lblMessage->setText(hidex.message());
        stopMonitoring();
        return;
    }

    if (isStarting)
    {
        refreshCurrentActionInfo(chargeInfo);
    }

    qreal time = chargeInfo.time / 60.0;
    qreal voltage = chargeInfo.voltage / 1000.0;
    qreal current = chargeInfo.current;
    qreal temperature = chargeInfo.temperature;
    qreal capacity = chargeInfo.capacity;

    bool change = false;
    if (minTime > time) { minTime = time; change = true; }
    if (maxTime < time) { maxTime = time; change = true; }
    if (minVoltage > voltage) { minVoltage = voltage; change = true; }
    if (maxVoltage < voltage) { maxVoltage = voltage; change = true; }
    if (minCurrent > current) { minCurrent = current; change = true; }
    if (maxCurrent < current) { maxCurrent = current; change = true; }
    if (minTemp > temperature) { minTemp = temperature; change = true; }
    if (maxTemp < temperature) { maxTemp = temperature; change = true; }
    if (minCapacity > capacity) { minCapacity = capacity; change = true; }
    if (maxCapacity < capacity) { maxCapacity = capacity; change = true; }

    if (change) {
        qreal maxAxisVoltage = ceil(maxVoltage * 10.0) / 10.0;
        qreal minAxisVoltage = floor(minVoltage * 10.0) / 10.0;
        axisVoltage.setRange(minAxisVoltage, maxAxisVoltage);

        qreal maxAxisCurrent = ceil(maxCurrent * 1.02);
        qreal minAxisCurrent = floor(minCurrent * 0.98);
        axisCurrent.setRange(minAxisCurrent, maxAxisCurrent);

        qreal maxAxisTime = ceil(maxTime);
        axisTime.setRange(minTime, maxAxisTime);

        qreal maxAxisTemp = ceil(maxTemp) + 2;
        qreal minAxisTemp = floor(minTemp) - 2;
        axisTemperature.setRange(minAxisTemp, maxAxisTemp);

        qreal maxAxisCapacity = ceil(maxCapacity / 10.0) * 10.0;
        axisCapacity.setRange(minCapacity, maxAxisCapacity);
    }

    serieVoltage.append(time, voltage);
    serieTemperature.append(time, temperature);
    serieCapacity.append(time, capacity);
    serieCurrent.append(time, current);

    if (chargeInfo.battery_type == BatteryType::LiPo || chargeInfo.battery_type == BatteryType::LiHV || chargeInfo.battery_type == BatteryType::LiFe || chargeInfo.battery_type == BatteryType::LiIo)
    {
        ui->lblCell1->setText(QString().sprintf(" %.2f", chargeInfo.vCell[0] / 1000.0).prepend(tr("Cell %i:").arg(1)).append(tr("V")));
        ui->lblCell2->setText(QString().sprintf(" %.2f", chargeInfo.vCell[1] / 1000.0).prepend(tr("Cell %i:").arg(2)).append(tr("V")));
        ui->lblCell3->setText(QString().sprintf(" %.2f", chargeInfo.vCell[2] / 1000.0).prepend(tr("Cell %i:").arg(3)).append(tr("V")));
        ui->lblCell4->setText(QString().sprintf(" %.2f", chargeInfo.vCell[3] / 1000.0).prepend(tr("Cell %i:").arg(4)).append(tr("V")));
        ui->lblCell5->setText(QString().sprintf(" %.2f", chargeInfo.vCell[4] / 1000.0).prepend(tr("Cell %i:").arg(5)).append(tr("V")));
        ui->lblCell6->setText(QString().sprintf(" %.2f", chargeInfo.vCell[5] / 1000.0).prepend(tr("Cell %i:").arg(6)).append(tr("V")));
    }

    ui->lblCurTime->setText(QString().sprintf(" %02u:%02u:%02u", chargeInfo.time / 3600, chargeInfo.time / 60 % 60, chargeInfo.time % 60).prepend(tr("Time:")));
    ui->lblCurVoltage->setText(QString().sprintf(" %.2f", voltage).prepend(tr("Voltage:")).append(tr("V")));
    ui->lblCurCurrent->setText(QString().sprintf(" %.3f", current / 1000.0).prepend(tr("Current :")).append(tr("A")));
    ui->lblCurCapacity->setText(tr("Capacity:").append(" %1").arg(chargeInfo.capacity).append(tr("mAh")));
    ui->lblCurTemp->setText(QString(tr("Temperature : %1°C").arg(chargeInfo.temperature)));


    QString statusStr(tr("Status:").append(" "));
    switch (chargeInfo.state) {
    case ChargeState::IDLE:
        statusStr.append(tr("Idle"));
        if (!isStarting) stopMonitoring();
        break;
    case ChargeState::CHARGING:
        statusStr.append(tr("Charging"));
        break;
    case ChargeState::DISCHARGING:
        statusStr.append(tr("Discharging"));
        break;
    case ChargeState::FINISH:
        statusStr.append(tr("Finish"));
        if (!isStarting) stopMonitoring();
        break;
    default:
        statusStr.append(QString(tr("Unknown (%1)").arg((int)chargeInfo.state)));
    }
    ui->lblStatus->setText(statusStr);

    if (isStarting) isStarting = false;
}



void ChargeSlot::on_chkVoltage_stateChanged(int newState)
{
    showHideSerie(newState, &serieVoltage, &axisVoltage, Qt::AlignLeft);
}

void ChargeSlot::on_chkCurrent_stateChanged(int newState)
{
    showHideSerie(newState, &serieCurrent, &axisCurrent, Qt::AlignRight);
}

void ChargeSlot::on_chkCapacity_stateChanged(int newState)
{
    showHideSerie(newState, &serieCapacity, &axisCapacity, Qt::AlignRight);
}

void ChargeSlot::on_chkTemperature_stateChanged(int newState)
{
    showHideSerie(newState, &serieTemperature, &axisTemperature, Qt::AlignLeft);
}

void ChargeSlot::on_lstBatteryType_currentIndexChanged(int newValue)
{
    ui->lstChargingMode->clear();

    BatteryType selectedBatteryType = (BatteryType) newValue;

    switch (selectedBatteryType) {

    case LiFe:
    case LiIo:
    case LiHV:
    case LiPo:
        for (int i = ModeLi::LiCharge; i <= ModeLi::LiBalance; i++) ui->lstChargingMode->addItem(modeLiLabel[i], i);
        ui->lblCells->show();
        ui->lblNCells->show();
        ui->sldCells->show();
        ui->lblCell1->show();
        break;

    case NiMH:
    case NiCd:
        ui->lblCells->hide();
        ui->sldCells->hide();
        ui->lblNCells->hide();
        ui->sldCells->setValue(1);
        ui->lblCell1->hide();
        for (int i = ModeNi::NiCharge; i <= ModeNi::NiCycle; i++) ui->lstChargingMode->addItem(modeNiLabel[i], i);
        break;
    case Pb:
        break;
    }

}

void ChargeSlot::on_sldCells_valueChanged(int value)
{
    QString txt;
    txt.sprintf("%i", value);
    ui->lblNCells->setText(txt);

    if (value > 1) ui->lblCell2->show(); else ui->lblCell2->hide();
    if (value > 2) ui->lblCell3->show(); else ui->lblCell3->hide();
    if (value > 3) ui->lblCell4->show(); else ui->lblCell4->hide();
    if (value > 4) ui->lblCell5->show(); else ui->lblCell5->hide();
    if (value > 5) ui->lblCell6->show(); else ui->lblCell6->hide();
}

void ChargeSlot::on_lstChargingMode_currentIndexChanged(int index)
{
    int batteryType = ui->lstBatteryType->currentData().value<int>();

    if ((batteryType <= 0x03 && index != (int)ModeLi::LiDischarge) || ((batteryType == 0x04 || batteryType == 0x05) && index != (int)ModeNi::NiDischarge)) {
        ui->lblChargeCurrent->show();
        ui->spnChargeCurrent->show();
    } else {
        ui->lblChargeCurrent->hide();
        ui->spnChargeCurrent->hide();
    }

    if ((batteryType <= 0x03 && index == (int)ModeLi::LiDischarge) || ((batteryType == 0x04 || batteryType == 0x05) && (index >= 0x02))) {
        ui->lblDischargeCurrent->show();
        ui->spnDischargeCurrent->show();
    } else {
        ui->lblDischargeCurrent->hide();
        ui->spnDischargeCurrent->hide();
    }

}



void ChargeSlot::freezeUnfreezeCommand()
{
    ui->lstBatteryType->setEnabled(!isMonitoring);
    ui->lstChargingMode->setEnabled(!isMonitoring);
    ui->sldCells->setEnabled(!isMonitoring);
    ui->spnChargeCurrent->setEnabled(!isMonitoring);
    ui->btnSettings->setEnabled(!isMonitoring);

    if (isMonitoring) {
        ui->btnStart->setText(tr("Stop"));
    } else {
        ui->btnStart->setText(tr("Start"));
    }
}

void ChargeSlot::startMonitoring()
{
    if (!isMonitoring)
    {
        minTime = minVoltage = minTemp = minCapacity = minCurrent = std::numeric_limits<qreal>::max();
        maxTime = maxVoltage = maxTemp = maxCapacity = maxCurrent = std::numeric_limits<qreal>::min();
        serieCurrent.clear();
        serieVoltage.clear();
        serieCapacity.clear();
        serieTemperature.clear();

        isMonitoring = true;
        freezeUnfreezeCommand();
        monitoringTimer.start(1000);
    }
}

void ChargeSlot::stopMonitoring()
{
    if (isMonitoring)
    {
        monitoringTimer.stop();
        isMonitoring = false;
        isStarting = true;
        freezeUnfreezeCommand();
    }
}

void ChargeSlot::showHideSerie(int newState, QLineSeries *serie, QValueAxis *yAxis, Qt::AlignmentFlag align)
{
    if (newState == Qt::Unchecked)
    {
        serie->detachAxis(yAxis);
        serie->detachAxis(&axisTime);
        chart1.removeAxis(yAxis);
        chart1.removeSeries(serie);
    }
    else if (newState == Qt::Checked)
    {
        chart1.addAxis(yAxis, align);
        chart1.addSeries(serie);
        serie->attachAxis(yAxis);
        serie->attachAxis(&axisTime);
    }
}

void ChargeSlot::refreshCurrentActionInfo(ChargeInfo info)
{
    ui->lstBatteryType->setCurrentIndex(info.battery_type);
    ui->lstChargingMode->setCurrentIndex(info.mode);

}
