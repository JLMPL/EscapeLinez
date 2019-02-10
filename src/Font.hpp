#ifndef FONT_HPP
#define FONT_HPP
#include <SDL2/SDL.h>
#include <string>

class Font
{
public:
    Font() = default;
    ~Font();

    void loadFromFile(const std::string& path);

private:
    TTF_Font* m_font = nullptr;

    friend class Text;
};

#endif
