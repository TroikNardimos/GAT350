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
#include "Actor.h"
#include "Random.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

// GitHub: https://github.com/TroikNardimos/GAT350

int main(int argc, char* argv[])
{
    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Input input;
    input.Initialize();
    input.Update();

    SetBlendMode(BlendMode::Normal);

    Camera camera{ renderer.m_width, renderer.m_height };
    camera.SetView(glm::vec3{0, 0, -50}, glm::vec3{0});
    camera.SetProjection(90.0f, (800.0f/600.0f), 0.1f, 200.0f);

    Transform cameraTransform{ {0,0,-20} };

    Framebuffer framebuffer(renderer, 800, 600);

    Image image;
    image.Load("landscape.jpg");

    Image imageAlpha;
    imageAlpha.Load("colours.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 100);

    //vertices_t vertices = { { -5, 5, 0 }, { 5, 5, 0 }, { -5, -5, 0 } };
    //Model model(vertices, { 0,255,0,255 });

    std::shared_ptr<Model> model1 = std::make_shared<Model>();
    std::shared_ptr<Model> model2 = std::make_shared<Model>();
    std::shared_ptr<Model> model3 = std::make_shared<Model>();
    model1->Load("cube.obj");
    model2->Load("cube.obj");
    model3->Load("cube.obj");
    model1->SetColour({ 255, 0, 0, 255 });
    model2->SetColour({ 0, 255, 0, 255 });
    model3->SetColour({ 0, 0, 255, 255 });

    std::vector<std::unique_ptr<Actor>> actors;

    Transform transform1{ {20.0f, 20.0f, 20.0f}, glm::vec3{0,0,0}, glm::vec3{3}};
    Transform transform2{ {20.0f, -20.0f, 20.0f}, glm::vec3{0,0,0}, glm::vec3{3}};
    Transform transform3{ {-20.0f, 20.0f, 20.0f}, glm::vec3{0,0,0}, glm::vec3{3}};
    std::unique_ptr<Actor> actor1 = std::make_unique<Actor>(transform1, model1);
    std::unique_ptr<Actor> actor2 = std::make_unique<Actor>(transform2, model2);
    std::unique_ptr<Actor> actor3 = std::make_unique<Actor>(transform3, model3);
    actor1->SetColour({ 255, 0, 0 });
    actor2->SetColour({ 0, 255, 0 });
    actor3->SetColour({ 0, 0, 255 });
    actors.push_back(std::move(actor1));
    actors.push_back(std::move(actor2));
    actors.push_back(std::move(actor3));


    bool quit = false;
    while (!quit)
    {
        time.Tick();
        input.Update();
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

        // clear screen
        //SDL_SetRenderDrawColor(renderer.m_renderer, 0, 0, 0, 0);
        //SDL_RenderClear(renderer.m_renderer);

        framebuffer.Clear(colour_t{0, 0, 0, 255});

        //int ticks = SDL_GetTicks();
        //float time = ticks * 0.001f;

#pragma region alpha_blend
        //SetBlendMode(BlendMode::Normal);
        //framebuffer.DrawImage(100, 100, image);
        //SetBlendMode(BlendMode::Multiply);
        //framebuffer.DrawImage(100, 100, imageAlpha);
#pragma endregion

#pragma region post_rocessing
        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColourBalance(framebuffer.m_buffer, 150, -50, -50);
        //PostProcess::Brightness(framebuffer.m_buffer, 100);
        //PostProcess::Noise(framebuffer.m_buffer, 100);
        //PostProcess::Threshhold(framebuffer.m_buffer, 100);
        //PostProcess::Posterize(framebuffer.m_buffer, 4);

        //for (int i = 0; i < 10; i++)
        //{
        //    PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //    PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //}
        
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 10);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
#pragma endregion

        if (input.GetMouseButtonDown(2))
        {
            input.SetRelativeMode(true);

            glm::vec3 direction{0};
            if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
            if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_W)) direction.y = 1;
            if (input.GetKeyDown(SDL_SCANCODE_S)) direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_Q)) direction.z = 1;
            if (input.GetKeyDown(SDL_SCANCODE_E)) direction.z = -1;

            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4 {direction, 0};

            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();
        }
        else
        {
            input.SetRelativeMode(false);
        }

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        //transform.rotation.z += 90 * time.GetDeltaTime();

        framebuffer.DrawImage(0, 0, image);

        for (auto& actor : actors)
        {
            actor->Draw(framebuffer, camera);
        }

        framebuffer.Update();

        renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }
	return 0;
}