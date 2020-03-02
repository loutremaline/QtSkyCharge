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
#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <QDialog>
#include <QTimer>
#include "systemInfo.h"

namespace Ui {
    class SystemSettings;
}

class SystemSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSettings(QWidget *parent = nullptr, unsigned char slot = 0);
    ~SystemSettings();

private slots:
    void on_chkTimeCut_stateChanged(int state);
    void on_chkCapacityCut_stateChanged(int state);
    void on_chkTempCut_stateChanged(int state);
    void initTimer_timeout();
    void on_btnSave_clicked();

private:
    Ui::SystemSettings *ui;
    unsigned char m_slot = 0;
    QTimer m_initTimer;
    SystemInfo m_sysInfo;


};

#endif // SYSTEMSETTINGS_H
