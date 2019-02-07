/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.hpp
 * Author: krzysiek
 *
 * Created on April 24, 2018, 2:56 PM
 */

#ifndef SINGLEPLAYER_HPP
#define SINGLEPLAYER_HPP

#include "State.hpp"
#include "Lines.hpp"
#include <SDL2/SDL.h>
#include "Settings.hpp"
#include "ConfigFile.hpp"

struct Player
{
    float x = 0, y = 0;
    float r;
};

class Singleplayer : public State
{
    public:
        void init(SDL_Window* win, SDL_Renderer* rend) override final;
        void quit() override final;
        void update(float deltaTime) override final;
        void AfterRendering() override final;
        
        StateType nextState() override final { return StateType::None; }
        
        void addLine();
        void moveLine();
        
        StateType getType() const override final
        {
            return StateType::Singleplayer;
        }
        
    private:
        Line        lines[90];
        Line        linesB[90];
        int         numberLines = 0,
                    TiMe = 0,
                    heigth = 0,
                    speed = 3;
                    
        float       timer = 0;

        int         w = GlobalConfigFile.getWidth(), 
                    h = GlobalConfigFile.getHeight();
        
        Player      p;

};

#endif /* MENU_HPP */

