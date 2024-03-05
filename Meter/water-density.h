
#ifndef WATERDENSITY_H
#define WATERDENSITY_H

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

// Determining the volume when determining the weight
// of the air from the water and the steel weights
//   - temperature: The temperature for correction
// This has to be documented.
double quadraticInterpolationVolumeCorrection(double temperature);

#endif // WATERDENSITY_H
