#include "Font.hpp"

Font::~Font()
{
    TTF_CloseFont(m_font);
}

void Font::loadFromFile(const std::string& path, const int size)
{
    m_font = TTF_OpenFont(path.c_str(), size);

    if (!m_font)
        printf("Error: Could not load font %s\n", path.c_str());
}
