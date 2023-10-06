#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

double HitSphere(const Point3 &sphereCenter, double sphereRadius, const Ray &ray) {
    Vec3 oc = ray.Origin() - sphereCenter; // 球心到光线原点的向量
    double a = Dot(ray.Direction(), ray.Direction());
    double b = 2.0 * Dot(oc, ray.Direction());
    double c = Dot(oc, oc) - sphereRadius * sphereRadius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;
    else
        return (-b - std::sqrt(discriminant)) / (2.0 * a); // 返回最近的交点
}

Color RayColor(const Ray &ray) {
    double p = HitSphere(Point3(0, 0, -1), 0.5, ray);
    if (p != -1.0) { // 如果有交点
        Vec3 normal = Normalize(ray.At(p) - Vec3(0, 0, -1)); // 光线和球体的焦点的法向量
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1); // 将法向量映射到 [0, 1] 作为颜色
    }

    Vec3 unitDirection = Normalize(ray.Direction());
    double t = 0.5 * (unitDirection.y() + 1.0); // 将 [-1, 1] 映射到 [0, 1]

    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // 线性插值
}

int main() {
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 1920;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Viewport
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    // Camera
    double focalLength = 1.0;
    Point3 cameraCenter = {0, 0, 0};

    // Viewport coordinate system, the origin is in the upper left corner
    Vec3 viewport_X = {viewportWidth, 0, 0}; // 视口坐标系的 X 轴
    Vec3 viewport_Y = {0, -viewportHeight, 0}; // 视口坐标系的 -Y 轴
    Vec3 pixelDelta_X = viewport_X / imageWidth; // 每个像素的宽度
    Vec3 pixelDelta_Y = viewport_Y / imageHeight; // 每个像素的高度

    // Calculate the location of the upper left pixel
    Point3 viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewport_X / 2 - viewport_Y / 2; // 视口左上角坐标
    Point3 pixelOrigin = viewportUpperLeft + 0.5 * (pixelDelta_X + pixelDelta_Y); // 第一个像素的中心

    std::ofstream outputFile("image.ppm");

    // Render
    outputFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; ++j) {
        std::clog << "\rScanline's remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            Point3 pixelCenter = pixelOrigin + i * pixelDelta_X + j * pixelDelta_Y;
            Vec3 rayDirection = pixelCenter - cameraCenter;
            Ray ray(pixelCenter, rayDirection);
            Color pixelColor = RayColor(ray);
            WriteColor(outputFile, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
    outputFile.close();
    return 0;
}
