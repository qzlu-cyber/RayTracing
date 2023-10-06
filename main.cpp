#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"

int main() {
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 1920;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    Camera camera(imageWidth, imageHeight);

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Render
    Renderer renderer(100);
    renderer.Render(imageWidth, imageHeight, camera, world);

    return 0;
}
