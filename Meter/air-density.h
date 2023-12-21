/*
 *  Author: Constantin
 *  File:   air-density.h
 */

#ifndef DENSITY_H
#define DENSITY_H

// Linear interpolation for temperature correction
// Parameters:
//   - temperature: The temperature for correction
//   - correction: The correction factor
double linearInterpolationTemperature(double temperature,
                                      double correction);

// Quadratic interpolation for temperature correction
// Parameters:
//   - temperature: The temperature for correction
//   - correction: The correction factor
double quadraticInterpolationTemperature(double temperature,
        double correction);


#endif // DENSITY_H
