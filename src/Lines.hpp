/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lines.hpp
 * Author: krzysiek
 *
 * Created on April 13, 2018, 12:30 PM
 */

#ifndef LINES_HPP
#define LINES_HPP

#include <cstdlib>
#include <time.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "ConfigFile.hpp"






class Line
{
    public:
        int X[2];
        int Y[2];
        int speed;
        int         w = GlobalConfigFile.getWidth(), 
                    h = GlobalConfigFile.getHeight();
        
        void moveX();
        
        void moveY(bool direction);
        
        void hide();
        
        void show();
        
        Line() = default;
        Line(int resolutionX, int resolutionY, int type, int& numberLines, int&heigth, int speed);
        
};




//class Player
//{
//    public:
//        float positon[2];
//        float radius;
//};




#endif 