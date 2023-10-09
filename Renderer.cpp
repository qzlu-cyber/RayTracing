//
// Created by 94164 on 2023/10/6.
//
#include "Renderer.h"

Renderer::Renderer(int samplesPerPixel, int depth) : m_SamplesPerPixel(samplesPerPixel), m_Depth(depth) {
    m_Out.open("image.ppm");
}

Renderer::~Renderer() {
    m_Out.close();
}

void Renderer::Render(int width, int height, Camera camera, const Scene &scene) {
    m_Out << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanline's remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < m_SamplesPerPixel; ++s) {
                Ray ray = camera.GetRay(i, j);
                pixelColor += RayColor(ray, scene);
            }
            WriteColor(pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
}

Color Renderer::RayColor(const Ray &ray, const Scene &scene) {
    if (m_Depth <= 0) {
        return {0, 0, 0};
    }

    HitRecord record;
    // 当光线与物体相交时，计算得出的交点 (record.point) 因为浮点数的精度可能会有一个微小的偏移
    // 这就可能导致反射的光线的原点可能偏离物体表面。如果光线的原点在物体表面之下，那么就会导致
    // 光线与物体再次相交，忽略与计算出的交点非常接近的命中点可以解决此问题。
    if (scene.Hit(ray, Interval(0.001, Infinity), record)) {
        Ray scattered ; // 反射光线
        Color attenuation; // 衰减

        if (record.material->Scatter(ray, record, attenuation, scattered)) {
            // 保存递归深度
            int depth = m_Depth;
            // 递归调用，每次递归深度减一
            --m_Depth;
            Color color = attenuation * RayColor(scattered, scene);
            // 恢复递归深度
            m_Depth = depth;

            return color;
        }
        return {0, 0, 0};
    }

    Vec3 unitDirection = Normalize(ray.Direction());
    double t = 0.5 * (unitDirection.y() + 1.0); // 将 [-1, 1] 映射到 [0, 1]

    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // 线性插值
}

void Renderer::WriteColor(const Color &pixelColor) {
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    // Divide the color by the number of samples.
    double scale = 1.0 / m_SamplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Gamma-correct for gamma=2.0.
    r = GammaCorrection(r);
    g = GammaCorrection(g);
    b = GammaCorrection(b);

    static const Interval range(0.0, 0.999); // 限制颜色分量的范围在 [0, 1)
    m_Out << static_cast<int>(256 * range.Clamp(r)) << ' '
          << static_cast<int>(256 * range.Clamp(g)) << ' '
          << static_cast<int>(256 * range.Clamp(b)) << '\n';

}

double Renderer::GammaCorrection(double linearColor) {
    return std::sqrt(linearColor);
}

