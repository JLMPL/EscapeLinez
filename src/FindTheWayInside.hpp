#ifndef FINDTHEWAYINSIDE_HPP
#define FINDTHEWAYINSIDE_HPP

#include "State.hpp"
#include "Settings.hpp"
#include "ConfigFile.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include "Maze.hpp"

class FindTheWayInside : public State
{
public:
    void init(SDL_Window* win) override final;
    void quit() override final;

    void update(float deltaTime) override final;
    void draw() override final;

    StateType nextState() override final { return StateType::None; }

    StateType getType() const override final
    {
        return StateType::FindTheWayInside;
    }
private:
    float m_timer = 0;

    Maze* m_maze;

    Player m_player;
    
    Square* m_CurrentSquare = nullptr;
};




#endif
