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

#include <cstddef>  // For NULL, size_t, ptrdiff_t, and other standard library facilities related to sizes and offsets.

// Version information - Single source of truth
#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 8
#define APP_VERSION_PATCH 0
#define APP_VERSION_REVISION 0

// Helper macros for stringification
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Automatically construct version strings from components
#define APP_VERSION_STRING \
    TOSTRING(APP_VERSION_MAJOR) "." \
    TOSTRING(APP_VERSION_MINOR) "." \
    TOSTRING(APP_VERSION_PATCH)

#define VERSION_BUILD \
    TOSTRING(APP_VERSION_MAJOR) "." \
    TOSTRING(APP_VERSION_MINOR) "." \
    TOSTRING(APP_VERSION_PATCH) "." \
    TOSTRING(APP_VERSION_REVISION)

// Constexpr versions for programmatic access
constexpr int AppVersionMajor = APP_VERSION_MAJOR;
constexpr int AppVersionMinor = APP_VERSION_MINOR;
constexpr int AppVersionPatch = APP_VERSION_PATCH;
constexpr int AppVersionRevision = APP_VERSION_REVISION;

// Registry path for application settings
constexpr const char* REGISTRY_PATH = "HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab";  ///< Windows registry path for storing application settings

// Maximum path length
constexpr std::size_t MAX_PATH_LENGTH = 260;

/* When defined, this flag removes RS-485/422 MODBUS related menu options and
 * functionality from the application. This is useful for deployments that
 * don't require serial communication capabilities.
 *
 * To enable RS-485/422 MODBUS support, comment out or remove this definition.
 */
#define BUILD_WITHOUT_RS_485_422_MODBUS

// Maximum size for arrays
constexpr std::size_t MAX_ARRAY_SIZE = 20;

// Alias for MAX_ARRAY_SIZE, used for clarity
constexpr size_t MAX_ENTRIES{MAX_ARRAY_SIZE};

// Main window dimensions
constexpr int MAIN_WINDOW_WIDTH = 1450;  ///< Width of the main window in pixels
constexpr int MAIN_WINDOW_HEIGHT = 800;  ///< Height of the main window in pixels

// Minimum and maximum temperature
constexpr double MIN_TEMPERATURE = 0.0;    ///< Minimum allowable temperature in Celsius
constexpr double MAX_TEMPERATURE = 100.0;  ///< Maximum allowable temperature in Celsius

// Default density values
constexpr double DEFAULT_DENSITY_BELOW_ZERO = 999.8395;     ///< Default density when temperature is below zero
constexpr double DEFAULT_DENSITY_ABOVE_HUNDRED = 958.3449;  ///< Default density when temperature is above one hundred

// Standard "ideal" water density at 20°C
constexpr double RHO_WATER_IDEAL_20_GRAD_C = 998.2009;

// Correction Factor for Air Buoyancy
constexpr double CORRECTION_FACTOR_AIR_BUOYANCY = 1.00105;

// Default volume correction values
constexpr double DEFAULT_VOLUME_CORRECTION_BELOW_ZERO =
    1.00116;  ///< Default volume correction factor when temperature is below zero
constexpr double DEFAULT_VOLUME_CORRECTION_ABOVE_HUNDRED =
    1.04451;  ///< Default volume correction factor when temperature is above one hundred

// CSV delimiter
constexpr char CSV_DELIMITER = ',';  ///< Delimiter used in CSV files

constexpr std::size_t MAX_NUMBER_FLOW_METERS = 20;

// Maximum number of flow meter types
constexpr std::size_t MAX_NUMBER_FLOW_METER_TYPES = 1000;  ///< Maximum number of flow meter types supported

// File name for flow meter types CSV
constexpr const char* CSV_FLOW_METER_TYPES =
    "watermeters.csv";  ///< Filename of the CSV file containing flow meter types

// Set the needed spaced for HTML page
#define SPACES_INDENT_HTML "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"

// Constants for MD5Transform routine
constexpr int S11 = 7;   ///< MD5 transformation constant S11
constexpr int S12 = 12;  ///< MD5 transformation constant S12
constexpr int S13 = 17;  ///< MD5 transformation constant S13
constexpr int S14 = 22;  ///< MD5 transformation constant S14
constexpr int S21 = 5;   ///< MD5 transformation constant S21
constexpr int S22 = 9;   ///< MD5 transformation constant S22
constexpr int S23 = 14;  ///< MD5 transformation constant S23
constexpr int S24 = 20;  ///< MD5 transformation constant S24
constexpr int S31 = 4;   ///< MD5 transformation constant S31
constexpr int S32 = 11;  ///< MD5 transformation constant S32
constexpr int S33 = 16;  ///< MD5 transformation constant S33
constexpr int S34 = 23;  ///< MD5 transformation constant S34
constexpr int S41 = 6;   ///< MD5 transformation constant S41
constexpr int S42 = 10;  ///< MD5 transformation constant S42
constexpr int S43 = 15;  ///< MD5 transformation constant S43
constexpr int S44 = 21;  ///< MD5 transformation constant S44

// UI timing constants
constexpr int SPLASH_SCREEN_DURATION_MS = 3000;  ///< Splash screen display duration in milliseconds
constexpr int PDF_RESOLUTION_DPI = 300;          ///< PDF output resolution in DPI

// UI Layout constants
constexpr int UI_DEFAULT_SPACING = 4;       ///< Default spacing between widgets in pixels
constexpr int UI_DEFAULT_MARGIN = 5;        ///< Default margin around layouts in pixels
constexpr int UI_GROUPBOX_SPACING = 10;     ///< Spacing for group boxes
constexpr int UI_BUTTON_MIN_WIDTH = 100;    ///< Minimum button width in pixels
constexpr int UI_BUTTON_MIN_HEIGHT = 30;    ///< Minimum button height in pixels
constexpr int UI_LINEEDIT_HEIGHT = 28;      ///< Standard line edit height in pixels
constexpr int UI_COMBOBOX_MIN_HEIGHT = 20;  ///< Minimum combo box height in pixels

// UI Color constants (RGB values)
constexpr int UI_COLOR_ERROR_RED = 0xFF0000;           ///< Red color for error states
constexpr int UI_COLOR_SUCCESS_GREEN = 0xDCEBDC;      ///< Light green for success states (220, 235, 220)
constexpr int UI_COLOR_BACKGROUND_GRAY = 0xEBEBEB;    ///< Light gray background (235, 235, 235)
constexpr int UI_COLOR_BORDER_BLUE = 0xADD8E6;        ///< Light blue border color
constexpr int UI_COLOR_GROUPBOX_PURPLE = 0xE6E6FF;    ///< Light purple for group boxes (230, 230, 255)
constexpr int UI_COLOR_PRIMARY_BLUE = 0x0078D7;       ///< Primary blue for focus indicators

// Filename of the Romanian language manual
constexpr const char* MANUAL_RO = "Manual de utilizare WStreamLab V1.8.pdf";

#endif  // DEFINITIONS_H_INCLUDED
