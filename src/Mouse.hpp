#ifndef MOUSE_HPP
#define MOUSE_HPP

struct Mouse
{
    int x = 0;
    int y = 0;
    bool left = false;
    bool right = false;

    void update();
};

extern Mouse GlobalMouse;

#endif
