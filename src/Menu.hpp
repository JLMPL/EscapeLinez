#ifndef MENU_HPP
#define MENU_HPP

#include "State.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Button.hpp"
#include "Settings.hpp"
#include <iostream>
#include "ConfigFile.hpp"



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
        SDL_Surface *wallpaper;

        SDL_Texture* tex;
        
        int w = GlobalConfigFile.getWidth(), h = GlobalConfigFile.getHeight();
        int hover = 0;


        Button singleButton;
        Button multiButton;
        Button settingsButton;
        Button exitButton;

        Button singleButtonS;
        Button multiButtonS;
        Button settingsButtonS;
        Button exitButtonS;
};



#endif /* MENU_HPP */

