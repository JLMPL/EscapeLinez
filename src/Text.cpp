#include "Text.hpp"
#include "Renderer.hpp"
#include <iostream>

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
    if(m_string != "")
    {
        SDL_Surface* surf = TTF_RenderText_Blended(m_font->m_font, m_string.c_str(), m_color);
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

std::string Text::getString()
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

bool Text::isFocus()
{
    return focus;
}

void Text::setInputMark()
{
    m_string_marked = m_string;
    m_string_marked.push_back('|');
    updateTextureMarked();
}

void Text::deleteInputMark()
{
    updateTexture();
}

SDL_Rect Text::getRect()
{
    return m_rect;
}

void Password::hide()
{
    m_password_hidden = m_string;
    if (m_password_hidden.size() > 1)
    {
        for (int i = m_password_hidden.size() - 2; i >= 0; i--)
        {
            m_password_hidden[i] = '#';
        }
    }
    updateTextureHidden();
}

void Password::setInputMark()
{
    m_string_marked = m_password_hidden;
    m_string_marked.push_back('|');
    updateTextureMarked();
}

void Text::popBack()
{
    if(m_string.size() > 0)
    {
        m_string.pop_back();
        updateTexture();
    }
}

void Password::popBack()
{
    if(m_string.size() > 0)
    {
        m_string.pop_back();
        hide();
        updateTexture();
    }
}


void Text::pushBack(const char t)
{
    m_string.push_back(t);
    updateTexture();
}

void Password::deleteInputMark()
{
    updateTextureHidden();
}

std::string Password::getStringHidden()
{
    return m_password_hidden;
}

void Password::updateTextureHidden()
{
    if(m_password_hidden != "")
    {
        SDL_Surface* surf = TTF_RenderText_Blended(m_font->m_font, m_password_hidden.c_str(), m_color);
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
}

void Text::updateTextureMarked()
{
    if(m_string != "")
    {
        SDL_Surface* surf = TTF_RenderText_Blended(m_font->m_font, m_string_marked.c_str(), m_color);
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
}


void Password::updateTextureMarked()
{
    if(m_string != "")
    {
        SDL_Surface* surf = TTF_RenderText_Blended(m_font->m_font, m_string_marked.c_str(), m_color);
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
}
