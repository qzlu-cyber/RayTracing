//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_UTILS_H
#define RAYTRACING_UTILS_H

#include <cmath>
#include <limits>
#include <memory>

// Constants
const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions
inline double DegreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

#endif //RAYTRACING_UTILS_H
