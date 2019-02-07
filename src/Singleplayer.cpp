#include "Singleplayer.hpp"

void Singleplayer::init(SDL_Window* win, SDL_Renderer* rend)
{
    Renderer = rend;
    Window = win;

    p.x = w / 2;
    p.y = 25;
    p.r = 10;
    
    timer = 0;
}

void Singleplayer::addLine()
{
    if(TiMe < 90)
    {
        if(numberLines%3 == 0)
            speed = rand()%7+1;
        lines[numberLines] = Line(w, h, 1, numberLines, heigth, speed);
        linesB[numberLines] = Line(w, h, 2, numberLines, heigth, speed);

        numberLines++;
        
            
    }
    TiMe++;
}

void Singleplayer::moveLine()
{
    for(int i = 0; i < numberLines; i++)
    {
        lines[i].moveX();
        int delta = abs(lines[i].X[1] - lines[i].X[0]);
        if(lines[i].X[0] < 0)
        {
            linesB[i].X[0]-=linesB[i].speed;
            if(linesB[i].X[0] <= w - 1 - delta)
            {
                lines[i].X[0] = w - 1 - delta;
                lines[i].X[1] = w - 1;
                linesB[i].X[0] = w - 1;
            }
        }
    }
}

void Singleplayer::update(float deltaTime)
{
    timer += deltaTime;

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_DOWN])
    {
        p.y += deltaTime * 0.5;
    }
    if (keys[SDL_SCANCODE_LEFT])
    {
        p.x -= deltaTime * 0.5;
    }
    if (keys[SDL_SCANCODE_RIGHT])
    {
        p.x += deltaTime * 0.5;
    }
    if (keys[SDL_SCANCODE_UP])
    {
        p.y -= deltaTime * 0.5;
    }

    if (timer > 5.f)
    {
        addLine();
        moveLine();
        timer = 0;
    }



    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor( Renderer, 0, 64, 240, 255);
    for (int i = 0; i < numberLines; i++)
    {
        SDL_RenderDrawLine(Renderer, lines[i].X[0], lines[i].Y[0], lines[i].X[1], lines[i].Y[1]);
        SDL_RenderDrawLine(Renderer, linesB[i].X[0], linesB[i].Y[0], linesB[i].X[1], linesB[i].Y[1]);
    }

    SDL_SetRenderDrawColor( Renderer, 240, 64, 0, 255);

    for(int i = 0; i<90; i++)
    {

        if(lines[i].Y[0] >= (p.y - 10) && lines[i].Y[1] <= (p.y + 10) && lines[i].X[0] < (p.x + 10) && lines[i].X[1] > (p.x - 10))
        {
            p.x = 683;
            p.y = 25;
            p.r = 10;
        }
        if(linesB[i].Y[0] >= (p.y - 10) && linesB[i].Y[1] <= (p.y + 10) && linesB[i].X[0] < (p.x + 10) && linesB[i].X[1] > (p.x - 10))
        {
            p.x = 683;
            p.y = 25;
            p.r = 10;
        }
    }

    for(float x = (-40); x < 40; x+=1)
    {
        for(float y = (-40); y < 40; y+=1)
        {
            if(pow(x, 2) + pow(y, 2) < pow(p.r, 2))
            {
                int a = x + p.x;
                int b = y + p.y;
                SDL_RenderDrawPoint(Renderer, a, b);
            }

        }
    }
}

void Singleplayer::AfterRendering()
{

}

void Singleplayer::quit()
{
    
}