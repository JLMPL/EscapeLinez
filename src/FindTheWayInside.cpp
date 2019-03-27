#include "FindTheWayInside.hpp"
#include "ConfigFile.hpp"
#include "Renderer.hpp"

void FindTheWayInside::init(SDL_Window* win)
{
    Window = win;

    m_player.r = 10;

    m_maze = new Maze(1, m_player.r);
    m_maze->generate();
    
    m_player.x = (m_maze->getSquareSize() / 2) + m_maze->getOffsetW();
    m_player.y = (m_maze->getSquareSize() / 2) + m_maze->getOffsetH();
    
    m_CurrentSquare = m_maze->getMaze()[0];

    m_timer = 0;
}

void FindTheWayInside::update(float deltaTime)
{
    m_timer += deltaTime;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    
    if((m_CurrentSquare->x * m_maze->getSquareSize() + m_maze->getOffsetW()) < (m_player.x - m_player.r) || m_CurrentSquare->leftWall == false)
    {
        if (keys[SDL_SCANCODE_LEFT])
        {
            m_player.x -= deltaTime * 200;
        }
    }
    if(((m_CurrentSquare->x * m_maze->getSquareSize()) + m_maze->getSquareSize()  + m_maze->getOffsetW()) > (m_player.x + m_player.r) || m_CurrentSquare->rightWall == false)
    {
        if (keys[SDL_SCANCODE_RIGHT])
        {
            m_player.x += deltaTime * 200;
        }
    }
    if((m_CurrentSquare->y * m_maze->getSquareSize()  + m_maze->getOffsetH()) < (m_player.y - m_player.r) || m_CurrentSquare->topWall == false)
    {
        if (keys[SDL_SCANCODE_UP])
        {
            m_player.y -= deltaTime * 200;
        }
    }
    if(((m_CurrentSquare->y * m_maze->getSquareSize()) + m_maze->getSquareSize()  + m_maze->getOffsetH())> (m_player.y + m_player.r) || m_CurrentSquare->downWall == false)
    {        
        if (keys[SDL_SCANCODE_DOWN])
        {
            m_player.y += deltaTime * 200;
        }
    }
    
    m_CurrentSquare = m_maze->findSquare(m_player.x / m_maze->getSquareSize(),  m_player.y / m_maze->getSquareSize()); 
}

void FindTheWayInside::draw()
{
    m_maze->draw();
    
    SDL_SetRenderDrawColor(GlobalRenderer, 255, 64, 0, 0);

    
     for(float x = (-40); x < 40; x+=1)
     {
         for(float y = (-40); y < 40; y+=1)
         {
             if(pow(x, 2) + pow(y, 2) < pow(m_player.r, 2))
             {
                 int a = x + m_player.x;
                 int b = y + m_player.y;
                 SDL_RenderDrawPoint(GlobalRenderer, a, b);
             }
    
         }
     }
}

void FindTheWayInside::quit()
{

}
