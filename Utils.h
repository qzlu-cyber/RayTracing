//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_UTILS_H
#define RAYTRACING_UTILS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants
const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions
inline double DegreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

inline double RandomDouble() {
    // Returns a random real in [0, 1).
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max) {
    // Returns a random real in [min, max).
    return min + (max - min) * RandomDouble();
}

#endif //RAYTRACING_UTILS_H
