#ifndef LINES_HPP
#define LINES_HPP
#include "ConfigFile.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>

class Line
{
public:
    Line() = default;
    Line(int resolutionX, int resolutionY, int type, int& numberLines, int&heigth, float speed);

    void moveX(float deltaTime);
    void moveY(bool direction);

    void hide();
    void show();

    int X[2];
    int Y[2];
    float speed;
    int w = GlobalConfigFile.getWidth();
    int h = GlobalConfigFile.getHeight();
};

#endif
