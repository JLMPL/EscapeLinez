#ifndef LINES_HPP
#define LINES_HPP
#include <SDL2/SDL.h>

class Line
{
public:
    Line() = default;
    Line(int height);

    void update(float deltaTime);
    void draw() const;

private:
    struct Pos
    {
        float x = 0;
        float y = 0;
    };

    Pos m_mainPos;
    Pos m_fragPos;

    int m_width = 32;
    float m_speed = 32;

    bool m_showFrag = false;
};

#endif
