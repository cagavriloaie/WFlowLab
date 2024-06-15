/**
 * \file flow-meter-type.h
 * \brief Header file defining enums for flow meter types.
 *
 * This file defines enums that represent different types of flow meters
 * used in the project.
 *
 * \author Constantin
 */

#ifndef FLOWMETERTYPE_H
#define FLOWMETERTYPE_H

#include <QDir>         // Qt class for handling directories and their contents.
#include <QMessageBox>  // Qt class for displaying modal dialog boxes with messages.
#include <iostream>     // Standard C++ stream input/output library.
#include <fstream>      // Standard C++ file stream input/output library.
#include <sstream>      // Standard C++ string stream input/output library.
#include <vector>       // Standard C++ container class for dynamic arrays.
#include <string>       // Standard C++ string class.
#include "definitions.h"  // User-defined header file containing project-specific definitions.

/** \brief Structure representing a water flow meter type.
 *
 *  This structure holds various properties of a water flow meter, including its name,
 *  nominal diameter, flow rates, and error margins.
 */
struct MeterFlowType
{
    std::string nameWaterMeter; ///< Name of the water meter.
    unsigned nominalDiameter;   ///< Nominal diameter of the water meter.
    double nominalFlow;         ///< Nominal flow rate of the water meter.
    double maximumFlow;         ///< Maximum flow rate of the water meter.
    double trasitionFlow;       ///< Transition flow rate of the water meter.
    double minimumFlow;         ///< Minimum flow rate of the water meter.
    double nominalError;        ///< Nominal error margin of the water meter.
    double maximumError;        ///< Maximum error margin of the water meter.

    /** \brief Constructor to initialize MeterFlowType with specific values.
     *
     *  \param _nameWaterMeter Name of the water meter.
     *  \param _nominalDiameter Nominal diameter of the water meter.
     *  \param _nominalFlow Nominal flow rate of the water meter.
     *  \param _maximumFlow Maximum flow rate of the water meter.
     *  \param _trasitionFlow Transition flow rate of the water meter.
     *  \param _minimumFlow Minimum flow rate of the water meter.
     *  \param _nominalError Nominal error margin of the water meter.
     *  \param _maximumError Maximum error margin of the water meter.
     */
    MeterFlowType(const std::string &_nameWaterMeter,
                  unsigned _nominalDiameter,
                  double _nominalFlow,
                  double _maximumFlow,
                  double _trasitionFlow,
                  double _minimumFlow,
                  double _nominalError,
                  double _maximumError)
        : nameWaterMeter(_nameWaterMeter),
        nominalDiameter(_nominalDiameter),
        nominalFlow(_nominalFlow),
        maximumFlow(_maximumFlow),
        trasitionFlow(_trasitionFlow),
        minimumFlow(_minimumFlow),
        nominalError(_nominalError),
        maximumError(_maximumError) {}

    /** \brief Default constructor to initialize MeterFlowType with default values.
     *
     *  Initializes all properties of the water meter to default values.
     */
    MeterFlowType()
        : nameWaterMeter(""),
        nominalDiameter(0),
        nominalFlow(0),
        maximumFlow(0),
        trasitionFlow(0),
        minimumFlow(0),
        nominalError(0),
        maximumError(0) {}
};

/**
 * \brief Vector containing default MeterFlowType objects representing various water flow meters.
 */
