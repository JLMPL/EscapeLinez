#include "FindTheWayInside.hpp"
#include "ConfigFile.hpp"
#include "Renderer.hpp"

void FindTheWayInside::init(SDL_Window* win)
{
    Window = win;

    m_player.x = GlobalConfigFile.getWidth() / 2;
    m_player.y = 25;
    m_player.r = 10;

    m_maze = new Maze(1, m_player.r);
    m_maze->generate();

    m_timer = 0;
}

void FindTheWayInside::update(float deltaTime)
{
    m_timer += deltaTime;

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_DOWN])
    {
        m_player.y += deltaTime * 96;
    }
    if (keys[SDL_SCANCODE_LEFT])
    {
        m_player.x -= deltaTime * 96;
    }
    if (keys[SDL_SCANCODE_RIGHT])
    {
        m_player.x += deltaTime * 96;
    }
    if (keys[SDL_SCANCODE_UP])
    {
        m_player.y -= deltaTime * 96;
    }

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
