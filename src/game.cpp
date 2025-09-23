#include "game.h"

bool Game::Initialize()
{
    // TODO: Improve data loading...
    auto data = ReadFromConfigFile("./assets/data.json");
    if (std::get<0>(data) == 0)
    {
        spdlog::error("Error loading data file.");
        return false;
    }
    const int cantidad = std::get<0>(data);
    const std::string rutaImagen = std::get<1>(data);
    float ancho = std::get<2>(data);
    float alto = std::get<3>(data);


    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        spdlog::error("Error initializing SDL. ");
        return false;
    }

    m_Window = SDL_CreateWindow(
        nullptr, 
        800,
        600,
        SDL_WINDOW_BORDERLESS
    );

    if (!m_Window)
    {
        spdlog::error("Error creating SDL window.");
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if (!m_Renderer)
    {
        spdlog::error("Error creating Renderer window.");
        return false;
    }

    SDL_SetWindowFullscreen(m_Window, true);

    SDL_Surface* megamanSurface = IMG_Load(rutaImagen.c_str());
    if (megamanSurface == nullptr)
    {
        spdlog::error("Error loading image.");
        return false;
    }
    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, megamanSurface);
    SDL_DestroySurface(megamanSurface);

    return true;
}

void Game::ProcessInput()
{
}

void Game::Update()
{
}

void Game::Render()
{
}
