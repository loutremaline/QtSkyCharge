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

#include <QString>

const QString batteryTypesLabel[7] = {"LiPo", "LiFe", "LiIo", "LiHV", "NiMH", "NiCd", "Pb"};
const QString modeLiLabel[5] = { "Charge", "Fast charge","Storage","Discharge","Balance"};
const QString modeNiLabel[5] = {"Charge", "Auto charge","Discharge","Re Peak","Cycle"};

#endif // CONST_H
