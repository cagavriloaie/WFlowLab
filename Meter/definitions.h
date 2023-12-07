/*
 *  Author: Constantin
 *  File:   definitions.h
 */
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstddef>

// Version information
#define VERSION_BUILD "1.2 Windows x86_32"

// CSV delimiter
constexpr char DELIMITER{';'};

// Maximum number of flow meter types
constexpr size_t MAX_NUMBER_FLOW_METER_TYPES{1000};

// File name for flow meter types CSV
#define CSV_FLOW_METER_TYPES  "watermeters.csv"

// Constants for MD5Transform routine
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#endif // DEFINITIONS_H
