#include "Maze.hpp"


void Maze::draw()
{
    int x1;
    int x2;
    int y1;
    int y2;

    SDL_SetRenderDrawColor(GlobalRenderer, 0, 64, 255, 0);


    for (int i = 0; i < m_V.size(); i++)
    {
        x1 = m_V[i]->x * m_WallLength;
        x2 = (m_V[i]->x + 1) * m_WallLength;
        y1 = m_V[i]->y * m_WallLength;
        y2 = (m_V[i]->y + 1) * m_WallLength;

        if (m_V[i]->topWall == true)
        {
            SDL_RenderDrawLine(GlobalRenderer, x1, y1, x2, y1);
        }
        if (m_V[i]->downWall == true)
        {
            SDL_RenderDrawLine(GlobalRenderer, x1, y2, x2, y2);
        }
        if (m_V[i]->leftWall == true)
        {
            SDL_RenderDrawLine(GlobalRenderer, x1, y1, x1, y2);
        }
        if (m_V[i]->rightWall == true)
        {
            SDL_RenderDrawLine(GlobalRenderer, x2, y1, x2, y2);
        }
    }
}


void Maze::generate()
{
    Square* CurrentSquare = m_V[0];
    Square* NextSquare = nullptr;
    m_V[0]->visited = true;
    m_stack.push_back(CurrentSquare);

    while (unvisitedSquares())
    {
        NextSquare = findSquareNeighbour(CurrentSquare->x, CurrentSquare->y);

        if (NextSquare != nullptr)
        {
            m_stack.push_back(CurrentSquare);

            if (CurrentSquare->x + 1 == NextSquare->x &&
                     CurrentSquare->y == NextSquare->y)
            {
                CurrentSquare->rightWall = false;
                NextSquare->leftWall = false;
            }
            else if (CurrentSquare->x - 1 == NextSquare->x &&
                     CurrentSquare->y == NextSquare->y)
            {
                CurrentSquare->leftWall = false;
                NextSquare->rightWall = false;
            }
            else if (CurrentSquare->y - 1 == NextSquare->y &&
                     CurrentSquare->x == NextSquare->x)
            {
                CurrentSquare->topWall = false;
                NextSquare->downWall = false;
            }
            else if (CurrentSquare->y + 1 == NextSquare->y &&
                     CurrentSquare->x == NextSquare->x)
            {
                CurrentSquare->downWall = false;
                NextSquare->topWall = false;
            }
            CurrentSquare = NextSquare;
            CurrentSquare->visited = true;
        }
        else if (m_stack.size() > 0)
        {
            CurrentSquare = m_stack.back();
            m_stack.pop_back();
        }
    }
}


bool Maze::unvisitedSquares()
{
    for (int i = 0; i < m_V.size(); i++)
    {

        if (m_V[i]->visited == false)
        {
            return true;
        }

    }

    return false;

}


// Square* Map::findSquare(int x, int y)
// {
//     for (int i = 0; i < m_V.size(); i++)
//     {
//         if (m_V[i]->x == x && m_V[i]->y == y)
//         {
//             return m_V[i];
//         }
//     }
//
//     return nullptr;
// }

Square* Maze::findSquareNeighbour(int x, int y)
{

    bool top = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool end = false;

    int randomNumber;

    Square* topSquare = nullptr;
    Square* downSquare = nullptr;
    Square* rightSquare = nullptr;
    Square* leftSquare = nullptr;

    for (unsigned int i = 0; i < m_V.size(); i++)
    {

        if (m_V[i]->x == (x + 1) && m_V[i]->y == y)
        {
            if(m_V[i]->visited == false)
            {
                right = true;
                rightSquare = m_V[i];
            }
        }
        else if (m_V[i]->x == x && m_V[i]->y == (y + 1))
        {
            if(m_V[i]->visited == false)
            {
                down = true;
                downSquare = m_V[i];
            }
        }
        else if (m_V[i]->x == (x - 1) && m_V[i]->y == y)
        {
            if(m_V[i]->visited == false)
            {
                left = true;
                leftSquare = m_V[i];
            }
        }
        else if (m_V[i]->x == x && m_V[i]->y == (y - 1))
        {
            if(m_V[i]->visited == false)
            {
                top = true;
                topSquare = m_V[i];
            }
        }
        else if(right && left && top && down) break;
    }

    if (top == true || left == true || right == true || down == true)
        do
        {
            randomNumber = ( std::rand() % 4 ) + 1;
            switch (randomNumber)
            {
                case 1:
                    if (top)
                    {
                        end = true;
                        return topSquare;
                    }
                    break;
                case 2:
                    if (right)
                    {
                        end = true;
                        return rightSquare;
                    }
                    break;
                case 3:
                    if (left)
                    {
                        end = true;
                        return leftSquare;
                    }
                    break;
                case 4:
                    if (down)
                    {
                        end = true;
                        return downSquare;
                    }
                    break;
            }
        } while(end != true);

    else return nullptr;



}
