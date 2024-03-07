/*
 *  Author: Constantin
 *  File:   definitions.h
 *  Description: Header file containing constants and definitions for the project.
 */

#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include <cstddef>

// Maximum path length
constexpr std::size_t MAX_PATH_LENGTH = 260;

// Maximum size for arrays
constexpr std::size_t MAX_ARRAY_SIZE = 20;

// Alias for MAX_ARRAY_SIZE, used for clarity
constexpr size_t MAX_ENTRIES{MAX_ARRAY_SIZE};

// Main window dimensions
constexpr int MAIN_WINDOW_WIDTH = 1450;
constexpr int MAIN_WINDOW_HEIGHT = 800;

// Minimum and maximum temperature
constexpr size_t MIN_TEMPERATURE = 0.0;
constexpr size_t MAX_TEMPERATURE = 100.0;

// Default density values
constexpr double DEFAULT_DENSITY_BELOW_ZERO = 999.8395;
constexpr double DEFAULT_DENSITY_ABOVE_HUNDRED = 958.3449;

// Default density values
constexpr double DEFAULT_VOLUME_CORRECTION_BELOW_ZERO = 1.00116;
constexpr double DEFAULT_VOLUME_CORRECTION__ABOVE_HUNDRED = 1.04451;

// Version information
constexpr const char* VERSION_BUILD = "1.3 Windows x86_32";

// CSV delimiter
constexpr char CSV_DELIMITER = ',';

// Maximum number of flow meter types
constexpr std::size_t MAX_NUMBER_FLOW_METER_TYPES = 1000;

// File name for flow meter types CSV
constexpr const char* CSV_FLOW_METER_TYPES = "watermeters.csv";

// Constants for MD5Transform routine
constexpr int S11 = 7;
constexpr int S12 = 12;
constexpr int S13 = 17;
constexpr int S14 = 22;
constexpr int S21 = 5;
constexpr int S22 = 9;
constexpr int S23 = 14;
constexpr int S24 = 20;
constexpr int S31 = 4;
constexpr int S32 = 11;
constexpr int S33 = 16;
constexpr int S34 = 23;
constexpr int S41 = 6;
constexpr int S42 = 10;
constexpr int S43 = 15;
constexpr int S44 = 21;

constexpr const char* MANUAL_RO ="Manual de utilizare WStreamLab V1.2.pdf";

#endif // DEFINITIONS_H
