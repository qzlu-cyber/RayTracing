#include <chrono>

#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"
#include "Material.h"
#include "Scene.h"

int main() {
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 1920;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    Camera camera(imageWidth, imageHeight, 20.0, 0.6, 10);

    // Materials
    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));

    // World
    std::shared_ptr<HittableList> world = std::make_shared<HittableList>();
    (*world).Add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

    for (int i = -11; i < 11; ++i) {
        for (int j = -11; j < 11; ++j) {
            double chooseMaterial = RandomDouble();
            Point3 center(i + 0.9 * RandomDouble(), 0.2, j + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMaterial < 0.8) {
                    // Diffuse
                    Color albedo = Color::Random() * Color::Random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    Point3 center2 = center + Vec3(0, RandomDouble(0, 0.5), 0);
                    (*world).Add(std::make_shared<Sphere>(center, center2, 0.2, sphereMaterial));
                } else if (chooseMaterial < 0.95) {
                    // Specular
                    Color albedo = Color::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<Specular>(albedo, fuzz);
                    (*world).Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else {
                    // Glass
                    sphereMaterial = std::make_shared<Dielectric>(1.5);
                    (*world).Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    (*world).Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    (*world).Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Specular>(Color(0.7, 0.6, 0.5), 0.0);
    (*world).Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    // Scene
    Scene scene(world);
    scene.BuildBVH();

    // Render
    Renderer renderer(100, 10);

    auto start = std::chrono::system_clock::now();
    renderer.Render(imageWidth, imageHeight, camera, scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

    return 0;
}
