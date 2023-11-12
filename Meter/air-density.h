/*
 *  Author: Constantin
 *  File:   air-density.cpp
 */

#ifndef DENSITY_H
#define DENSITY_H

double liniarInterpolationTemperature(double temperature,
                                      double correction);

double quadraticInterpolationTemperature(double temperature,
        double correction);

#endif // DENSITY_H
