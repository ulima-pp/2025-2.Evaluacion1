#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <tuple>
#include "file_management.h"

class Game
{
    private:
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_Texture;

    public:
        bool Initialize();
        void ProcessInput();
        void Update();
        void Render();
};