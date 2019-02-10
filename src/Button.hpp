#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Button
{
public:
    Button() = default;
    ~Button();

    void init(const std::string& released, const std::string& selected, int x, int y, int w = 300);
    void draw();

    bool isPressed() const;

private:
    bool isHover() const;

private:
    SDL_Texture* m_released = nullptr;
    SDL_Texture* m_selected = nullptr;
    SDL_Rect     m_rect;

    int m_initTime = 0;
};

#endif /* BUTTON_HPP */

