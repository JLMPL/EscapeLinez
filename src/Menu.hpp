#ifndef MENU_HPP
#define MENU_HPP

#include "State.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Button.hpp"
#include "Settings.hpp"
#include <iostream>
#include "ConfigFile.hpp"

/*
    Narazie nie będzie działać klawiatura w menu
*/

class Menu : public State
{
    public:
        void init(SDL_Window* win, SDL_Renderer* rend) override final;
        void quit() override final;
        void update(float deltaTime) override final;
        void AfterRendering() override final;
        void processEvent(const SDL_Event& event) override final;

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

        Button singleButton;
        Button multiButton;
        Button settingsButton;
        Button exitButton;
};



#endif /* MENU_HPP */

