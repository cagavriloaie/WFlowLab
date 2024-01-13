/*
 *  Author: Constantin
 *  File:   definitions.h
 *  Description: Header file containing constants and definitions for the project.
 */
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>

constexpr std::size_t MAX_PATH_LENGTH = 260;
constexpr std::size_t MAX_ARRAY_SIZE = 20;

constexpr int MAIN_WINDOW_WIDTH = 1450;
constexpr int MAIN_WINDOW_HEIGHT = 800;

constexpr double DEFAULT_DENSITY_BELOW_ZERO = 999.8395;
constexpr double DEFAULT_DENSITY_ABOVE_100 = 958.3449;

// Version information
const char* const VERSION_BUILD = "1.2 Windows x86_32";

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

#endif // DEFINITIONS_H
