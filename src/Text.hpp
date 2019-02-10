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
    bool isFocus();
    virtual void setInputMark();
    virtual void deleteInputMark();
    SDL_Rect getRect();
    std::string getString();
    virtual void popBack();
    void pushBack(const char t);

    void setPosition(int x, int y);

    void draw();

protected:
    void updateTexture();
    virtual void updateTextureMarked();

protected:
    const Font* m_font = nullptr;

    bool focus = false;

    std::string m_string;
    std::string m_string_marked;

    SDL_Color m_color = {255,255,255,255};

    SDL_Texture* m_texture = nullptr;
    SDL_Rect m_rect = {0,0,32,32};
};

class Password : public Text
{
private:
    std::string m_password_hidden;
private:
    void updateTextureHidden();
    void updateTextureMarked() override final;
public:
    void hide();
    void popBack() override final;
    void setInputMark() override final;
    void deleteInputMark() override final;
    std::string getStringHidden();

};

#endif
