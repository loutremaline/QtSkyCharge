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
