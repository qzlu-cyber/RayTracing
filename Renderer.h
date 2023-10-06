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
    Renderer() = default;
    explicit Renderer(int samplesPerPixel);
    ~Renderer();

    void Render(int width, int height, Camera camera, const Hittable &world);

private:
    static Color RayColor(const Ray &ray, const Hittable &world);
    void WriteColor(Color pixelColor);

private:
    std::ofstream m_Out;
    int m_SamplesPerPixel; // 每个像素的采样次数
};

#endif //RAYTRACING_RENDERER_H
