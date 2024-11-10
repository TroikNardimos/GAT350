#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"
#include "Random.h"
#include "Tracer.h"
#include "Scene.h"
#include "Triangle.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Plane.h"

// GitHub: https://github.com/TroikNardimos/GAT350

void InitScene(Scene& scene);
void InitScene01(Scene& scene, Camera& camera);
void InitFinalScene(Scene& scene, Camera& camera);
void InitSceneCornell(Scene& scene, Camera& camera);

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));
    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("RayTracer", 800, 600);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_height);
    Camera camera{70, (framebuffer.m_width / (float)framebuffer.m_height)};
    camera.SetView({ 0,0,-20 }, { 0,0,0 });

    Scene scene;
    InitFinalScene(scene, camera);
    
    scene.Update();
    scene.Render(framebuffer, camera, 100, 10);
    framebuffer.Update();

    bool quit = false;
    while (!quit)
    {
        time.Tick();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        framebuffer.Update();

        renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }
	return 0;
}

void InitScene(Scene& scene)
{
    scene.SetSky(HSVToRGB(300, 1, 0.2f), HSVToRGB(300, 1, 1));

    std::shared_ptr<Material> grey = std::make_shared<Lambertian>(colour3_t{ 0.5f });
    std::shared_ptr<Material> black = std::make_shared<Lambertian>(colour3_t{ 0.0f });
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(colour3_t{ 1.0f });
    std::shared_ptr<Material> red = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.0f, 0.0f });
    std::shared_ptr<Material> orange = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.5f, 0.0f });
    std::shared_ptr<Material> yellow = std::make_shared<Lambertian>(colour3_t{ 1.0f, 1.0f, 0.0f });
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(colour3_t{ 0.0f, 1.0f, 0.0f });
    std::shared_ptr<Material> blue = std::make_shared<Lambertian>(colour3_t{ 0.0f, 0.0f, 1.0f });
    std::shared_ptr<Material> magenta = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.0f, 1.0f });
    std::shared_ptr<Material> light = std::make_shared<Emissive>(colour3_t{ 1.0f, 1.0f, 1.0f }, 5);
    std::shared_ptr<Material> clear = std::make_shared<Dielectric>(colour3_t{ 1.0f, 1.0f, 1.0f }, 1.33f);

    std::vector<std::shared_ptr<Material>> materials;

    materials.push_back(std::move(grey));
    materials.push_back(std::move(black));
    materials.push_back(std::move(white));
    materials.push_back(std::move(red));
    materials.push_back(std::move(orange));
    materials.push_back(std::move(yellow));
    materials.push_back(std::move(green));
    materials.push_back(std::move(blue));
    materials.push_back(std::move(magenta));
    //materials.push_back(std::move(light));

    auto object1 = std::make_unique<Sphere>(Transform{ glm::vec3{0, 0, 0} }, 3.0f, clear);
    //scene.AddObject(std::move(object1));

    auto object2 = std::make_unique<Sphere>(Transform{ glm::vec3{0, 0, -20} }, 3.0f, materials[3]);
    //scene.AddObject(std::move(object2));

    std::shared_ptr<Material> metal = std::make_shared<Metal>(colour3_t{ 0.9f }, 0.2f);
    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0,-5,0}, glm::vec3{0,0,0} }, metal);
    //scene.AddObject(std::move(plane));

    auto triangle = std::make_unique<Triangle>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 0, 2, 0 }, glm::vec3{ 2, 0, 0 }, materials[6]);
    //scene.AddObject(std::move(triangle));

    std::shared_ptr<Material> random = std::make_shared<Lambertian>(HSVToRGB(randomf(0, 360), 1.0f, 1.0f));
    auto model = std::make_unique<Model>(Transform{ glm::vec3{2,0,2}, glm::vec3{40,40,0}, glm::vec3{4} }, light);
    model->Load("Models/cube.obj");
    //scene.AddObject(std::move(model));

    //framebuffer.Clear(ColourConvert(colour4_t{ 0, 0, 0, 1 }));

}

