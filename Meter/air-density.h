/*
 *  Author: Constantin
 *  File:   air-density.h
 */

#ifndef DENSITY_H
#define DENSITY_H

// Linear interpolation for temperature correction
double linearInterpolationTemperature(double temperature,
                                      double correction);

// Quadratic interpolation for temperature correction
double quadraticInterpolationTemperature(double temperature,
        double correction);

#endif // DENSITY_H