std::vector < MeterFlowType > meterFlowTypesDefault =
{
    // --------------------------------------------------------------------------------------------------------
    //                  Type                           DN       QN      Qmax     Qt      Qmin    ErrNom  ErrMax
    //                                                 mm       l/h      l/h     l/h      l/h       %      %
    // --------------------------------------------------------------------------------------------------------
    MeterFlowType("Itron Flodis DN 15",                15,     1500,     3000,  22.5,      15,      2,     5),
    MeterFlowType("Itron Flodis DN 20",                20,     2500,     5000,  37.5,      25,      2,     5),
    MeterFlowType("Itron Flodis DN 25",                25,     3500,     7000,  52.5,      35,      2,     5),
    // --------------------------------------------------------------------------------------------------------
    MeterFlowType("Itron Flostar DN 40",               40,    16000,    20000,   160,       80,     2,     5),
    MeterFlowType("Itron Flostar DN 50",               50,    25000,    31250,   127,       79,     2,     5),
    MeterFlowType("Itron Flostar DN 65",               65,    40000,    50000,   160,      100,     2,     5),
    MeterFlowType("Itron Flostar DN 80",               80,    63000,    78000,   252,      157,     2,     5),
    MeterFlowType("Itron Flostar DN 100",             100,   100000,   125000,   400,      250,     2,     5),
    MeterFlowType("Itron Flostar DN 150",             150,   160000,   200000,   406,      254,     2,     5),
    // --------------------------------------------------------------------------------------------------------
    MeterFlowType("FGH Sentinel 420 PC DN 15 R80",     15,     2500,     3125,    50,    31.25,     2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 15 R160",    15,     2500,     3125,    25,      15.63,   2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 20 R80",     20,     4000,     5000,   100,     62.5,     2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 20 R160",    20,     4000,     5000,    40,     25.0,     2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 25 R80",     25,     6300,     7875,   126,       78.75,  2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 25 R160",    25,     6300,     7875,    63,       39.4,   2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 25 R80",     25,     8000,    10000,   160,      100,     2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 25 R160",    25,     8000,    10000,    80.64,    50.4,   2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 32 R80",     32,    10000,    12000,   200,      125,     2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 32 R160",    32,    10000,    12000,   100,       62.5,   2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 40 R80",     40,    16000,    20000,   320,      200,     2,     5),
    MeterFlowType("FGH Sentinel 420 PC DN 40 R160",    40,    16000,    20000,   160,      100,     2,     5),
    // --------------------------------------------------------------------------------------------------------
    MeterFlowType("FGH MeiStream Plus Cl. C DN 40",    40,    30000,    50000,   130,       80,     2,     5),
    MeterFlowType("FGH MeiStream Plus Cl. C DN 50",    50,    35000,    55000,   130,       70,     2,     5),
    MeterFlowType("FGH MeiStream Plus Cl. C DN 65",    65,    40000,    60000,   160,      100,     2,     5),
    MeterFlowType("FGH MeiStream Plus Cl. C DN 80",    80,    63000,   120000,   250,      130,     2,     5),
    MeterFlowType("FGH MeiStream Plus Cl. C DN 100",  100,   100000,   160000,   400,    200,       2,     5),
    MeterFlowType("FGH MeiStream Plus Cl. C DN 150",  150,   250000,   400000,   630,   350,        2,     5),
    // --------------------------------------------------------------------------------------------------------
    MeterFlowType("FGH iPERL R800 DN 15",              15,     2500,     3125,     5,      3.13,    2,     5),
    MeterFlowType("FGH iPERL R800 DN 20",              20,     4000,     5000,     8,      5,       2,     5),
    MeterFlowType("FGH iPERL R800 DN 25",              25,     6300,     7875,    12.6,    7.88,    2,     5),
    MeterFlowType("FGH iPERL R800 DN 30",              30,    10000,    12500,    20,     12.5,     2,     5),
    MeterFlowType("FGH iPERL R800 DN 40",              40,    16000,    20000,    32,     20,       2,     5),
    // -------------------------------------------------------------------------------------------------------
    MeterFlowType("FGH MNK DN 15 R80",                 15,     2500,     3125,    50,     31.25,    2,     5),
    MeterFlowType("FGH MNK DN 15 R160",                15,     2500,     3125,    25,     15.63,    2,     5),
    MeterFlowType("FGH MNK DN 20 R80",                 20,     4000,     5000,   100,     62.5,     2,     5),
    MeterFlowType("FGH MNK DN 20 R160",                20,     4000,     5000,    40,     25,       2,     5),
    MeterFlowType("FGH MNK DN 25 R80",                 25,     6300,     7875,   126,     78.75,    2,     5),
    MeterFlowType("FGH MNK DN 25 A",                   25,     6300,    7875,     63,     39.4,     2,     5),
    MeterFlowType("FGH MNK DN 25 B",                   25,     8000,    10000,   160,    100,       2,     5),
    MeterFlowType("FGH MNK DN 25 C",                   25,     8000,    10000,    80.64,  50.4,     2,     5),
    MeterFlowType("FGH MNK DN 32 R80",                 32,    10000,    12000,   200,     125,      2,     5),
    MeterFlowType("FGH MNK DN 32 R160",                32,    10000,    12000,   100,      62.5,    2,     5),
    MeterFlowType("FGH MNK DN 40 R80",                 40,    16000,    20000,   320,     200,      2,     5),
    MeterFlowType("FGH MNK DN 40 R160",                40,    16000,    20000,   160,     100,      2,     5),
    MeterFlowType("FGH MNK DN 50 R80",                 50,    25000,    31250,   500,     312.5,    2,     5),
    MeterFlowType("FGH MNK DN 50 R255",                50,    25000,    31250,   160,     100,      2,     5)
};

/**
 * \brief Reads meter flow types from a CSV file and returns them as a vector of MeterFlowType objects.
 *
 * This function reads meter flow types from the specified CSV file. Each line in the CSV file
 * represents a MeterFlowType object with fields separated by CSV_DELIMITER. If the file cannot
 * be opened, it displays a warning message using QMessageBox and returns the default meter
 * flow types.
 *
 * \param filename The path to the CSV file containing meter flow types.
 * \return std::vector<MeterFlowType> A vector containing MeterFlowType objects read from the CSV file.
 *         If the file cannot be read or is corrupted, it returns meterFlowTypesDefault.
 *
 * \see MeterFlowType, meterFlowTypesDefault, QMessageBox
 */
