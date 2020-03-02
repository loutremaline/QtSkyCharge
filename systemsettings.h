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
