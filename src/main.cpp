/*#include <cstdlib>
#include <time.h>
#include <iostream>
#include <math.h>
#include <SFML/Network.hpp>
#include "Multiplayer.hpp"
#include "Singleplayer.hpp"
#include "Menu.hpp"
#include "Settings.hpp"
#include "Login.hpp"
#include "ConfigFile.hpp"
#include "WaitingRoom.hpp"

State* currentState = nullptr;
SDL_Window* win = nullptr;
SDL_Renderer* renderer = nullptr;

void setState(StateType type)
{
    if (currentState)
        currentState->quit();

    delete currentState;

    switch (type)
    {
        case StateType::Menu:
            currentState = new Menu();
            break;
        case StateType::Singleplayer:
            currentState = new Singleplayer();
            break;
        case StateType::Multiplayer:
            currentState = new Multiplayer();
            break;
        case StateType::Settings:
            currentState = new Settings();
            break;
        case StateType::WaitingRoom:
            currentState = new WaitingRoom();
            break;
        case StateType::Login:
            currentState = new Login();
            break;

    }

    currentState->init(win, renderer);
}

int main(int argc, char* args[])
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    GlobalConfigFile.load();

    auto flags = SDL_WINDOW_SHOWN;

    if (GlobalConfigFile.isFullscreen())
        flags = SDL_WINDOW_FULLSCREEN;

    win = SDL_CreateWindow("Escape Lines", 0, 0, GlobalConfigFile.getWidth(), GlobalConfigFile.getHeight(), flags);

    bool open = true;

    renderer = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

    SDL_Event event;

    float prevTime;
    float currTime;

    setState(StateType::Login);// <- 1 state

    while (open)
    {
        while (SDL_PollEvent( &event))
        {
            if (event.type == SDL_QUIT)
            {
                open = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    open = false;
                else if (event.key.keysym.sym == SDLK_BACKSPACE && currentState->getType() != StateType::Login)
                    setState(StateType::Menu);
            }

            currentState->processEvent(event);
        }

        prevTime = currTime;
        currTime = SDL_GetTicks();
        float deltaTime = (currTime - prevTime) / 2;

        if (currentState->nextState() != StateType::None)
        {
            setState(currentState->nextState());
        }


        SDL_RenderClear(renderer);
        currentState->update(deltaTime);
        SDL_RenderPresent(renderer);
        currentState->AfterRendering();
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    currentState->quit();
    delete currentState;

    return 0;
}
*/

#include "Game.hpp"

int main(int argc, char* args[])
{
    Game game;
    game.run();
    return 0;
}
