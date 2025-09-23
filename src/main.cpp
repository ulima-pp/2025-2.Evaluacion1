#include "file_management.h"
#include "colisiones.h"
#include <string>
#include <spdlog/spdlog.h>
#include <tuple>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>
#include <glm/vec2.hpp>

struct Megaman
{
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    Rectangulo box;
    SDL_Texture* textura;
};

std::vector<Megaman> SpawnearMegamans(int cantidad, SDL_Texture* textura, float ancho, float alto)
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
            { 
                {ancho, alto},
                {
                    x + ancho / 2.f,
                    y + alto / 2.f
                }
            },
            textura
        };
        listadoMegamans.push_back(m);
        //listadoMegamans.emplace_back(x, y, vx, vy, textura);
    }

    return listadoMegamans;
}

void VerificarColisiones(std::vector<Megaman>& listaMegamans)
{
    for (size_t i = 0; i < listaMegamans.size(); ++i)
    {
        Megaman& a = listaMegamans[i];

        for (size_t j = i + 1; j < listaMegamans.size(); ++j)
        {
            Megaman& b = listaMegamans[j];

            //spdlog::info("Hubo colision: A({},{}) B({},{})", 
            //        a.box.centerPosition.x, a.box.centerPosition.y, b.box.centerPosition.x, b.box.centerPosition.y);
            
            if (ColisionRectangular(a.box, b.box))
            {
                a.velocidadX *= -1;
                a.velocidadY *= -1;
                b.velocidadX *= -1;
                b.velocidadY *= -1;
            }
        }
    }
}

int main()
{
    

    //spdlog::info("Cantidad: {}", std::get<0>(data));
    //spdlog::info("Ubicacion Imagen: {}", std::get<1>(data));
    

    auto listadoMegamans = SpawnearMegamans(cantidad,texture, ancho, alto);

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
            m.box.centerPosition.x += m.velocidadX*deltatime;
            m.box.centerPosition.y += m.velocidadY*deltatime;
        }

        VerificarColisiones(listadoMegamans);

        millisecsPreviousFrame = SDL_GetTicks();

        // Renderer
        SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
        SDL_RenderClear(m_Renderer);

        for (const Megaman& m : listadoMegamans)
        {
            SDL_FRect megamanRect = { 
                m.posX, 
                m.posY, 
                m.box.anchoAlto.x, 
                m.box.anchoAlto.y 
            };
            SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
            SDL_RenderRect(m_Renderer, &megamanRect);
            SDL_RenderTexture(m_Renderer, texture, nullptr, &megamanRect);
        }

        SDL_RenderPresent(m_Renderer);
    }

    return 0;
}