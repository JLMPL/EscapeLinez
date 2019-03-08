#ifndef FINDTHE_HPP
#define FINDTHE_HPP

#include "State.hpp"
#include "Settings.hpp"
#include "ConfigFile.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>
#include <vector>

class FindThe : public State
{
public:
    void init(SDL_Window* win) override final;
    void quit() override final;

    void update(float deltaTime) override final;
    void draw() override final;

    StateType nextState() override final { return StateType::None; }

    StateType getType() const override final
    {
        return StateType::FindThe;
    }
private:
    float m_timer = 0;

    Player m_player;
};




#endif
