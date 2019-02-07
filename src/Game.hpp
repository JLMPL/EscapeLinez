#ifndef GAME_HPP
#define GAME_HPP
#include "State.hpp"
#include <SDL2/SDL.h>

/*
    Główna klasa programu
    Inicjalizuje SDL
    Zarządza Stejtami
*/
class Game
{
public:
    Game();
    ~Game();

    void run();

    void setState(StateType type);

private:
    void initSDL();
    void processEvent(const SDL_Event& event);
    void update();
    void draw();

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Event m_event;

    bool m_open = true;

    float m_prevTime = 0;
    float m_currTime = 0;
    float m_deltaTime = 0;

    State* m_currState = nullptr;

};

#endif
