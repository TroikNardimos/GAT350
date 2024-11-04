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
    camera.SetView({ 5,3,5 }, { 0,0,0 });

    Scene scene;

    std::shared_ptr<Material> grey    = std::make_shared<Lambertian>(colour3_t{ 0.5f });
    std::shared_ptr<Material> black   = std::make_shared<Lambertian>(colour3_t{ 0.0f });
    std::shared_ptr<Material> white   = std::make_shared<Lambertian>(colour3_t{ 1.0f });
    std::shared_ptr<Material> red     = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.0f, 0.0f });
    std::shared_ptr<Material> orange  = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.5f, 0.0f });
    std::shared_ptr<Material> yellow  = std::make_shared<Lambertian>(colour3_t{ 1.0f, 1.0f, 0.0f });
    std::shared_ptr<Material> green   = std::make_shared<Lambertian>(colour3_t{ 0.0f, 1.0f, 0.0f });
    std::shared_ptr<Material> blue    = std::make_shared<Lambertian>(colour3_t{ 0.0f, 0.0f, 1.0f });
    std::shared_ptr<Material> magenta = std::make_shared<Lambertian>(colour3_t{ 1.0f, 0.0f, 1.0f });
    std::shared_ptr<Material> light   = std::make_shared<Emissive>(colour3_t{ 1.0f, 1.0f, 1.0f }, 5);
    std::shared_ptr<Material> clear   = std::make_shared<Dielectric>(colour3_t{ 1.0f, 1.0f, 1.0f }, 1.33f);

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
    
    //auto object1 = std::make_unique<Sphere>(glm::vec3{0.0f}, 3.0f, clear);
    //scene.AddObject(std::move(object1));

    //auto object2 = std::make_unique<Sphere>(glm::vec3{0.0f, 0.0f, -20.0f}, 3.0f, materials[3]);
    //scene.AddObject(std::move(object2));

    std::shared_ptr<Material> metal = std::make_shared<Metal>(colour3_t{0.9f}, 0.2f);
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, metal);
    scene.AddObject(std::move(plane));

    auto triangle = std::make_unique<Triangle>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 0, 2, 0 }, glm::vec3{ 2, 0, 0 }, materials[6]);
    //scene.AddObject(std::move(triangle));

    auto model = std::make_unique<Model>(materials[7]);
    model->Load("cube.obj");
    scene.AddObject(std::move(model));

    //framebuffer.Clear(ColourConvert(colour4_t{ 0, 0, 0, 1 }));

    scene.Render(framebuffer, camera, 50, 50);

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