#include "Text.hpp"
#include "Renderer.hpp"

Text::~Text()
{
    SDL_DestroyTexture(m_texture);
}

void Text::setFont(const Font& font)
{
    m_font = &font;
}

void Text::updateTexture()
{
    SDL_Surface* surf = TTF_RenderText_Blended(m_font->m_font, m_string.c_str(), m_color);
    m_texture = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    m_rect.w = surf->w;
    m_rect.h = surf->h;

    SDL_FreeSurface(surf);
}

void Text::draw()
{
    SDL_RenderCopy(GlobalRenderer, m_texture, NULL, &m_rect);
}

void Text::setString(const std::string& string)
{
    m_string = string;
    updateTexture();
}

void Text::setColor(const SDL_Color& color)
{
    m_color = color;
    updateTexture();
}

void Text::setPosition(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
}
