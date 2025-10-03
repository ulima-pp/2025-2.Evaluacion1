#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <tuple>
#include <random>
#include <string>
#include <glm/vec2.hpp>
#include "file_management.h"
#include "colisiones.h"

struct Megaman
{
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    Fisicas::Forma& box;
    SDL_Texture *textura;
};

class Game
{
    private:
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_Texture;
        int m_Cantidad;
        std::string m_RutaImagen;
        float m_Ancho;
        float m_Alto;
        bool m_IsRunning;
        std::vector<Megaman> m_ListadoMegamans;
        
        void ProcessInput();
        void Update(float deltatime);
        void Render();

    public:
        Game();
        bool Initialize();
        void Run();
};