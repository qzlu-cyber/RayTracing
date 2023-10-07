#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"
#include "Material.h"

int main() {
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 1920;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    Camera camera(imageWidth, imageHeight);

    // Materials
    auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<Specular>(Color(0.8, 0.8, 0.8), 0.3);
    auto materialRight = std::make_shared<Specular>(Color(0.8, 0.6, 0.2), 1.0);

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, materialLeft));
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, materialCenter));
    world.Add(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, materialRight));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, materialGround));

    // Render
    Renderer renderer(100, 10);
    renderer.Render(imageWidth, imageHeight, camera, world);

    return 0;
}
