/**
 * \file definitions.h
 * \brief Header file containing constants and definitions for the project.
 *
 * This file defines constants and provides important definitions
 * used throughout the project.
 *
 * \author Constantin
 */

#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include <cstddef> // For NULL, size_t, ptrdiff_t, and other standard library facilities related to sizes and offsets.

// Version information
constexpr const char* VERSION_BUILD = "1.4 Windows x86_32"; ///< Version and build information of the application

// Maximum path length
constexpr std::size_t MAX_PATH_LENGTH = 260;

// Maximum size for arrays
constexpr std::size_t MAX_ARRAY_SIZE = 20;

// Alias for MAX_ARRAY_SIZE, used for clarity
constexpr size_t MAX_ENTRIES{MAX_ARRAY_SIZE};

// Main window dimensions
constexpr int MAIN_WINDOW_WIDTH  = 1450; ///< Width of the main window in pixels
constexpr int MAIN_WINDOW_HEIGHT = 800;  ///< Height of the main window in pixels

// Minimum and maximum temperature
constexpr size_t MIN_TEMPERATURE = 0.0;   ///< Minimum allowable temperature in Celsius
constexpr size_t MAX_TEMPERATURE = 100.0; ///< Maximum allowable temperature in Celsius

// Default density values
constexpr double DEFAULT_DENSITY_BELOW_ZERO    = 999.8395; ///< Default density when temperature is below zero
constexpr double DEFAULT_DENSITY_ABOVE_HUNDRED = 958.3449; ///< Default density when temperature is above one hundred

// Default volume correction values
constexpr double DEFAULT_VOLUME_CORRECTION_BELOW_ZERO     = 1.00116; ///< Default volume correction factor when temperature is below zero
constexpr double DEFAULT_VOLUME_CORRECTION__ABOVE_HUNDRED = 1.04451; ///< Default volume correction factor when temperature is above one hundred

// CSV delimiter
constexpr char CSV_DELIMITER = ','; ///< Delimiter used in CSV files

// Maximum number of flow meter types
constexpr std::size_t MAX_NUMBER_FLOW_METER_TYPES = 1000; ///< Maximum number of flow meter types supported

// File name for flow meter types CSV
constexpr const char* CSV_FLOW_METER_TYPES = "watermeters.csv"; ///< Filename of the CSV file containing flow meter types

// Set the needed spaced for HTML page
#define SPACES_INDENT_HTML "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"

// Constants for MD5Transform routine
constexpr int S11 = 7;  ///< MD5 transformation constant S11
constexpr int S12 = 12; ///< MD5 transformation constant S12
constexpr int S13 = 17; ///< MD5 transformation constant S13
constexpr int S14 = 22; ///< MD5 transformation constant S14
constexpr int S21 = 5;  ///< MD5 transformation constant S21
constexpr int S22 = 9;  ///< MD5 transformation constant S22
constexpr int S23 = 14; ///< MD5 transformation constant S23
constexpr int S24 = 20; ///< MD5 transformation constant S24
constexpr int S31 = 4;  ///< MD5 transformation constant S31
constexpr int S32 = 11; ///< MD5 transformation constant S32
constexpr int S33 = 16; ///< MD5 transformation constant S33
constexpr int S34 = 23; ///< MD5 transformation constant S34
constexpr int S41 = 6;  ///< MD5 transformation constant S41
constexpr int S42 = 10; ///< MD5 transformation constant S42
constexpr int S43 = 15; ///< MD5 transformation constant S43
constexpr int S44 = 21; ///< MD5 transformation constant S44

// Filename of the Romanian language manual
constexpr const char* MANUAL_RO = "Manual de utilizare WStreamLab V1.4.pdf";

#endif // DEFINITIONS_H_INCLUDED
