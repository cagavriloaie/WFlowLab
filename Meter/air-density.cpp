/*
 *  Author: Constantin
 *  File:   air-density.cpp
 */

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "air-density.h"

const double temperaturePoints[] =
{
    0.0,  1.0,  2.0,  3.0,  4.0,   5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0,
    12.0, 13.0, 14.0, 15.0, 16.0,  17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0,  29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0,
    36.0, 37.0, 38.0, 39.0, 40.0,  41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0,
    48.0, 49.0, 50.0, 51.0, 52.0,  53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0,
    60.0, 61.0, 62.0, 63.0, 64.0,  65.0, 66.0, 67.0, 68.0, 69.0, 70.0, 71.0,
    72.0, 73.0, 74.0, 75.0, 76.0,  77.0, 78.0, 79.0, 80.0, 81.0, 82.0, 83.0,
    84.0, 85.0, 86.0, 87.0, 88.0,  89.0, 90.0, 91.0, 92.0, 93.0, 94.0, 95.0,
    96.0, 97.0, 98.0, 99.0, 100.0, 101.
};

const double densityPoints[] =
{
    999.8395, 999.8986, 999.9399, 999.9642, 999.9719, 999.9637, 999.9399,
    999.9011, 999.8476, 999.7800, 999.6985, 999.6036, 999.4957, 999.3752,
    999.2422, 999.0972, 998.9404, 998.7721, 998.5925, 998.4020, 998.2009,
    997.9891, 997.7671, 997.5350, 997.2930, 997.0413, 996.7800, 996.5095,
    996.2297, 995.9409, 995.6431, 995.3367, 995.0217, 994.6982, 994.3665,
    994.0266, 993.6786, 993.3229, 992.9594, 992.5883, 992.2097, 991.8257,
    991.4321, 991.0313, 990.6234, 990.2084, 989.7864, 989.3575, 988.9219,
    988.4794, 988.0305, 987.5748, 987.1127, 986.6443, 986.1694, 985.6883,
    985.2010, 984.7075, 984.2079, 983.7023, 983.1908, 982.6733, 982.1500,
    981.6209, 981.0861, 980.5455, 979.9993, 979.4476, 978.8903, 978.3274,
    977.7591, 977.1854, 976.6063, 976.0219, 975.4321, 974.8372, 974.2369,
    973.6316, 973.0211, 972.4054, 971.7847, 971.1589, 970.5281, 969.8923,
    969.2515, 968.6058, 967.9552, 967.2997, 966.6394, 965.9742, 965.3043,
    964.6295, 963.9500, 963.2657, 962.5768, 961.8831, 961.1848, 960.4818,
    959.7741, 959.0618, 958.3449, 957.6451
};

double liniarInterpolationTemperature(double temperature,
                                      double correction)
{
    if (temperature <= 0.0)
    {
        return 999.8395;
    }
    if (temperature >= 100.0)
    {
        return 958.3449;
    }
    double startTemperature =
        temperaturePoints[static_cast<size_t>(std::floor(temperature))];
    double startDensity =
        densityPoints[static_cast<size_t>(std::floor(temperature))];
    double stopDensity =
        densityPoints[static_cast<size_t>(std::floor(temperature + 1))];
    double density = startDensity + (stopDensity - startDensity) *
                     (temperature - startTemperature);
    // Because same particular condition the water density has to be corrected
    density = correction - densityPoints[20] + density;
    return density;
}

double quadraticInterpolationTemperature(double temperature,
        double correction)
{
    if (temperature <= 0.0)
    {
        return 999.8395;
    }
    if (temperature >= 100.0)
    {
        return 958.3449;
    }
    double firstTemperature = std::floor(temperature);
    double secondTemperature = std::floor(temperature + 1);
    double thirdTemperature = std::floor(temperature + 2);
    double firstDensity = densityPoints[static_cast<size_t>
                                        (firstTemperature)];
    double secondDensity =
        densityPoints[static_cast<size_t>(secondTemperature)];
    double thirdDensity = densityPoints[static_cast<size_t>
                                        (thirdTemperature)];
    double density = 0.5 * firstDensity * (temperature -
                                           secondTemperature) *
                     (temperature - thirdTemperature) -
                     secondDensity * (temperature - firstTemperature) *
                     (temperature - thirdTemperature) +
                     0.5 * thirdDensity * (temperature - firstTemperature) *
                     (temperature - secondTemperature);
    // Because same particular condition the water density has to be corrected
    density = correction - densityPoints[20] + density;
    return density;
}
