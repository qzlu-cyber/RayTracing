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
#include "Material.h"
#include "Scene.h"

class Renderer {
public:
    Renderer() = default;

    explicit Renderer(int samplesPerPixel, int depth);

    ~Renderer();

    void Render(int width, int height, Camera camera, const Scene &scene);

private:
    Color RayColor(const Ray &ray, const Scene &scene);

    static double GammaCorrection(double linearColor);

    void WriteColor(const Color &pixelColor);

private:
    std::ofstream m_Out;
    int m_SamplesPerPixel; // 每个像素的采样次数
    int m_Depth; // 光线弹射次数
};

#endif //RAYTRACING_RENDERER_H
