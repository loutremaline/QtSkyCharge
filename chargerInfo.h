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
