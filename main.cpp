#include <iostream>
#include <fstream>

#include "Utils.h"
#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

Color RayColor(const Ray &ray, const HittableList &world) {
    HitRecord record;
    if (world.Hit(ray, Interval(0, Infinity), record))
        return 0.5 * (record.normal + Color(1.0, 1.0, 1.0)); // 如果光线击中物体，返回物体表面法向量的颜色

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

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Render
    std::ofstream outputFile("image.ppm");
    outputFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; ++j) {
        std::clog << "\rScanline's remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            Point3 pixelCenter = pixelOrigin + i * pixelDelta_X + j * pixelDelta_Y;
            Vec3 rayDirection = Normalize(pixelCenter - cameraCenter);
            Ray ray(cameraCenter, rayDirection);
            Color pixelColor = RayColor(ray, world);
            WriteColor(outputFile, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
    outputFile.close();
    return 0;
}
