/**
 * \file waterdensity.h
 * \brief Header file for water density calculations.
 *
 * This file defines functions for calculating water density and related corrections.
 *
 * \author Constantin
 * \date Insert date
 */

#ifndef WATERDENSITY_H
#define WATERDENSITY_H

/**
 * \brief Performs linear interpolation for temperature correction.
 *
 * Given a temperature and a correction factor, this function performs linear interpolation
 * to adjust the correction factor based on the temperature.
 *
 * \param temperature The temperature for correction.
 * \param correction The correction factor to be adjusted.
 * \return Adjusted correction factor based on linear interpolation.
 */
double linearInterpolationTemperature(double temperature,
                                      double correction);

/**
 * \brief Performs quadratic interpolation for temperature correction.
 *
 * Given a temperature and a correction factor, this function performs quadratic interpolation
 * to adjust the correction factor based on the temperature.
 *
 * \param temperature The temperature for correction.
 * \param correction The correction factor to be adjusted.
 * \return Adjusted correction factor based on quadratic interpolation.
 */
double quadraticInterpolationTemperature(double temperature,
                                         double correction);

/**
 * \brief Calculates the volume correction using quadratic interpolation.
 *
 * This function determines the volume correction factor based on the temperature
 * using quadratic interpolation. The exact formula and parameters are specific
 * to the application's requirements.
 *
 * \param temperature The temperature for which the volume correction is calculated.
 * \return Volume correction factor based on quadratic interpolation.
 */
double quadraticInterpolationVolumeCorrection(double temperature);

#endif // WATERDENSITY_H