std::vector < MeterFlowType > readFlowMeterTypesCSV(
    const std::string  &filename)
{
    QString currentPath = QDir::currentPath();
    Q_UNUSED(currentPath);
    std::ifstream file(filename);
    std::vector < MeterFlowType > meterFlowTypes;

    if (!file.is_open())
    {
        QMessageBox warningMessage;
        warningMessage.addButton(QMessageBox::Ok);
        warningMessage.setWindowTitle(QObject::tr("Warning"));
        warningMessage.setText(QObject::tr("Flow Meters DB"));
        warningMessage.setInformativeText(
            QObject::tr("The watermeters.csv with Flow Meters DB cannot be found."));
        warningMessage.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                      Qt::WindowTitleHint |
                                      Qt::WindowCloseButtonHint);
        warningMessage.exec();
        /* Default Water Flow Meters DB */
        return meterFlowTypesDefault;
    }

    bool dbCorrupted = false;

    try
    {
        std::string line;
        size_t expectedFieldCount = 0;

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string field;

            // Count the number of fields in the first line to determine the expected count
            while (std::getline(iss, field, CSV_DELIMITER)) {
                expectedFieldCount++;
            }
        }

        while (std::getline(file, line)) {
            std::string lineCopy = line;
            size_t actualFieldCount = 0;

            // Count the number of fields in the current line
            std::istringstream issCopy(lineCopy);
            std::string field;
            while (std::getline(issCopy, field, CSV_DELIMITER)) {
                actualFieldCount++;
            }

            // Check if the field count matches the expected count
            if (actualFieldCount != expectedFieldCount) {
                dbCorrupted = true;
                continue;
            }

            // Parse the line into MeterFlowType structure
            MeterFlowType meterFlow;
            std::istringstream iss(line);
            std::string token;

            std::getline(iss, meterFlow.nameWaterMeter, CSV_DELIMITER);
            std::getline(iss, token, CSV_DELIMITER);
            meterFlow.nominalDiameter = std::stod(token);
            std::getline(iss, token, CSV_DELIMITER);
            meterFlow.maximumFlow = std::stod(token);
            std::getline(iss, token, CSV_DELIMITER);
            meterFlow.nominalFlow = std::stod(token);
            std::getline(iss, token, CSV_DELIMITER);
            meterFlow.trasitionFlow = std::stod(token);
            std::getline(iss, token, CSV_DELIMITER);
            meterFlow.minimumFlow = std::stod(token);
            std::getline(iss, token, CSV_DELIMITER);
            meterFlow.nominalError = std::stod(token);
            std::getline(iss, token);
            meterFlow.maximumError = std::stod(token);

            // Add the parsed MeterFlowType to the vector
            meterFlowTypes.push_back(meterFlow);
        }
    }
    catch (const std::exception &e)
    {
        file.close();
        QMessageBox warningMessage;
        warningMessage.addButton(QMessageBox::Ok);
        warningMessage.setWindowTitle(QObject::tr("Warning"));
        warningMessage.setText(QObject::tr("Flow Meters DB"));
        warningMessage.setInformativeText(
            QObject::tr("The watermeters.csv with Flow Meters DB is corrupted."));
        warningMessage.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                      Qt::WindowTitleHint |
                                      Qt::WindowCloseButtonHint);
        warningMessage.exec();
        return meterFlowTypesDefault;
    }

    file.close();

    if (dbCorrupted)
    {
        QMessageBox warningMessage;
        warningMessage.addButton(QMessageBox::Ok);
        warningMessage.setWindowTitle(QObject::tr("Warning"));
        warningMessage.setText(QObject::tr("Flow Meters DB"));
        warningMessage.setInformativeText(
            QObject::tr("The watermeters.csv with Flow Meters DB is corrupted."));
        warningMessage.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                      Qt::WindowTitleHint |
                                      Qt::WindowCloseButtonHint);
        warningMessage.exec();
    }
    return meterFlowTypes;
}

/**
 * \brief Database array storing water flow meter types.
 *
 * This array stores information about water flow meter types. Each element represents
 * a MeterFlowType structure, which includes attributes such as name, nominal diameter,
 * flow rates (nominal, maximum, transition, minimum), and error margins.
 *
 * This array is initialized to store up to MAX_NUMBER_FLOW_METER_TYPES meter types.
 * Ensure that the array size is sufficient for your application's needs to avoid overflow.
 *
 * \see MeterFlowType, MAX_NUMBER_FLOW_METER_TYPES
 */
MeterFlowType MeterFlowDB[MAX_NUMBER_FLOW_METER_TYPES] = {};


#endif // FLOWMETERTYPE_H
