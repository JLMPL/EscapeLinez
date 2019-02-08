#include "Game.hpp"
#include "ConfigFile.hpp"
#include "Mouse.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Multiplayer.hpp"
#include "Settings.hpp"
#include "Singleplayer.hpp"
#include "WaitingRoom.hpp"
#include "Renderer.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>

Game::Game()
{
    initSDL();

    setState(StateType::Menu);
}

Game::~Game()
{
    if (m_currState)
        m_currState->quit();

    delete m_currState;

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::initSDL()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    GlobalConfigFile.load();

    auto flags = SDL_WINDOW_SHOWN;

    if (GlobalConfigFile.isFullscreen())
        flags = SDL_WINDOW_FULLSCREEN;

    m_window = SDL_CreateWindow(
        "Escape Lines",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        GlobalConfigFile.getWidth(),
        GlobalConfigFile.getHeight(),
        flags
    );
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    GlobalRenderer = m_renderer;
}

void Game::run()
{
    while (m_open)
    {
        while (SDL_PollEvent(&m_event))
        {
            processEvent(m_event);
        }

        update();
        draw();
    }
}

void Game::processEvent(const SDL_Event& event)
{
    if (event.type == SDL_QUIT)
    {
        m_open = false;
    }
    else if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                m_open = false;
                break;
            case SDLK_BACKSPACE:
            {
                if (m_currState->getType() != StateType::Login)
                    setState(StateType::Menu);
            }
            break;
        }
    }

    m_currState->processEvent(m_event);
}

void Game::update()
{
    m_prevTime = m_currTime;
    m_currTime = SDL_GetTicks();
    m_deltaTime = (m_currTime - m_prevTime) / 1000.f;

    GlobalMouse.update();

    SDL_RenderClear(m_renderer);

    if (m_currState->nextState() != StateType::None)
    {
        setState(m_currState->nextState());
    }

    m_currState->update(m_deltaTime);
}

void Game::draw()
{
    SDL_RenderPresent(m_renderer);
}

void Game::setState(StateType type)
{
    if (m_currState)
        m_currState->quit();

    delete m_currState;

    switch (type)
    {
        case StateType::Menu:
            m_currState = new Menu();
            break;
        case StateType::Singleplayer:
            m_currState = new Singleplayer();
            break;
        case StateType::Multiplayer:
            m_currState = new Multiplayer();
            break;
        case StateType::Settings:
            m_currState = new Settings();
            break;
        case StateType::WaitingRoom:
            m_currState = new WaitingRoom();
            break;
        case StateType::Login:
            m_currState = new Login();
            break;
    }

    m_currState->init(m_window, m_renderer);
}
