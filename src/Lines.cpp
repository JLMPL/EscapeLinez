#include "Lines.hpp"

void Line::moveX()
{
    this->X[0]-=this->speed;
    this->X[1]-=this->speed;
}


void Line::moveY(bool direction)
{
    if(direction)
    {
        this->Y[0]+=this->speed;
    }
    else
    {
        this->Y[0]-=this->speed;
    }
}

void Line::hide()
{
    this->X[0] = 0;
    this->X[1] = 0;
    this->Y[0] = 0;
    this->Y[1] = 0;
}


Line::Line(int resolutionX, int resolutionY, int type, int& numberLines, int& heigth, int speed)
{
    
    
    switch(type)
    {
        case 1:
            if(numberLines%3 == 0)
                heigth+=55;
            
            do
            {
                int c = 50 + heigth;
                this->X[0] = rand()%resolutionX;
                this->X[1] = rand()%resolutionX;
                this->Y[0] = c;
                this->Y[1] = this->Y[0];
                this->speed = speed;
                int memo = this->X[0];
                if(this->X[0] > this->X[1])
                {
                    this->X[0] = this->X[1];
                    this->X[1] = memo;
                }
            } while(abs(this->X[0] - this->X[1]) < 400 || abs(this->X[0] - this->X[1]) > 410);

            break;
            
        case 2:
            
            int c = 50 + heigth;
            this->X[0] = w;
            this->X[1] = w;
            this->Y[0] = c;
            this->Y[1] = this->Y[0];
            this->speed = speed;
            

            break;          

    }
}