void InitSceneCornell(Scene& scene, Camera& camera)
{
    //camera.SetView({ 0, 0, 20 }, { 0, 0, 0 });
    //scene.SetSky(HSVToRGB(240, 0, 0.5f), HSVToRGB(240, 0, 0.5f));

    std::shared_ptr<Material> white = std::make_shared<Lambertian>(colour3_t{ 1.0f });
    std::shared_ptr<Material> grey = std::make_shared<Lambertian>(colour3_t{ 0.5f });
    std::shared_ptr<Material> red = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.0f, 0.0f });
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(colour3_t{ 0.0f, 1.0f, 0.0f });
    std::shared_ptr<Material> light = std::make_shared<Emissive>(colour3_t{ 1.0f, 1.0f, 1.0f }, 50);
    std::shared_ptr<Material> metal = std::make_shared<Metal>(colour3_t{ 0.9f }, 0.2f);
    std::shared_ptr<Material> random = std::make_shared<Lambertian>(HSVToRGB(randomf(0, 360), 1.0f, 1.0f));

    auto sphere = std::make_unique<Sphere>(Transform{ glm::vec3{-5, -5, 0} }, 3.0f, grey);
    scene.AddObject(std::move(sphere));

    auto floor = std::make_unique<Plane>(Transform{ glm::vec3{0,-20,0}, glm::vec3{0,0,0} }, grey);
    scene.AddObject(std::move(floor));

    auto roof = std::make_unique<Plane>(Transform{ glm::vec3{0,20,0}, glm::vec3{0,0,0} }, grey);
    scene.AddObject(std::move(roof));

    auto lightSource = std::make_unique<Model>(Transform{ glm::vec3{0,20,30}, glm::vec3{0,0,0}, glm::vec3{10, 1, 10} }, light);
    lightSource->Load("Models/cube.obj");
    scene.AddObject(std::move(lightSource));

    auto back = std::make_unique<Plane>(Transform{ glm::vec3{0,0,50}, glm::vec3{90,0,0} }, grey);
    scene.AddObject(std::move(back));

    auto left = std::make_unique<Plane>(Transform{ glm::vec3{-30,0,0}, glm::vec3{0,0,90}}, red);
    scene.AddObject(std::move(left));

    auto right = std::make_unique<Plane>(Transform{ glm::vec3{30,0,0}, glm::vec3{0,0,90} }, green);
    scene.AddObject(std::move(right));

    auto model = std::make_unique<Model>(Transform{ glm::vec3{5,-5,0}, glm::vec3{0,-15,0}, glm::vec3{4} }, grey);
    model->Load("Models/cube.obj");
    scene.AddObject(std::move(model));
}

void InitScene01(Scene& scene, Camera& camera)
{
    camera.SetFOV(20.0f);
    camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

    auto ground_material = std::make_shared<Lambertian>(colour3_t(0.5f));
    scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomf();
            glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = HSVToRGB(randomf(0, 360), 1.0f, 1.0f);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = HSVToRGB(randomf(0, 360), 1.0f, 1.0f);
                    auto fuzz = randomf(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(colour3_t{ 1 }, 1.5f);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(colour3_t{ 1 }, 1.5f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(colour3_t(0.4f, 0.2f, 0.1f));
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));

    auto material3 = std::make_shared<Metal>(colour3_t(0.7f, 0.6f, 0.5f), 0.0f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
}

void InitFinalScene(Scene& scene, Camera& camera)
{
    camera.SetFOV(20.0f);
    camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

    auto ground_material = std::make_shared<Lambertian>(colour3_t(0.5f));
    scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomf();
            auto choose_shape = randomf();
            glm::vec3 center(a + 1.9 * randomf(), 0.2, b + 0.9 * randomf());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> material;

                if (choose_mat < 0.4) {
                    // diffuse
                    auto albedo = HSVToRGB(randomf(0, 360), 1.0f, 1.0f);

                    material = std::make_shared<Lambertian>(albedo);
                    if (choose_shape < 0.8)
                    {
                        scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, material));
                    }
                    else if (choose_shape < 0.95)
                    {
                        auto model = std::make_unique<Model>(Transform{ center }, material);
                        model->GetTransform().scale = glm::vec3{ 0.5f };
                        model->Load("Models/cube.obj");
                        scene.AddObject(std::move(model));
                    }
                    else
                    {
                        scene.AddObject(std::make_unique<Triangle>(
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            material)
                        );
                    }
                }
                else if (choose_mat < 0.8) {
                    // metal
                    auto albedo = HSVToRGB(randomf(0, 360), 1.0f, 1.0f);
                    auto fuzz = randomf(0.0f, 0.5f);
                    material = std::make_shared<Metal>(albedo, fuzz);
                    if (choose_shape < 0.8)
                    {
                        scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, material));
                    }
                    else if (choose_shape < 0.95)
                    {
                        auto model = std::make_unique<Model>(Transform{ center }, material);
                        model->Load("Models/cube.obj");
                        model->GetTransform().scale = glm::vec3{ 0.5f };
                        scene.AddObject(std::move(model));
                    }
                    else
                    {
                        scene.AddObject(std::make_unique<Triangle>(
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            material)
                        );
                    }
                }
                else {
                    // glass
                    material = std::make_shared<Dielectric>(colour3_t{ 1 }, 1.5f);
                    if (choose_shape < 0.8)
                    {
                        scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, material));
                    }
                    else if (choose_shape < 0.95)
                    {
                        auto model = std::make_unique<Model>(Transform{ center }, material);
                        model->Load("Models/cube.obj");
                        model->GetTransform().scale = glm::vec3{ 0.5f };
                        scene.AddObject(std::move(model));
                    }
                    else
                    {
                        scene.AddObject(std::make_unique<Triangle>(
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            glm::vec3{random(-2, 2), random(-2, 2), random(-2, 2)},
                            material)
                        );
                    }
                }
            }
        }
    }

    //auto material1 = std::make_shared<Dielectric>(colour3_t{ 1 }, 1.5f);
    //scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

    //auto material2 = std::make_shared<Lambertian>(colour3_t(0.4f, 0.2f, 0.1f));
    //scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));

    //auto material3 = std::make_shared<Metal>(colour3_t(0.7f, 0.6f, 0.5f), 0.0f);
    //scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
}