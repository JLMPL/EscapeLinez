#ifndef CATCHMEIFYOUCAN_HPP
#define CATCHMEIFYOUCAN_HPP
#include "State.hpp"
#include "Line.hpp"
#include "Settings.hpp"
#include "ConfigFile.hpp"
#include "Player.hpp"

#include <SDL2/SDL.h>
#include <vector>

class CatchMeIfYouCan : public State
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
        return StateType::CatchMe;
    }

private:
    std::vector<Line> m_lines;

    int m_height = 64;

    float m_timer = 0;

    Player m_player;
};

#endif /* MENU_HPP */
