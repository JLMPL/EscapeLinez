#ifndef TEXT_HPP
#define TEXT_HPP
#include "Font.hpp"

class Text
{
public:
    Text() = default;
    ~Text();

    void setFont(const Font& font);
    void setString(const std::string& string);
    void setColor(const SDL_Color& color);

    void setPosition(int x, int y);

    void draw();

private:
    void updateTexture();

private:
    const Font* m_font = nullptr;

    std::string m_string;

    SDL_Color m_color = {255,255,255,255};

    SDL_Texture* m_texture = nullptr;
    SDL_Rect m_rect = {0,0,32,32};
};

#endif
