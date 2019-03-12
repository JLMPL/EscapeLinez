#ifndef MAZE_HPP
#define  MAZE_HPP

#include <vector>
#include "ConfigFile.hpp"
#include <cstdlib>
#include <ctime>
#include "Renderer.hpp"
#include <SDL2/SDL.h>
#include <iostream>

struct Square
{
    Square(int x, int y):x(x), y(y) {}
    bool visited = false;
    bool special = false;

    bool topWall = true;
    bool downWall = true;
    bool leftWall = true;
    bool rightWall = true;

    int x;
    int y;
};


class Maze
{
public:
    Maze() = default;
    Maze(int WallSize, int PlayerSize)
    {
        m_WallSize = WallSize;
        m_PlayerSize = PlayerSize;
        m_WallLength = (4 * PlayerSize + 5);
        m_CorridorSize = (4 * PlayerSize + 5);
        m_SquareSize = m_CorridorSize + (2 * m_WallSize);

        m_Width = w / m_SquareSize;
        m_Heigth = h / m_SquareSize;

        for (int i = 0; i < m_Width; i++)
        {
            for (int j = 0; j < m_Heigth; j++)
            {
                m_V.push_back(new Square(i, j));
            }
        }
    }
    void generate();
    bool unvisitedSquares();
    // Square* findSquare(int x, int y);
    Square* findSquareNeighbour(int x, int y);
    void draw();


private:
    int m_WallSize;
    int m_WallLength;
    int m_PlayerSize;
    int m_CorridorSize;
    int m_SquareSize;
    int m_Width;
    int m_Heigth;

    std::vector<Square*> m_V;
    std::vector<Square*> m_stack;

    int w = GlobalConfigFile.getWidth();
    int h = GlobalConfigFile.getHeight();

};


#endif
