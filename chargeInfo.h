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
#ifndef CHARGEINFO_H
#define CHARGEINFO_H

#include "enum.h"

/**
 * @brief Information of the current charge operation (for a given slot).
 */
class ChargeInfo
{
public:
    /**
     * @brief Current state.
     */
    ChargeState state;

    /**
     * @brief Current command.
     */
    ChargerCommand command;

    /**
     * @brief current operation (depending on battery type).
     */
    unsigned char mode;

    /**
     * @brief Concerned slot.
     */
    unsigned char slot;

    /**
     * @brief Battery type.
     */
    BatteryType battery_type;

    /**
     * @brief Current battery voltage.
     */
    unsigned short voltage;

    /**
     * @brief Charge or discharge battery capacity reached.
     */
    unsigned short capacity;

    /**
     * @brief Current battery current.
     */
    unsigned short current;

    /**
     * @brief Total time elapsed for current operation.
     */
    unsigned short time;

    /**
     * @brief Current (external) temperature.
     */
    unsigned char temperature;

    /**
     * @brief Current voltage of each cells.
     */
    unsigned short vCell[6];
};

#endif // CHARGEINFO_H
