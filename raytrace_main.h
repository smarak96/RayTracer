#ifndef RAYTRACE_MAIN_H
#define RAYTRACE_MAIN_H

#include <cmath>
#include<iostream>
#include<limits>
#include<memory>
#include<random>
using namespace std;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees*pi/180.0;
}
inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0,1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

#include "color.h"
#include "ray_class.h"
#include "vec_class.h"
#include "interval.h"
#endif