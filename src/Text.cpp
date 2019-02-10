#include "Text.hpp"
#include "Renderer.hpp"
#include <iostream>

Text::~Text()
{
    SDL_DestroyTexture(m_texture);
}

void Text::setTextType(const TextType& type)
{
    m_type = type;
}

void Text::setFont(const Font& font)
{
    m_font = &font;

    m_string += ' ';
    updateTexture();
    m_string.pop_back();
}

void Text::setCaret(bool isCaret)
{
    m_isCaret = isCaret;
}

void Text::updateTexture()
{
    if (!m_string.empty())
    {
        std::string actual = m_string;

        if (m_type == TextType::Password && actual.size() > 1)
        {
            for (int i = 0; i < actual.size() - 1; i++)
                actual[i] = '*';
        }

        SDL_Surface* surf = TTF_RenderText_Blended(m_font->m_font, actual.c_str(), m_color);
        m_texture = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

        m_rect.w = surf->w;
        m_rect.h = surf->h;

        SDL_FreeSurface(surf);
    }
    else
    {
        m_rect.w = 0;
        m_rect.h = 0;
    }

    m_caret.x = m_rect.x + m_rect.w;
    m_caret.y = m_rect.y;

    m_caret.h = m_rect.h;
    m_caret.w = 2;
}

void Text::update(float deltaTime)
{
    m_timer += deltaTime;

    if (m_timer > 0.5)
    {
        m_caretBlink = !m_caretBlink;
        m_timer = 0;
    }
}

void Text::draw()
{
    SDL_RenderCopy(GlobalRenderer, m_texture, NULL, &m_rect);

    if (m_isCaret && m_caretBlink)
    {
        SDL_SetRenderDrawColor(GlobalRenderer, 255,255,255,255);
        SDL_RenderFillRect(GlobalRenderer, &m_caret);
    }
}

void Text::setString(const std::string& string)
{
    m_string = string;
    updateTexture();
}

const std::string& Text::getString()
{
    return m_string;
}

void Text::setColor(const SDL_Color& color)
{
    m_color = color;
}

void Text::setPosition(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
}

SDL_Rect Text::getRect()
{
    return m_rect;
}
