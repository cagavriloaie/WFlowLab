/*
 *  Author: Constantin
 *  File:   definitions.h
 *  Description: Header file containing constants and definitions for the project.
 */
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>

#define MAX_ARRAY_SIZE 20

#define MAIN_WINDOW_WIDTH   1450
#define MAIN_WINDOW_HEIGHT   800

// Version information
#define VERSION_BUILD "1.2 Windows x86_32"

// CSV delimiter
constexpr char DELIMITER{','};

// Maximum number of flow meter types
constexpr size_t MAX_NUMBER_FLOW_METER_TYPES{1000};

// File name for flow meter types CSV
#define CSV_FLOW_METER_TYPES  "watermeters.csv"

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
