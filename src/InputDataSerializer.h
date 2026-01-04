/**
 * \file InputDataSerializer.h
 * \brief Serialization and deserialization for TableBoard input data
 *
 * This file provides a clean separation of I/O operations from UI logic,
 * with proper error handling, file format validation, and versioning support.
 *
 * \author Constantin
 * \date 2026-01-01
 */

#ifndef INPUTDATASERIALIZER_H
#define INPUTDATASERIALIZER_H

#include <QString>
#include <QStringList>
#include <vector>
#include <cstdint>

/**
 * \brief Namespace for TableBoard-related constants
 */
namespace TableBoardConstants {
    constexpr int AUTOHIDE_MESSAGE_DURATION_MS = 3000;  ///< Duration for auto-hide messages (3 seconds)
    constexpr size_t MAX_ENTRIES = 20;                  ///< Maximum number of water meter entries
    constexpr const char* INPUT_FILE_EXTENSION = ".in"; ///< Input file extension
    constexpr const char* INPUT_FILE_FILTER = "Input data (*.in);;All files (*.*)"; ///< File dialog filter
}

/**
 * \brief Handles serialization and deserialization of water meter input data
 *
 * This class provides a robust, maintainable way to save and load input data
 * with proper error handling, file format validation, and version control.
 */
class InputDataSerializer {
public:
    /**
     * \brief File format header for validation and versioning
     */
    struct FileHeader {
        static constexpr const char* MAGIC = "WSTREAML"; ///< Magic identifier (8 bytes)
        static constexpr uint16_t VERSION = 1;            ///< Current file format version

        char magic[8];           ///< Magic number to identify file type
        uint16_t version;        ///< File format version
        uint32_t entriesCount;   ///< Number of water meter entries
        uint32_t reserved;       ///< Reserved for future use (alignment/checksum)
    };

    /**
     * \brief Data for a single water meter entry
     */
    struct MeterEntry {
        QString serialNumber;      ///< Water meter serial number
        QString firstIndexStart;   ///< First index start value
        QString firstIndexStop;    ///< First index stop value
        QString secondIndexStart;  ///< Second index start value
        QString secondIndexStop;   ///< Second index stop value
        QString thirdIndexStart;   ///< Third index start value
        QString thirdIndexStop;    ///< Third index stop value

        MeterEntry() = default;
    };

    /**
     * \brief Flow rate measurement data
     */
    struct FlowRateData {
        QString flowRate;    ///< Flow rate value
        QString mass;        ///< Mass measurement
        QString temperature; ///< Temperature measurement
        QString volume;      ///< Volume measurement

        FlowRateData() = default;
    };

    /**
     * \brief Complete input data structure
     */
    struct InputData {
        size_t entriesNumber;            ///< Number of entries
        QString waterMeterName;          ///< Water meter type name
        QString ambientTemperature;      ///< Ambient temperature (°C)
        QString atmosphericPressure;     ///< Atmospheric pressure (mbar)
        QString relativeAirHumidity;     ///< Relative air humidity (%)

        bool rbVolumetric;               ///< Volumetric method selected
        bool rbGravimetric;              ///< Gravimetric method selected
        bool rbManual;                   ///< Manual mode selected
        bool rbInterface;                ///< Interface mode selected
        bool rbTerminal;                 ///< Terminal mode selected

        std::vector<MeterEntry> meterEntries; ///< Water meter entries
        FlowRateData minimum;            ///< Minimum flow rate data
        FlowRateData transitory;         ///< Transitory flow rate data
        FlowRateData nominal;            ///< Nominal flow rate data

        InputData() : entriesNumber(0), rbVolumetric(false), rbGravimetric(false),
                      rbManual(false), rbInterface(false), rbTerminal(false) {}
    };

    /**
     * \brief Save input data to file
     *
     * \param filePath Full path to the output file
     * \param data Input data to save
     * \param errorMsg Output parameter for error message (if any)
     * \return true on success, false on failure
     */
    static bool save(const QString& filePath, const InputData& data, QString& errorMsg);

    /**
     * \brief Load input data from file
     *
     * \param filePath Full path to the input file
     * \param data Output parameter for loaded data
     * \param errorMsg Output parameter for error message (if any)
     * \return true on success, false on failure
     */
    static bool load(const QString& filePath, InputData& data, QString& errorMsg);

private:
    /**
     * \brief Write file header with validation data
     *
     * \param stream Output stream
     * \param entriesCount Number of entries to write
     * \return true on success, false on failure
     */
    static bool writeHeader(std::ofstream& stream, size_t entriesCount);

    /**
     * \brief Read and validate file header
     *
     * \param stream Input stream
     * \param header Output parameter for header data
     * \param errorMsg Output parameter for error message
     * \return true if valid, false otherwise
     */
    static bool readHeader(std::ifstream& stream, FileHeader& header, QString& errorMsg);

    /**
     * \brief Write a single meter entry to stream
     *
     * \param stream Output stream
     * \param entry Meter entry to write
     * \return true on success, false on failure
     */
    static bool writeEntry(std::ofstream& stream, const MeterEntry& entry);

    /**
     * \brief Read a single meter entry from stream
     *
     * \param stream Input stream
     * \param entry Output parameter for meter entry
     * \return true on success, false on failure
     */
    static bool readEntry(std::ifstream& stream, MeterEntry& entry);

    /**
     * \brief Write flow rate data to stream
     *
     * \param stream Output stream
     * \param data Flow rate data to write
     * \return true on success, false on failure
     */
    static bool writeFlowRate(std::ofstream& stream, const FlowRateData& data);

    /**
     * \brief Read flow rate data from stream
     *
     * \param stream Input stream
     * \param data Output parameter for flow rate data
     * \return true on success, false on failure
     */
    static bool readFlowRate(std::ifstream& stream, FlowRateData& data);

    /**
     * \brief Write a QString to stream with newline
     *
     * \param stream Output stream
     * \param value String to write
     * \return true on success, false on failure
     */
    static bool writeLine(std::ofstream& stream, const QString& value);

    /**
     * \brief Read a line from stream into QString
     *
     * \param stream Input stream
     * \param value Output parameter for string
     * \return true on success, false on failure
     */
    static bool readLine(std::ifstream& stream, QString& value);
};

#endif // INPUTDATASERIALIZER_H
