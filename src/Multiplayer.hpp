#ifndef MULTIPLAYER_HPP
#define MULTIPLAYER_HPP
#include "State.hpp"
#include "Lines.hpp"
#include "Settings.hpp"
#include <SDL2/SDL.h>
#include <SFML/Network.hpp>

struct Players
{
    float x = 0, y = 0;
    float r;
};

class Multiplayer : public State
{
    public:
        void init(SDL_Window* win, SDL_Renderer* rend) override final;
        void quit() override final;

        void update(float deltaTime) override final;
        void draw() override final;

        StateType nextState() override final { return StateType::None; }

        void addLine();
        void moveLine();

        StateType getType() const override final
        {
            return StateType::Multiplayer;
        }

    private:
        int changeState = 0;

        Players     players[4];
        Line        lines[90],
                    linesB[90];
        int         numberLines = 0,
                    TiMe = 0,
                    heigth = 0,
                    speed = 3,
                    w,
                    h;
        float       timer = 0;


};

#endif /* MULTIPLAYER_HPP */

