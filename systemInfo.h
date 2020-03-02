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
