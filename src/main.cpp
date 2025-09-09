#include "file_management.h"
#include <string>
#include <spdlog/spdlog.h>
#include <tuple>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>

struct Megaman
{
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    SDL_Texture* textura;
};

std::vector<Megaman> SpawnearMegamans(int cantidad, SDL_Texture* textura)
{
    std::random_device rd; // A non-deterministic seed source
    std::mt19937 gen(rd()); // The random number engine

    std::uniform_real_distribution<float> randomPositionX(0.f, 800.f);
    std::uniform_real_distribution<float> randomPositionY(0.f, 600.f);
    std::uniform_real_distribution<float> randomVelocityX(-100.f, 100.f);
    std::uniform_real_distribution<float> randomVelocityY(-100.f, 100.f);

    std::vector<Megaman> listadoMegamans{};
    for (int i=0; i < cantidad; i++)
    {
        float x = randomPositionX(gen);
        float y = randomPositionY(gen);
        float vx = randomVelocityX(gen);
        float vy = randomVelocityY(gen);
        Megaman m = {
            x,
            y,
            vx,
            vy,
            textura
        };
        listadoMegamans.push_back(m);
        //listadoMegamans.emplace_back(x, y, vx, vy, textura);
    }

    return listadoMegamans;
}

int main()
{
    auto data = ReadFromConfigFile("./assets/data.json");
    if (std::get<0>(data) == 0)
    {
        return 1;
    }
    const int cantidad = std::get<0>(data);
    const std::string rutaImagen = std::get<1>(data);

    //spdlog::info("Cantidad: {}", std::get<0>(data));
    //spdlog::info("Ubicacion Imagen: {}", std::get<1>(data));
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        spdlog::error("Error initializing SDL. ");
        return -1;
    }

    SDL_Window* m_Window = SDL_CreateWindow(
        nullptr, 
        800,
        600,
        SDL_WINDOW_BORDERLESS
    );

    if (!m_Window)
    {
        spdlog::error("Error creating SDL window.");
        return -1;
    }

    SDL_Renderer* m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if (!m_Renderer)
    {
        spdlog::error("Error creating Renderer window.");
        return -1;
    }

    SDL_SetWindowFullscreen(m_Window, true);

    SDL_Surface* megamanSurface = IMG_Load(rutaImagen.c_str());
    if (megamanSurface == nullptr)
    {
        spdlog::error("Error loading image.");
        return -2;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, megamanSurface);
    SDL_DestroySurface(megamanSurface);

    auto listadoMegamans = SpawnearMegamans(cantidad,texture);

    bool isRunning = true;
    auto millisecsPreviousFrame = SDL_GetTicks();
    while (isRunning)
    {
        // Getting Input data from player
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    isRunning = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (!event.key.repeat &&
                        event.key.key == SDLK_ESCAPE) 
                    {
                        isRunning = false;
                    }
                    break;
            }
        }

        double deltatime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

        // Updating
        for (Megaman& m : listadoMegamans)
        {
            if (m.posX + m.velocidadX*deltatime < 0.f ||
                m.posX + m.velocidadX*deltatime > 800.f)
            {
                m.velocidadX *= -1.f;
            }
            if (m.posY + m.velocidadY*deltatime < 0.f ||
                m.posY + m.velocidadY*deltatime > 600.f)
            {
                m.velocidadY *= -1.f;
            }
            m.posX += m.velocidadX*deltatime;
            m.posY += m.velocidadY*deltatime;
        }
        millisecsPreviousFrame = SDL_GetTicks();

        // Renderer
        SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
        SDL_RenderClear(m_Renderer);

        for (const Megaman& m : listadoMegamans)
        {
            SDL_FRect megamanRect = { 
                m.posX, 
                m.posY, 
                30.f, 
                34.f 
            };
            SDL_RenderTexture(m_Renderer, texture, nullptr, &megamanRect);
        }

        SDL_RenderPresent(m_Renderer);
    }

    return 0;
}