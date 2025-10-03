#include "game.h"

std::vector<Megaman> SpawnearMegamans(int cantidad, SDL_Texture *textura, float ancho, float alto)
{
    std::random_device rd;  // A non-deterministic seed source
    std::mt19937 gen(rd()); // The random number engine

    std::uniform_real_distribution<float> randomPositionX(0.f, 800.f);
    std::uniform_real_distribution<float> randomPositionY(0.f, 600.f);
    std::uniform_real_distribution<float> randomVelocityX(-100.f, 100.f);
    std::uniform_real_distribution<float> randomVelocityY(-100.f, 100.f);

    std::vector<Megaman> listadoMegamans{};
    for (int i = 0; i < cantidad; i++)
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
            {{ancho, alto},
             {x + ancho / 2.f,
              y + alto / 2.f}},
            textura};
        listadoMegamans.push_back(m);
        // listadoMegamans.emplace_back(x, y, vx, vy, textura);
    }

    return listadoMegamans;
}

void VerificarColisiones(std::vector<Megaman> &listaMegamans)
{
    

    for (size_t i = 0; i < listaMegamans.size(); ++i)
    {
        Megaman &a = listaMegamans[i];

        for (size_t j = i + 1; j < listaMegamans.size(); ++j)
        {
            Megaman &b = listaMegamans[j];

            // spdlog::info("Hubo colision: A({},{}) B({},{})",
            //         a.box.centerPosition.x, a.box.centerPosition.y, b.box.centerPosition.x, b.box.centerPosition.y);

            
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

Game::Game()
    : m_Window(nullptr), m_Renderer(nullptr),
      m_Texture(nullptr), m_Cantidad(0),
      m_RutaImagen(""), m_Ancho(0.f),
      m_Alto(0.f), m_IsRunning(true),
      m_ListadoMegamans({})
{}

bool Game::Initialize()
{
    // TODO: Improve data loading...
    auto data = ReadFromConfigFile("./assets/data.json");
    if (std::get<0>(data) == 0)
    {
        spdlog::error("Error loading data file.");
        return false;
    }
    m_Cantidad = std::get<0>(data);
    m_RutaImagen = std::get<1>(data);
    m_Ancho = std::get<2>(data);
    m_Alto = std::get<3>(data);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        spdlog::error("Error initializing SDL. ");
        return false;
    }

    m_Window = SDL_CreateWindow(
        nullptr,
        800,
        600,
        SDL_WINDOW_BORDERLESS);

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

    SDL_Surface *megamanSurface = IMG_Load(m_RutaImagen.c_str());
    if (megamanSurface == nullptr)
    {
        spdlog::error("Error loading image.");
        return false;
    }
    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, megamanSurface);
    SDL_DestroySurface(megamanSurface);

    return true;
}

void Game::Run()
{
    m_ListadoMegamans = SpawnearMegamans(
        m_Cantidad,
        m_Texture,
        m_Ancho,
        m_Alto);

    auto millisecsPreviousFrame = SDL_GetTicks();
    while (m_IsRunning)
    {
        ProcessInput();

        double deltatime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

        Update(deltatime);

        millisecsPreviousFrame = SDL_GetTicks();

        Render();
    }
}

void Game::ProcessInput()
{
    // Getting Input data from player
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            m_IsRunning = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (!event.key.repeat &&
                event.key.key == SDLK_ESCAPE)
            {
                m_IsRunning = false;
            }
            break;
        }
    }
}

void Game::Update(float deltatime)
{
    // Updating
    for (Megaman &m : m_ListadoMegamans)
    {
        if (m.posX + m.velocidadX * deltatime < 0.f ||
            m.posX + m.velocidadX * deltatime > 800.f)
        {
            m.velocidadX *= -1.f;
        }
        if (m.posY + m.velocidadY * deltatime < 0.f ||
            m.posY + m.velocidadY * deltatime > 600.f)
        {
            m.velocidadY *= -1.f;
        }
        m.posX += m.velocidadX * deltatime;
        m.posY += m.velocidadY * deltatime;
        m.box.centerPosition.x += m.velocidadX * deltatime;
        m.box.centerPosition.y += m.velocidadY * deltatime;
    }

    VerificarColisiones(m_ListadoMegamans);
}

void Game::Render()
{
    // Renderer
    SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_Renderer);

    for (const Megaman &m : m_ListadoMegamans)
    {
        SDL_FRect megamanRect = {
            m.posX,
            m.posY,
            m.box.anchoAlto.x,
            m.box.anchoAlto.y};
        SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
        SDL_RenderRect(m_Renderer, &megamanRect);
        SDL_RenderTexture(m_Renderer, m_Texture, nullptr, &megamanRect);
    }

    SDL_RenderPresent(m_Renderer);
}
