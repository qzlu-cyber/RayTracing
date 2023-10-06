//
// Created by 94164 on 2023/10/6.
//
#include "Renderer.h"

Renderer::Renderer(int samplesPerPixel) : m_SamplesPerPixel(samplesPerPixel) {
    m_Out.open("image.ppm");
}

Renderer::~Renderer() {
    m_Out.close();
}

void Renderer::Render(int width, int height, Camera camera, const Hittable &world) {
    m_Out << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanline's remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < m_SamplesPerPixel; ++s) {
                Ray ray = camera.GetRay(i, j);
                pixelColor += RayColor(ray, world);
            }
            WriteColor(pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
}

Color Renderer::RayColor(const Ray &ray, const Hittable &world) {
    HitRecord record;
    if (world.Hit(ray, Interval(0, Infinity), record))
        return 0.5 * (record.normal + Color(1.0, 1.0, 1.0)); // 如果光线击中物体，返回物体表面法向量的颜色

    Vec3 unitDirection = Normalize(ray.Direction());
    double t = 0.5 * (unitDirection.y() + 1.0); // 将 [-1, 1] 映射到 [0, 1]

    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // 线性插值
}

void Renderer::WriteColor(Color pixelColor) {
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    // Divide the color by the number of samples.
    double scale = 1.0 / m_SamplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    static const Interval range(0.0, 0.999); // 限制颜色分量的范围在 [0, 1)
    m_Out << static_cast<int>(256 * range.Clamp(r)) << ' '
          << static_cast<int>(256 * range.Clamp(g)) << ' '
          << static_cast<int>(256 * range.Clamp(b)) << '\n';

}

