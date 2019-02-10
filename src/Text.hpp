#ifndef TEXT_HPP
#define TEXT_HPP
#include "Font.hpp"

enum class TextType
{
    Regular,
    Password
};

class Text
{
public:
    Text() = default;
    ~Text();

    void update(float deltaTime);
    void draw();

    void setTextType(const TextType& type);
    void setCaret(bool isCaret);
    void setFont(const Font& font);
    void setString(const std::string& string);
    void setColor(const SDL_Color& color);
    void setPosition(int x, int y);

    SDL_Rect getRect();
    const std::string& getString();

protected:
    void updateTexture();

protected:
    const Font* m_font = nullptr;
    TextType m_type = TextType::Regular;

    bool m_isCaret = false;
    bool m_caretBlink = false;

    std::string m_string;

    SDL_Color m_color = {255,255,255,255};

    SDL_Texture* m_texture = nullptr;
    SDL_Rect m_rect = {0,0,32,32};

    SDL_Rect m_caret = {0,0,32,32};

    float m_timer = 0;
};

#endif
