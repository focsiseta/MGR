#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}
vec3 sample_square() {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0.0);
}
vec3 random_vector() {
    return vec3{random_double(),random_double(),random_double()};
}
vec3 random_vector(double min, double max) {
    return vec3{random_double(min,max),random_double(min,max),random_double(min,max)};
}
vec3 randomUnitDir() {
    while (true) {
        //first we create a random vector
        vec3 rVector{random_vector(-1,1)};
        //we check if it's inside our unit sphere
        auto size = rVector.length_squared();
        //1e-160 to avoid rays that when normalized sqrooted become 0, returning vector of +-inf,+-inf,+-inf
        if (1e-160 < size && size <= 1.0) {
            //if it's a kool vector we return it normalized
            return unit_vector(rVector);
        }
    }
}
//Returns a normalized direction inside the
vec3 vectorInsideEmisphere(vec3& normal) {
    //!!!!!! Normal has to be passed normalized
    vec3 v = randomUnitDir();
    if (dot(v,normal) >= 0.0) {
        return v;
    }else {
        return -v;
    }
}


// Common Headers

#include "color.h"
#include "vec3.h"

#endif