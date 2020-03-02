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
#ifndef CHARGERINFO_H
#define CHARGERINFO_H

#include <string>

/**
 * @brief Charger information.
 */
class ChargerInfo
{
public:

    /**
     * @brief Charger model code.
     */
    std::string coreType;

    /**
     * @brief Current software version installed on the charger. First digit : major release. Second digit : minor release.
     */
    unsigned char softwareVersion[2];
    /**
     * @brief Current hardware version installed on teh charger.
     */
    unsigned char hardwareVersion;
};

#endif // CHARGERINFO_H
