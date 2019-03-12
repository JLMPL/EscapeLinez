#include "CatchMeIfYouCan.hpp"
#include "ConfigFile.hpp"
#include "Renderer.hpp"

void CatchMeIfYouCan::init(SDL_Window* win)
{
    Window = win;

    m_player.x = GlobalConfigFile.getWidth() / 2;
    m_player.y = 25;
    m_player.r = 10;

    m_timer = 0;
}

void CatchMeIfYouCan::addLine()
{
    m_lines.push_back(Line(m_height));
    m_height += 48;
}

void CatchMeIfYouCan::update(float deltaTime)
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

    if (m_timer > 0.1f)
    {
        addLine();
        m_timer = 0;
    }

    for (auto& line : m_lines)
        line.update(deltaTime);

/*    for (int i = 0; i < 90; i++)
    {
        if (lines[i].Y[0] >= (player.y - 10) && lines[i].Y[1] <= (player.y + 10) && lines[i].X[0] < (player.x + 10) && lines[i].X[1] > (player.x - 10))
        {
            player.x = 683;
            player.y = 25;
            player.r = 10;
        }
        if (linesB[i].Y[0] >= (player.y - 10) && linesB[i].Y[1] <= (player.y + 10) && linesB[i].X[0] < (player.x + 10) && linesB[i].X[1] > (player.x - 10))
        {
            player.x = 683;
            player.y = 25;
            player.r = 10;
        }
    }*/
}

void CatchMeIfYouCan::draw()
{
    for (auto& line : m_lines)
        line.draw();

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

void CatchMeIfYouCan::quit()
{

}
