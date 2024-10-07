#include "Renderer.h"
#include "Framebuffer.h"

// GitHub: https://github.com/TroikNardimos/GAT350

int main(int argc, char* argv[])
{
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Game Engine", 800, 600);

    Framebuffer framebuffer(renderer, 800, 600);

    bool quit = false;
    while (!quit)
    {
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
        //for (int i = 0; i < 10; i++)
        //{
        //    int x = rand() % framebuffer.m_width;
        //    int y = rand() % framebuffer.m_height;
        //    int x2 = rand() % framebuffer.m_width;
        //    int y2 = rand() % framebuffer.m_height;
        //    int x3 = rand() % framebuffer.m_width;
        //    int y3 = rand() % framebuffer.m_height;
        //    //framebuffer.DrawPoint(x, y, { 255,255,255,255 });
        //    //framebuffer.DrawRect(10,10,100,100, {0,255,0,255});
        //    //framebuffer.DrawLine(x, y, x2, y2, { (uint8_t)(rand() % 255),(uint8_t)(rand() % 255),(uint8_t)(rand() % 255), 255 });
        //    framebuffer.DrawTriangle(x, y, x2, y2, x3, y3, { (uint8_t)(rand() % 255),(uint8_t)(rand() % 255),(uint8_t)(rand() % 255), 255 });
        //}

        framebuffer.DrawLine(100, 100, 200, 200, { 255,0,0,255 });
        framebuffer.DrawRect(500, 100, 100, 100, { 255,255,0,255 });
        framebuffer.DrawCircle(200, 400, 100, { 0,255,0,255 });
        framebuffer.DrawTriangle(500, 400, 600, 400, 550, 500, { 0,0,255,255 });


        framebuffer.Update();

        renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }
	return 0;
}