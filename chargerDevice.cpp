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
#include "chargerDevice.h"


ChargerDevice::ChargerDevice() {}

ChargerDevice::~ChargerDevice()
{
    m_closeHidDevice();
}



ChargerInfo ChargerDevice::getDeviceInfo()
{
    m_ensureHidDeviceOpened();

    ChargerInfo ci;
    std::array<unsigned char, BUFFER_SIZE> raw_response = m_sendCommand(ChargerCommand::DEVICE_INFO, 0, nullptr);

    char tmpStr[6] = {(char)raw_response[5], (char)raw_response[6], (char)raw_response[7], (char)raw_response[8], (char)raw_response[9], (char)raw_response[10], };
    ci.coreType = std::string(tmpStr);
    ci.softwareVersion[0] = raw_response[16];
    ci.softwareVersion[1] = raw_response[17];
    ci.hardwareVersion = raw_response[18];

    return ci;
}

ChargeInfo ChargerDevice::getChargeInfo(unsigned char slot)
{
    m_ensureHidDeviceOpened();

    std::array<unsigned char, BUFFER_SIZE> raw_response = m_sendCommand(ChargerCommand::CHARGE_INFO, slot, nullptr);

    ChargeInfo info;
    info.command = (ChargerCommand)raw_response[0];
    info.slot = raw_response[1];
    info.battery_type = (BatteryType)raw_response[2];
    info.mode = raw_response[3];
    info.state = (ChargeState)raw_response[4];
    info.time = raw_response[5] * 256 + raw_response[6];
    info.voltage = raw_response[7] * 256 + raw_response[8];
    info.current = raw_response[9] * 256 + raw_response[10];
    info.capacity = raw_response[11] * 256 + raw_response[12];
    info.temperature = raw_response[14];

    for (int numCell = 0, index = 17; numCell < 6; numCell++)
    {
        info.vCell[numCell] = raw_response[index] * 256 + raw_response[index + 1];
        index += 2;
    }

    return  info;
}

SystemInfo ChargerDevice::getSystemInfo(unsigned char slot)
{
    m_ensureHidDeviceOpened();

    std::array<unsigned char, BUFFER_SIZE> raw_response = m_sendCommand(ChargerCommand::GET_SYS_INFO, slot, nullptr);

    SystemInfo sysInfo;
    sysInfo.keyBeep = raw_response[2];
    sysInfo.buzzer = raw_response[3];
    sysInfo.capacityCut = raw_response[4];
    sysInfo.timeCut = raw_response[5];
    sysInfo.temperatureUnit = raw_response[6];
    sysInfo.capacityLimit = raw_response[7] * 256 + raw_response[8];
    sysInfo.timeLimit = raw_response[9] * 256 + raw_response[10];
    sysInfo.tempLimit = raw_response[11];
    sysInfo.restTime = raw_response[12];
    sysInfo.dcInputLowCut = raw_response[13];
    sysInfo.sensitivityNiMH = raw_response[14];
    sysInfo.sensitivityNiCd = raw_response[15];
    sysInfo.acPower = raw_response[16];
    sysInfo.tempCut = raw_response[17];

    return sysInfo;
}

void ChargerDevice::saveSystemInfo(unsigned char slot, SystemInfo *sysInfo)
{
    m_ensureHidDeviceOpened();
    m_sendCommand(ChargerCommand::SET_SYS_INFO, slot, sysInfo);
}


void ChargerDevice::start(unsigned char slot, ChargeAction *action)
{
    m_ensureHidDeviceOpened();
    m_sendCommand(ChargerCommand::START, slot, action);
}

void ChargerDevice::stop(unsigned char slot)
{
    m_ensureHidDeviceOpened();
    m_sendCommand(ChargerCommand::STOP, slot, nullptr);
}

void ChargerDevice::m_ensureHidDeviceOpened()
{
    if (m_hidDevice == nullptr)
    {
        m_openHidDevice();
    }
}

void ChargerDevice::m_openHidDevice()
{
    int ret = hid_init();

    if (ret != 0)
    {
        throw HidException(ret, tr("Error initializing USB port."));
    }

    m_hidDevice = hid_open(VENDOR_ID, PRODUCT_ID, nullptr);
    if (m_hidDevice == nullptr)
    {
        throw HidException(-1, tr("Error Opening USB device charger."));
    }
}

