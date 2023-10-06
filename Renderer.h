//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include <iostream>
#include <fstream>

#include "Ray.h"
#include "HittableList.h"
#include "Camera.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    static void Render(int width, int height, Camera camera, const Hittable &world);

private:
    static Color RayColor(const Ray &ray, const Hittable &world);
    static void WriteColor(Color pixelColor);

private:
    static std::ofstream m_Out;
};

#endif //RAYTRACING_RENDERER_H
