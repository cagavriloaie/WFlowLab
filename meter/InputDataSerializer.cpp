/**
 * \file InputDataSerializer.cpp
 * \brief Implementation of InputDataSerializer
 *
 * \author Constantin
 * \date 2026-01-01
 */

#include "InputDataSerializer.h"
#include <fstream>
#include <cstring>
#include <QFileInfo>
#include <QDir>

bool InputDataSerializer::save(const QString& filePath, const InputData& data, QString& errorMsg) {
    // Validate entries count
    if (data.entriesNumber > TableBoardConstants::MAX_ENTRIES) {
        errorMsg = QString("Entries count (%1) exceeds maximum (%2)")
            .arg(data.entriesNumber)
            .arg(TableBoardConstants::MAX_ENTRIES);
        return false;
    }

    if (data.meterEntries.size() != data.entriesNumber) {
        errorMsg = QString("Mismatch between declared entries (%1) and actual data (%2)")
            .arg(data.entriesNumber)
            .arg(data.meterEntries.size());
        return false;
    }

    // Ensure directory exists
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            errorMsg = QString("Cannot create directory: %1").arg(dir.absolutePath());
            return false;
        }
    }

    // Open file for writing
    std::ofstream file(filePath.toStdString(), std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        errorMsg = QString("Cannot open file for writing: %1").arg(filePath);
        return false;
    }

    // Write header
    if (!writeHeader(file, data.entriesNumber)) {
        errorMsg = "Failed to write file header";
        file.close();
        return false;
    }

    // Write metadata
    if (!writeLine(file, data.waterMeterName) ||
        !writeLine(file, data.ambientTemperature) ||
        !writeLine(file, data.atmosphericPressure) ||
        !writeLine(file, data.relativeAirHumidity)) {
        errorMsg = "Failed to write metadata";
        file.close();
        return false;
    }

    // Write boolean flags
    file << (data.rbVolumetric ? "1" : "0") << "\n";
    file << (data.rbGravimetric ? "1" : "0") << "\n";
    file << (data.rbManual ? "1" : "0") << "\n";
    file << (data.rbInterface ? "1" : "0") << "\n";
    file << (data.rbTerminal ? "1" : "0") << "\n";

    if (!file.good()) {
        errorMsg = "Failed to write boolean flags";
        file.close();
        return false;
    }

    // Write meter entries
    for (const auto& entry : data.meterEntries) {
        if (!writeEntry(file, entry)) {
            errorMsg = "Failed to write meter entry";
            file.close();
            return false;
        }
    }

    // Write flow rate data
    if (!writeFlowRate(file, data.minimum) ||
        !writeFlowRate(file, data.transitory) ||
        !writeFlowRate(file, data.nominal)) {
        errorMsg = "Failed to write flow rate data";
        file.close();
        return false;
    }

    file.close();

    // Verify file was written successfully
    if (!file.good()) {
        errorMsg = "File write operation failed";
        return false;
    }

    return true;
}

bool InputDataSerializer::load(const QString& filePath, InputData& data, QString& errorMsg) {
    // Check if file exists
    if (!QFileInfo::exists(filePath)) {
        errorMsg = QString("File does not exist: %1").arg(filePath);
        return false;
    }

    // Open file for reading
    std::ifstream file(filePath.toStdString(), std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        errorMsg = QString("Cannot open file for reading: %1").arg(filePath);
        return false;
    }

    // Read and validate header
    FileHeader header;
    if (!readHeader(file, header, errorMsg)) {
        file.close();
        return false;
    }

    // Validate entries count
    if (header.entriesCount > TableBoardConstants::MAX_ENTRIES) {
        errorMsg = QString("File contains %1 entries, but maximum is %2")
            .arg(header.entriesCount)
            .arg(TableBoardConstants::MAX_ENTRIES);
        file.close();
        return false;
    }

    data.entriesNumber = header.entriesCount;

    // Read metadata
    if (!readLine(file, data.waterMeterName) ||
        !readLine(file, data.ambientTemperature) ||
        !readLine(file, data.atmosphericPressure) ||
        !readLine(file, data.relativeAirHumidity)) {
        errorMsg = "Failed to read metadata";
        file.close();
        return false;
    }

    // Read boolean flags
    QString tmpLine;
    if (!readLine(file, tmpLine)) {
        errorMsg = "Failed to read rbVolumetric flag";
        file.close();
        return false;
    }
    data.rbVolumetric = (tmpLine == "1" || tmpLine.toLower() == "true");

    if (!readLine(file, tmpLine)) {
        errorMsg = "Failed to read rbGravimetric flag";
        file.close();
        return false;
    }
    data.rbGravimetric = (tmpLine == "1" || tmpLine.toLower() == "true");

    if (!readLine(file, tmpLine)) {
        errorMsg = "Failed to read rbManual flag";
        file.close();
        return false;
    }
    data.rbManual = (tmpLine == "1" || tmpLine.toLower() == "true");

    if (!readLine(file, tmpLine)) {
        errorMsg = "Failed to read rbInterface flag";
        file.close();
        return false;
    }
    data.rbInterface = (tmpLine == "1" || tmpLine.toLower() == "true");

    if (!readLine(file, tmpLine)) {
        errorMsg = "Failed to read rbTerminal flag";
        file.close();
        return false;
    }
    data.rbTerminal = (tmpLine == "1" || tmpLine.toLower() == "true");

    // Read meter entries
    data.meterEntries.clear();
    data.meterEntries.reserve(data.entriesNumber);

    for (size_t i = 0; i < data.entriesNumber; ++i) {
        MeterEntry entry;
        if (!readEntry(file, entry)) {
            errorMsg = QString("Failed to read meter entry %1").arg(i + 1);
            file.close();
            return false;
        }
        data.meterEntries.push_back(entry);
    }

    // Read flow rate data
    if (!readFlowRate(file, data.minimum) ||
        !readFlowRate(file, data.transitory) ||
        !readFlowRate(file, data.nominal)) {
        errorMsg = "Failed to read flow rate data";
        file.close();
        return false;
    }

    file.close();
    return true;
}

