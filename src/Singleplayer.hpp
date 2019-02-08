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
    void init(SDL_Window* win) override final;
    void quit() override final;

    void update(float deltaTime) override final;
    void draw() override final;

    StateType nextState() override final { return StateType::None; }

    void addLine();
    void moveLine(float deltaTime);

    StateType getType() const override final
    {
        return StateType::Singleplayer;
    }

private:
    Line        lines[90];
    Line        linesB[90];

    int         numberLines = 0;
    int         TiMe = 0;
    int         heigth = 0;
    int         speed = 3;

    float       timer = 0;

    int         w = GlobalConfigFile.getWidth(),
                h = GlobalConfigFile.getHeight();

    Player      p;

};

#endif /* MENU_HPP */

