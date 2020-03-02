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
#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

class SystemInfo
{
public:
    /**
     * @brief Is beep on key pressed enabled.
     */
    bool keyBeep;

    /**
     * @brief Is system buzzer enabled
     */
    bool buzzer;

    /**
     * @brief Is capacity limit cut-off enabled.
     */
    bool capacityCut;

    /**
     * @brief Is time limit cut-off enabled.
     */
    bool timeCut;

    /**
     * @brief Is temperature cut-off enabled.
     */
    bool tempCut;

    /**
     * @brief Capacity limit.
     */
    unsigned short capacityLimit;

    /**
     * @brief Time limit.
     */
    unsigned short timeLimit;

    /**
     * @brief Temperature limit.
     */
    unsigned short tempLimit;

    /**
     * @brief PAuse time between charge and discharge when cycling.
     */
    unsigned char restTime;

    /**
     * @brief Delta Peak sensitivity for NiCd.
     */
    unsigned char sensitivityNiCd;

    /**
     * @brief Delta Peak sensitivity for NiMH.
     */
    unsigned char sensitivityNiMH;

    /**
     * @brief Minimal DC input voltage before cut-off.
     */
    unsigned char dcInputLowCut;

    /**
     * @brief Temperature unit (celsius / fahrenheit)
     */
    unsigned char temperatureUnit;

    /**
     * @brief ??
     */
    unsigned char acPower;


};

#endif // SYSTEMINFO_H