// Private helper methods

bool InputDataSerializer::writeHeader(std::ofstream& stream, size_t entriesCount) {
    FileHeader header;
    std::memcpy(header.magic, FileHeader::MAGIC, 8);
    header.version = FileHeader::VERSION;
    header.entriesCount = static_cast<uint32_t>(entriesCount);
    header.reserved = 0;

    stream.write(reinterpret_cast<const char*>(&header), sizeof(header));
    return stream.good();
}

bool InputDataSerializer::readHeader(std::ifstream& stream, FileHeader& header, QString& errorMsg) {
    stream.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (!stream.good()) {
        errorMsg = "Failed to read file header - file may be corrupted";
        return false;
    }

    // Validate magic number
    if (std::memcmp(header.magic, FileHeader::MAGIC, 8) != 0) {
        errorMsg = "Invalid file format - this is not a WStreamLab input file";
        return false;
    }

    // Check version compatibility
    if (header.version != FileHeader::VERSION) {
        errorMsg = QString("File version (%1) differs from current version (%2) - data may not load correctly")
            .arg(header.version)
            .arg(FileHeader::VERSION);
        // Note: We return false here, but you could make this a warning and continue
        return false;
    }

    return true;
}

bool InputDataSerializer::writeEntry(std::ofstream& stream, const MeterEntry& entry) {
    return writeLine(stream, entry.serialNumber) &&
           writeLine(stream, entry.firstIndexStart) &&
           writeLine(stream, entry.firstIndexStop) &&
           writeLine(stream, entry.secondIndexStart) &&
           writeLine(stream, entry.secondIndexStop) &&
           writeLine(stream, entry.thirdIndexStart) &&
           writeLine(stream, entry.thirdIndexStop);
}

bool InputDataSerializer::readEntry(std::ifstream& stream, MeterEntry& entry) {
    return readLine(stream, entry.serialNumber) &&
           readLine(stream, entry.firstIndexStart) &&
           readLine(stream, entry.firstIndexStop) &&
           readLine(stream, entry.secondIndexStart) &&
           readLine(stream, entry.secondIndexStop) &&
           readLine(stream, entry.thirdIndexStart) &&
           readLine(stream, entry.thirdIndexStop);
}

bool InputDataSerializer::writeFlowRate(std::ofstream& stream, const FlowRateData& data) {
    return writeLine(stream, data.flowRate) &&
           writeLine(stream, data.mass) &&
           writeLine(stream, data.temperature) &&
           writeLine(stream, data.volume);
}

bool InputDataSerializer::readFlowRate(std::ifstream& stream, FlowRateData& data) {
    return readLine(stream, data.flowRate) &&
           readLine(stream, data.mass) &&
           readLine(stream, data.temperature) &&
           readLine(stream, data.volume);
}

bool InputDataSerializer::writeLine(std::ofstream& stream, const QString& value) {
    stream << value.toStdString() << "\n";
    return stream.good();
}

bool InputDataSerializer::readLine(std::ifstream& stream, QString& value) {
    std::string line;
    if (!std::getline(stream, line)) {
        return false;
    }
    value = QString::fromStdString(line);
    return true;
}
