#include "Button.hpp"
#include "Mouse.hpp"
#include "Renderer.hpp"
#include "TextureLoader.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Button::init(const std::string& released, const std::string& selected, int x, int y, int w)
{
    m_released = loadTexture("data/Images/" + released);
    m_selected = loadTexture("data/Images/" + selected);

    m_rect.w = w;
    m_rect.h = 70;
    m_rect.x = x;
    m_rect.y = y;
}

void Button::draw()
{
    if (isHover())
        SDL_RenderCopy(GlobalRenderer, m_selected, NULL, &m_rect);
    else
        SDL_RenderCopy(GlobalRenderer, m_released, NULL, &m_rect);
}

bool Button::isHover() const
{
    if (GlobalMouse.x < m_rect.x)
        return false;
    if (GlobalMouse.x > m_rect.x + m_rect.w)
        return false;
    if (GlobalMouse.y < m_rect.y)
        return false;
    if (GlobalMouse.y > m_rect.y + m_rect.h)
        return false;
    return true;
}

bool Button::isPressed() const
{
    return isHover() && GlobalMouse.left;
}

Button::~Button()
{
    SDL_DestroyTexture(m_released);
    SDL_DestroyTexture(m_selected);
}
