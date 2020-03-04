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
#ifndef CONST_H
#define CONST_H

#include <QObject>
#include <QString>

class Labels : QObject
{

public:
    static const QString batteryTypesLabel[7];
    static const QString modeLiLabel[5];
    static const QString modeNiLabel[5];
    static const QString cycleOrderLabel[2];
};

const QString Labels::batteryTypesLabel[] = { tr("LiPo"), tr("LiFe"), tr("LiIo"), tr("LiHV"), tr("NiMH"), tr("NiCd"), tr("Pb") };
const QString Labels::modeLiLabel[] = { tr("Charge"), tr("Fast charge"), tr("Storage") , tr("Discharge") , tr("Balance") };
const QString Labels::modeNiLabel[] = { tr("Charge"), tr("Auto charge"), tr("Discharge"), tr("Re Peak") , tr("Cycle") };
const QString Labels::cycleOrderLabel[] = { tr("DCHG>CHG"), tr("CHG>DCHG") };

#endif // CONST_H
