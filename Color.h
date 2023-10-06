//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include <iostream>

#include "Vec3.h"

using Color = Vec3;

void WriteColor(std::ofstream &out, Color pixelColor) {
    out << static_cast<int>(255.999 * pixelColor.x()) << ' '
        << static_cast<int>(255.999 * pixelColor.y()) << ' '
        << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}

#endif //RAYTRACING_COLOR_H
