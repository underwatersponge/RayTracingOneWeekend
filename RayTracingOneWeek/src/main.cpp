
#include "shape/Sphere.h"
#include "shape/HitTableList.h"
#include "cam/Camera.h"
#include "mat/Lambertian.h"
#include "mat/Metal.h"
#include "mat/Dielectric.h"
#include <filesystem>

//#define under

int main() {
	// scene
	HitTableList scene;

#ifdef under

	// ================================== sample scene ================================//
	auto materialGround = std::make_shared<Lambertian>(Color(0.3, 0.3, 0.0));
	auto materialCenter= std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto materialLeft = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
	auto materialLeft = std::make_shared<Dielectric>(1.00 / 1.33);
	auto materialLeft = std::make_shared<Dielectric>(1.50);
	auto materialBubble= std::make_shared<Dielectric>(1.0 / 1.50);
	auto materialRight = std::make_shared<Metal>(Color(1.0, 1.0, 0.2), 0.1);

	scene.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	scene.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.6, materialCenter));
	scene.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	scene.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, materialBubble));
	scene.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.2), 0.5, materialRight));

	Camera camera;
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;
	camera.maxDepth = 20;

	camera.fov = 73;
	camera.lookFrom = { -2.0, 2.0, 1.0 };
	camera.lookAt = { 0.0, 0.0, -1.0 };
	camera.vup = { 0.0, 1.0, 0.0 };
	
	camera.defocusAngle = 10.0;
	camera.focusDist = 3.4;
	// ========================== ========================= // 
#else
    // ========================== ============================//
    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    scene.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randFloat();
            Point3 center(a + 0.9 * randFloat(), 0.2, b + 0.9 * randFloat());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center2 = center + Vec3(0.0, randFloat(0, 0.5), 0);
                    scene.add(std::make_shared<Sphere>(center, center2, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randFloat(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    scene.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    scene.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    scene.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 200;
    camera.samplesPerPixel = 20;
    camera.maxDepth = 20;

    camera.fov = 20;
    camera.lookFrom = Point3(13, 2, 3);
    camera.lookAt = Point3(0, 0, 0);
    camera.vup = Vec3(0, 1, 0);

    camera.defocusAngle = 0.6;
    camera.focusDist = 10.0;
#endif // DEBUG
    // ====================== ======================== //

    std::string fileName = "image.ppm";
    std::ofstream file(fileName);

	camera.render(file, scene);

	std::cout << "\rDone. ===================== \n";

	return 0;
}
