#ifndef CHARGEACTION_H
#define CHARGEACTION_H

#include "enum.h"

/**
 * @brief Action that could be processed on charger device.
 */
class ChargeAction
{
public:
    /**
     * @brief Battery type (default : LiPo).
     */
    BatteryType type = BatteryType::LiPo;

    /**
     * @brief Cells number.
     */
    unsigned char cells;

    /**
     * @brief mode (default : NiCharge / LiCharge)
     */
    unsigned char mode = 0x00;

    /**
     * @brief Charge current (default 0.1A)
     */
    unsigned short int chargeCurrent = 100;

    /**
     * @brief Discharge Current (default : 0.1A)
     */
    unsigned short int dischargeCurrent = 100;

    /**
     * @brief Charge / discharge cycle number (default : 1)
     */
    unsigned char cycleCount = 1;

    /**
     * @brief Delay between charge and discharge in cyle (default : 10mn).
     */
    unsigned char cycleDelay = 10;

    /**
     * @brief Start mode (discharge or charge) for cycle (default : DCHG_CHG)
     */
    CycleWay cycleWay;

    /**
     * @brief Delta Peak (default : 4mV)
     */
    unsigned char peakSense = 4;

    /**
     * @brief ??? mA (default : 0)
     */
    unsigned short int trickle = 0;

    /**
     * @brief Re-peak cycle count (default : 1)
     */
    unsigned char rPeakCount;



    /**
     * @brief Predefined discharge end voltage (for each battery type)
     */
    unsigned short int predefinedDischargeCutVoltage[7] = {3200, 2600, 3100, 3200, 1000, 1000, 1800};

    /**
     * @brief Predefined charge end voltage (for each battery type)
     */
    unsigned short int predefinedChargeCutVoltage[7] = {4200, 3600, 4100, 4350, 1800, 1800, 2400};

};

#endif // CHARGEACTION_H
