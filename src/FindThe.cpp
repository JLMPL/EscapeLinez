#include "FindThe.hpp"
#include "ConfigFile.hpp"
#include "Renderer.hpp"

void FindThe::init(SDL_Window* win)
{
    Window = win;

    m_player.x = GlobalConfigFile.getWidth() / 2;
    m_player.y = 25;
    m_player.r = 10;

    m_timer = 0;
}

void FindThe::update(float deltaTime)
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

void FindThe::draw()
{


    SDL_SetRenderDrawColor(GlobalRenderer, 240, 64, 0, 255);

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

void FindThe::quit()
{

}
