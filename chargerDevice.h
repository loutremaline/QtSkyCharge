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
#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <array>
#include "hidapi/hidapi.h"
#include "enum.h"
#include "chargerInfo.h"
#include "chargeInfo.h"
#include "chargeAction.h"
#include "systemInfo.h"
#include "hidexception.h"

#define BUFFER_SIZE 64
#define VENDOR_ID   0x0000
#define PRODUCT_ID  0x0001


/**
 * @brief Represents a charger device.
 */
class ChargerDevice : public QObject
{
public:
    ChargerDevice();
    ~ChargerDevice();

    /**
     * @brief retrieve charger information.
     * @return charger information.
     */
    ChargerInfo getDeviceInfo();

    /**
     * @brief Retrieve current charge information.
     * @param slot slot to consider for retrieve charge information.
     * @return charge information.
     */
    ChargeInfo getChargeInfo(unsigned char slot);

    /**
     * @brief Retrieve system settings for given slot.
     * @param slot number to process.
     * @return system settings.
     */
    SystemInfo getSystemInfo(unsigned char slot);

    /**
     * @brief Save system settings for a given slot.
     * @param slot number to process.
     * @param settings to save.
     */
    void saveSystemInfo(unsigned char slot, SystemInfo *sysInfo);

    /**
     * @brief Start selected action.
     * @param slot number to process.
     * @param action to start.
     */
    void start(unsigned char slot, ChargeAction *action);

    /**
     * @brief Stop current action.
     * @param slot number to process.
     */
    void stop(unsigned char slot);



private:
    char m_initFlags = {0};
    hid_device *m_hidDevice = nullptr;

    /**
     * @brief ensure hid device is connected before sending an order.
     */
    void m_ensureHidDeviceOpened();

    /**
     * @brief open the underlying hid device port.
     */
    void m_openHidDevice();

    /**
     * @brief close the underlying hid device port.
     */
    void m_closeHidDevice();

    std::array<unsigned char, BUFFER_SIZE> m_sendCommand(ChargerCommand cmd, unsigned char slot, void *data);

};

#endif // DEVICE_H
