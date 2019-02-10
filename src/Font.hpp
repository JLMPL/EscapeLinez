#ifndef FONT_HPP
#define FONT_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Font
{
public:
    Font() = default;
    ~Font();

    void loadFromFile(const std::string& path, const int size);

private:
    TTF_Font* m_font = nullptr;

    friend class Text;
};

#endif
