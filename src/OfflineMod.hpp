#ifndef OFFLINEMOD_HPP
#define OFFLINEMOD_HPP

#include "State.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Button.hpp"
#include "Settings.hpp"
#include <iostream>
#include "ConfigFile.hpp"



class OfflineMod : public State
{
public:
    void init(SDL_Window* win) override final;
    void quit() override final;

    void processEvent(const SDL_Event& event) override final;
    void update(float deltaTime) override final;
    void draw() override final;

    StateType nextState() override final;

    StateType getType() const override final
    {
        return StateType::Menu;
    }

private:
    StateType changeState = StateType::None;

    SDL_Texture* m_background = nullptr;

    int w = GlobalConfigFile.getWidth();
    int h = GlobalConfigFile.getHeight();

    Button CatchMeIfYouCanButton;
    Button FindTheWayInsideButton;

};


#endif /* OFFLINEMOD_HPP */
