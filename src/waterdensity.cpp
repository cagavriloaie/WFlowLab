/**
 * \file air-density.cpp
 * \brief Implementation of water density and volume correction calculations.
 *
 * This source file implements functions used to compute water density
 * and volume correction factors as functions of temperature.
 * The calculations are based on tabulated reference values and
 * linear or quadratic interpolation methods.
 *
 * \author Constantin
 * \date Creation date to be added
 */

#include "waterdensity.h"  // Header file for water density calculations

#include <cmath>  // Standard C++ math library

#include <QDebug>  // Qt debug/logging functions

#include "definitions.h"  // Project-specific constants and definitions

/**
 * \brief Discrete temperature reference points in degrees Celsius.
 *
 * This array contains integer temperature values from 0 °C to 100 °C inclusive.
 * The values are used as reference points for density and volume correction
 * interpolation.
 */
const double temperaturePoints[] = {
    0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
    17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0,
    34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0, 49.0, 50.0,
    51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0,
    68.0, 69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0, 81.0, 82.0, 83.0, 84.0,
    85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0, 93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0};

/**
 * \brief Reference water density values corresponding to temperaturePoints[].
 *
 * Each element represents the water density in kg/m³ at the corresponding
 * temperature from temperaturePoints[]. These values are used as input data
 * for interpolation-based density calculations.
 *
 * Note: The last value (101 °C) is included only to support interpolation
 * near the upper boundary.
 */
const double densityPoints[] = {
    999.8395, 999.8986, 999.9399, 999.9642, 999.9719, 999.9637, 999.9399, 999.9011, 999.8476, 999.7800, 999.6985,
    999.6036, 999.4957, 999.3752, 999.2422, 999.0972, 998.9404, 998.7721, 998.5925, 998.4020, 998.2009, 997.9891,
    997.7671, 997.5350, 997.2930, 997.0413, 996.7800, 996.5095, 996.2297, 995.9409, 995.6431, 995.3367, 995.0217,
    994.6982, 994.3665, 994.0266, 993.6786, 993.3229, 992.9594, 992.5883, 992.2097, 991.8257, 991.4321, 991.0313,
    990.6234, 990.2084, 989.7864, 989.3575, 988.9219, 988.4794, 988.0305, 987.5748, 987.1127, 986.6443, 986.1694,
    985.6883, 985.2010, 984.7075, 984.2079, 983.7023, 983.1908, 982.6733, 982.1500, 981.6209, 981.0861, 980.5455,
    979.9993, 979.4476, 978.8903, 978.3274, 977.7591, 977.1854, 976.6063, 976.0219, 975.4321, 974.8372, 974.2369,
    973.6316, 973.0211, 972.4054, 971.7847, 971.1589, 970.5281, 969.8923, 969.2515, 968.6058, 967.9552, 967.2997,
    966.6394, 965.9742, 965.3043, 964.6295, 963.9500, 963.2657, 962.5768, 961.8831, 961.1848, 960.4818, 959.7741,
    959.0618, 958.3449, 957.6451 /* 101°C just to be used for interpolation */
};

/**
 * \brief Volume correction factors as a function of temperature.
 *
 * This array contains volume correction coefficients corresponding to
 * temperatures from 0 °C to 100 °C. The factors are used to correct measured
 * volumes to a reference temperature.
 *
 * Note: The value at 101 °C exists only to allow safe interpolation at
 * the upper temperature limit.
 */
const double volumeCorrectionPoints[] =
    {
        1.00116, 1.00110, 1.00106, 1.00104, 1.00103, 1.00104, 1.00106, 1.00110, 1.00115, 1.00122, 1.00130, 1.00140,
        1.00151, 1.00163, 1.00176, 1.00190, 1.00206, 1.00223, 1.00241, 1.00260, 1.00280, 1.00302, 1.00324, 1.00347,
        1.00372, 1.00397, 1.00423, 1.00451, 1.00479, 1.00508, 1.00538, 1.00569, 1.00601, 1.00634, 1.00667, 1.00702,
        1.00737, 1.00773, 1.00810, 1.00847, 1.00886, 1.00925, 1.00965, 1.01006, 1.01047, 1.01090, 1.01133, 1.01177,
        1.01221, 1.01267, 1.01313, 1.01359, 1.01407, 1.01455, 1.01504, 1.01553, 1.01604, 1.01655, 1.01706, 1.01758,
        1.01811, 1.01865, 1.01919, 1.01974, 1.02030, 1.02086, 1.02143, 1.02200, 1.02259, 1.02317, 1.02377, 1.02437,
        1.02498, 1.02559, 1.02621, 1.02684, 1.02747, 1.02811, 1.02875, 1.02941, 1.03006, 1.03073, 1.03140, 1.03207,
        1.03276, 1.03344, 1.03414, 1.03484, 1.03555, 1.03626, 1.03698, 1.03770, 1.03844, 1.03917, 1.03992, 1.04067,
        1.04142, 1.04219, 1.04295, 1.04373, 1.04451, 1.04530 /* 101°C just to be used for interpolation */
};

/**
 * \brief Computes water density using linear interpolation.
 *
 * This function estimates the water density at a given temperature by
 * performing linear interpolation between adjacent reference points.
 * A correction term is applied relative to the density at 20 °C.
 *
 * \param temperature Temperature in degrees Celsius.
 * \param correction  Reference correction value applied at 20 °C.
 * \return Interpolated and corrected water density in kg/m³.
 *
 * Temperatures outside the supported range return predefined default values.
 */
