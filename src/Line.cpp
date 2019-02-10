#include "Line.hpp"
#include "Renderer.hpp"
#include "ConfigFile.hpp"

Line::Line(int height)
{
    int x = rand() % GlobalConfigFile.getWidth();

    m_mainPos = {x, height};
    m_fragPos = {x, height};

    m_width = (rand() % 200) + 900;

    m_speed = (rand() % 48) + 48;
}

void Line::update(float deltaTime)
{
    m_mainPos.x -= m_speed * deltaTime;

    if (m_mainPos.x < 0)
    {
        m_showFrag = true;
        int screenWidth = GlobalConfigFile.getWidth();

        m_fragPos.x = (screenWidth - abs(m_mainPos.x));

        if (m_fragPos.x < (screenWidth - m_width))
            m_mainPos.x = (screenWidth - m_width);
    }
    else
        m_showFrag = false;
}

void Line::draw() const
{
    SDL_SetRenderDrawColor(GlobalRenderer, 0, 64, 240, 255);
    SDL_RenderDrawLine(GlobalRenderer, m_mainPos.x, m_mainPos.y, m_mainPos.x + m_width, m_mainPos.y);

    if (m_showFrag)
    {
        SDL_SetRenderDrawColor(GlobalRenderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(GlobalRenderer, m_fragPos.x, m_fragPos.y, m_fragPos.x + m_width, m_fragPos.y);
    }
}