void ChargerDevice::m_closeHidDevice()
{
    if (m_hidDevice != nullptr)
    {
        hid_close(m_hidDevice);
        m_hidDevice = nullptr;
    }

    hid_exit();
}

std::array<unsigned char, BUFFER_SIZE> ChargerDevice::m_sendCommand(ChargerCommand cmd, unsigned char slot, void *data)
{
    ChargeAction *action;
    SystemInfo *sysInfo;

    // Create raw request
    unsigned char request[BUFFER_SIZE] = {0};

    int index = 0;
    request[index++] = 0x00;
    request[index++] = 15;
    request[index++] = 0x00;
    request[index++] = cmd;
    request[index++] = 0x00;
    request[index++] = slot;

    switch (cmd) {

    case ChargerCommand::START:
        action = (ChargeAction *)data;
        request[index++] = action->type;
        request[index++] = action->cells;
        request[index++] = action->mode;
        request[index++] = action->chargeCurrent / 256;
        request[index++] = action->chargeCurrent % 256;
        request[index++] = action->dischargeCurrent / 256;
        request[index++] = action->dischargeCurrent % 256;
        request[index++] = action->cycleCount;
        request[index++] = action->cycleDelay;
        request[index++] = action->cycleWay;
        request[index++] = action->peakSense;
        if (action->type == BatteryType::NiCd || action->type == BatteryType::NiMH) {
            request[index++] = action->cutVoltage / 256;
            request[index++] = action->cutVoltage % 256;
        } else {
            request[index++] = action->predefinedDischargeCutVoltage[action->type] * action->cells / 256;
            request[index++] = action->predefinedDischargeCutVoltage[action->type] * action->cells % 256;
        }
        request[index++] = action->predefinedChargeCutVoltage[action->type] / 256;
        request[index++] = action->predefinedChargeCutVoltage[action->type] % 256;
        request[index++] = action->trickle / 256;
        request[index++] = action->trickle % 256;
        request[index++] = action->rPeakCount;
        break;

    case ChargerCommand::SET_SYS_INFO:
        sysInfo = (SystemInfo *)data;
        request[index++] = sysInfo->keyBeep;
        request[index++] = sysInfo->buzzer;
        request[index++] = sysInfo->capacityCut;
        request[index++] = sysInfo->timeCut;
        request[index++] = sysInfo->temperatureUnit;
        request[index++] = sysInfo->capacityLimit / 256;
        request[index++] = sysInfo->capacityLimit % 256;
        request[index++] = sysInfo->timeLimit / 10;
        request[index++] = sysInfo->tempLimit;
        request[index++] = sysInfo->restTime;
        request[index++] = sysInfo->dcInputLowCut;
        request[index++] = sysInfo->sensitivityNiMH;
        request[index++] = sysInfo->sensitivityNiCd;
        request[index++] = sysInfo->acPower;
        request[index++] = sysInfo->tempCut;

        break;

    default:
        break;
    }

    // Compute checksum
    unsigned char cs = 0;
    for (int i = 3; i < index; i++)
    {
        cs = cs + request[i];
    }

    // Set request size
    request[2] = index - 2;

    // Set checksum
    request[index++] = cs;

    // Set tail
    request[index++] = 0xff;
    request[index] = 0xff;

    // Send request
    int len = hid_write(m_hidDevice, request, BUFFER_SIZE);
    if (len < 0)
    {
        throw HidException(-1, tr("Sending data to device failed."));
    }

    std::array<unsigned char, BUFFER_SIZE> response = {0};

    if (cmd == ChargerCommand::CHARGE_INFO || cmd == ChargerCommand::DEVICE_INFO  || cmd == ChargerCommand::GET_SYS_INFO)
    {
        // Read response from device
        len = hid_read(m_hidDevice, response.data(), BUFFER_SIZE);

        if (len < 0)
        {
            throw HidException(-1, tr("Reading data to device failed."));
        }
    }

    return response;
}
