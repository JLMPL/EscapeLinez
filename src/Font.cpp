#include "Font.hpp"

Font::~Font()
{
    TTF_CloseFont(m_font);
}

void Font::loadFromFile(const std::string& path)
{
    m_font = TTF_OpenFont(path.c_str(), 36);

    if (!m_font)
        printf("Error: Could not load font %s\n", path.c_str());
}