double getWaterDensityAtTemperature(double temperature, double correction) {
    // Check if temperature is below 0 or above 100
    if (temperature <= MIN_TEMPERATURE) {
        return DEFAULT_DENSITY_BELOW_ZERO;
    }
    if (temperature >= MAX_TEMPERATURE) {
        return DEFAULT_DENSITY_ABOVE_HUNDRED;
    }

    // Find the index for interpolation
    size_t index = static_cast<size_t>(std::floor(temperature));

    // Validate array index - ensure we can safely access densityPoints[index + 1]
    // densityPoints has 102 elements (0-101), so we need index + 1 <= 101, i.e., index <= 100
    constexpr size_t densityArraySize = sizeof(densityPoints) / sizeof(densityPoints[0]);
    if (index >= densityArraySize - 1) {
        // Temperature too high for interpolation
        qWarning() << "WaterDensity: Index out of bounds for temperature" << temperature;
        return DEFAULT_DENSITY_ABOVE_HUNDRED;
    }

    // Perform linear interpolation
    double startTemperature = temperaturePoints[index];
    double startDensity = densityPoints[index];
    double stopDensity = densityPoints[index + 1];

    double density = startDensity + (stopDensity - startDensity) * (temperature - startTemperature);

    // Correct the water density based on a specific condition
    density = correction - densityPoints[20] + density;

    return density;
}

/**
 * \brief Estimates water density using quadratic interpolation.
 *
 * This function computes water density at the specified temperature using
 * quadratic Lagrange interpolation over three neighboring reference points.
 * The method provides smoother results compared to linear interpolation.
 *
 * \param temperature Temperature in degrees Celsius.
 * \return Estimated water density in kg/m³.
 *
 * For temperatures outside the valid range, predefined default densities
 * are returned. Array indices are clamped to prevent out-of-bounds access.
 */
double get_ro(double temperature) {
    // Handle temperatures outside the interpolation range by returning default densities
    if (temperature <= MIN_TEMPERATURE) {
        return DEFAULT_DENSITY_BELOW_ZERO;
    }
    if (temperature >= MAX_TEMPERATURE) {
        return DEFAULT_DENSITY_ABOVE_HUNDRED;
    }

    // Clamp the base temperature index (t0) to ensure safe indexing for quadratic interpolation
    // We subtract 3 because we use t0, t0+1, and t0+2 indices from densityPoints

    constexpr size_t densityPointCount = sizeof(densityPoints) / sizeof(densityPoints[0]);

    double t0 = std::min(std::floor(temperature), static_cast<double>(densityPointCount - 3));
    double t1 = t0 + 1;
    double t2 = t0 + 2;

    // Convert clamped temperatures to indices for densityPoints array access
    size_t i0 = static_cast<size_t>(t0);
    size_t i1 = static_cast<size_t>(t1);
    size_t i2 = static_cast<size_t>(t2);

    // Retrieve density values at the three surrounding temperature points
    double d0 = densityPoints[i0];
    double d1 = densityPoints[i1];
    double d2 = densityPoints[i2];

    // Compute the quadratic interpolation using the Lagrange polynomial formula
    double density = 0.5 * d0 * (temperature - t1) * (temperature - t2) - d1 * (temperature - t0) * (temperature - t2) +
                     0.5 * d2 * (temperature - t0) * (temperature - t1);

    return density;
}

/**
 * \brief Computes the volume correction factor using quadratic interpolation.
 *
 * This function evaluates the volume correction factor at the given temperature
 * using quadratic Lagrange interpolation based on three adjacent reference
 * values from the volumeCorrectionPoints[] table.
 *
 * \param temperature Temperature in degrees Celsius.
 * \return Interpolated volume correction factor.
 *
 * If the temperature lies outside the supported range, predefined default
 * correction factors are returned.
 */
double get_K(double temperature) {
    if (temperature <= MIN_TEMPERATURE) {
        return DEFAULT_VOLUME_CORRECTION_BELOW_ZERO;
    }
    if (temperature >= MAX_TEMPERATURE) {
        return DEFAULT_VOLUME_CORRECTION_ABOVE_HUNDRED;
    }

    // Use floor to get the lower bound of the interval
    int index = static_cast<int>(std::floor(temperature));

    // Ensure index - 1, index, index + 1 are valid
    if (index < 1) {
        index = 1;  // shift to allow index-1 access
    } else if (index > static_cast<int>(sizeof(volumeCorrectionPoints) / sizeof(volumeCorrectionPoints[0])) - 2) {
        index = static_cast<int>(sizeof(volumeCorrectionPoints) / sizeof(volumeCorrectionPoints[0])) - 2;
    }

    double x0 = index - 1;
    double x1 = index;
    double x2 = index + 1;

    double y0 = volumeCorrectionPoints[static_cast<size_t>(x0)];
    double y1 = volumeCorrectionPoints[static_cast<size_t>(x1)];
    double y2 = volumeCorrectionPoints[static_cast<size_t>(x2)];

    // Lagrange interpolation formula
    double t = temperature;

    double L0 = ((t - x1) * (t - x2)) / ((x0 - x1) * (x0 - x2));
    double L1 = ((t - x0) * (t - x2)) / ((x1 - x0) * (x1 - x2));
    double L2 = ((t - x0) * (t - x1)) / ((x2 - x0) * (x2 - x1));

    double interpolated = y0 * L0 + y1 * L1 + y2 * L2;

    return interpolated;
}
