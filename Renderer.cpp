//
// Created by 94164 on 2023/10/6.
//
#include "Renderer.h"

std::ofstream Renderer::m_Out; // 静态成员变量必须在类外初始化

Renderer::Renderer() {
    Renderer::m_Out.open("image.ppm");
}

Renderer::~Renderer() {
    Renderer::m_Out.close();
}

void Renderer::Render(int width, int height, Camera camera, const Hittable &world) {
    Renderer::m_Out << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanline's remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            Point3 pixelCenter = camera.PixelOrigin() + i * camera.PixelDelta_X() + j * camera.PixelDelta_Y();
            Vec3 rayDirection = Normalize(pixelCenter - camera.Origin());
            Ray ray(camera.Origin(), rayDirection);
            Color pixelColor = RayColor(ray, world);
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
    Renderer::m_Out << static_cast<int>(255.999 * pixelColor.x()) << ' '
                    << static_cast<int>(255.999 * pixelColor.y()) << ' '
                    << static_cast<int>(255.999 * pixelColor.z()) << '\n';

}

