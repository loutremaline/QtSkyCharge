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
#ifndef ENUM_H
#define ENUM_H

/**
 * @brief Commands that could be sent to the charger.
 */
enum ChargerCommand
{
    START           = 0x05, // (5) Start ?
    SET_SYS_INFO    = 0x11, // (17)
    CHARGE_INFO     = 0x55, // (85) Get current charge information
    DEVICE_INFO     = 0x57, // (87) Get charge information
    GET_SYS_INFO    = 0x5a, // (90)
    UNKNOW_2        = 0x5f, // (95)
    STOP            = 0xfe  // (254)
};

enum ChargeState
{
    IDLE = 0,
    CHARGING = 1,
    DISCHARGING = 2,
    WAITING = 3,
    FINISH = 4,
    INPUT_LOW = 128,
    INPUT_HIGH = 129,
    CONNECTION_BREAK = 130,
    CELL_CONNECTOR = 131,
    CHECK_MAIN_PORT = 132,
    CAPACITY_CUT = 133,
    TIME_CUT = 134,
    INT_TEMPERATURE = 135,
    BATT_TEMPERATURE = 136,
    OVER_LOAD = 137,
    BATT_REVERSE = 138,
    NO_NEED_CHARGE = 139,
    BATT_FULL = 140,
    OTHER_ERROR = 141
};

enum BatteryType
{
    LiPo = 0x00,
    LiFe = 0x01,
    LiIo = 0x02,
    LiHV = 0x03,
    NiMH = 0x04,
    NiCd = 0x05,
    Pb   = 0x06
};

enum ModeLi
{
    LiCharge    = 0x00,
    LiFast      = 0x01,
    LiStorage   = 0x02,
    LiDischarge = 0x03,
    LiBalance   = 0x04
};

enum ModeNi
{
    NiCharge    = 0x00,
    NiAuto      = 0x01,
    NiDischarge = 0x02,
    NiRePeak    = 0x03,
    NiCycle     = 0x04
};

enum CycleWay
{
    DCHG_CHG    = 0x00,
    CHG_DCHG    = 0x01
};

enum DeviceModel
{
    D100,   // 100089
    D200,   // 100097
    D400,   // 100123
    D100V2, // 100131
    D250,   // 100125
    D260    // 100157
};

#endif // ENUM_H
