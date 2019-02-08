#include "Multiplayer.hpp"
#include "ConfigFile.hpp"
#include <SFML/Network.hpp>

void Multiplayer::init(SDL_Window* win, SDL_Renderer* rend)
{
    Window = win;
    Renderer = rend;

    w = GlobalConfigFile.getWidth();
    h = GlobalConfigFile.getHeight();

    for (int i = 0; i < 4; i++)
    {
//        players[i].x = 623 + (i * 30);
//        players[i].y = 25;
//        players[i].r = 10;
    }

    timer = 0;
}

void Multiplayer::addLine()
{
    if (TiMe < 90)
    {
        if (numberLines%3 == 0)
            speed = rand()%4+2;
        lines[numberLines] = Line(w, h, 1, numberLines, heigth, speed);
        linesB[numberLines] = Line(w, h, 2, numberLines, heigth, speed);

        numberLines++;


    }
    TiMe++;
}

void Multiplayer::moveLine()
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

void Multiplayer::update(float deltaTime)
{
    timer += deltaTime;

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_DOWN])
    {
        players[0].y += deltaTime * 32;
    }
    if (keys[SDL_SCANCODE_LEFT])
    {
        players[0].x -= deltaTime * 32;
    }
    if (keys[SDL_SCANCODE_RIGHT])
    {
        players[0].x += deltaTime * 32;
    }
    if (keys[SDL_SCANCODE_UP])
    {
        players[0].y -= deltaTime * 32;
    }

    if (timer > 5.f)
    {
        addLine();
        moveLine();
        timer = 0;
    }


//    for(int i = 0; i<90; i++)
//    {
//
//        if(lines[i].Y[0] >= (p.y - 10) && lines[i].Y[1] <= (p.y + 10) && lines[i].X[0] < (p.x + 10) && lines[i].X[1] > (p.x - 10))
//        {
//            p.x = 683;
//            p.y = 25;
//            p.r = 10;
//        }
//        if(linesB[i].Y[0] >= (p.y - 10) && linesB[i].Y[1] <= (p.y + 10) && linesB[i].X[0] < (p.x + 10) && linesB[i].X[1] > (p.x - 10))
//        {
//            p.x = 683;
//            p.y = 25;
//            p.r = 10;
//        }
//    }
}

void Multiplayer::draw()
{
    SDL_SetRenderDrawColor(Renderer, 0, 64, 240, 255);

    for (int i = 0; i < numberLines; i++)
    {
        SDL_RenderDrawLine(Renderer, lines[i].X[0], lines[i].Y[0], lines[i].X[1], lines[i].Y[1]);
        SDL_RenderDrawLine(Renderer, linesB[i].X[0], linesB[i].Y[0], linesB[i].X[1], linesB[i].Y[1]);
    }

    for (float x = (-40); x < 40; x+=1)
    {
        for (float y = (-40); y < 40; y+=1)
        {
            if (pow(x, 2) + pow(y, 2) < pow(players[0].r, 2))
            {
                SDL_SetRenderDrawColor( Renderer, 240, 64, 0, 255);
                int a = x + players[0].x;
                int b = y + players[0].y;
                SDL_RenderDrawPoint(Renderer, a, b);

                SDL_SetRenderDrawColor( Renderer, 64, 240, 0, 255);
                a = x + players[1].x;
                b = y + players[1].y;
                SDL_RenderDrawPoint(Renderer, a, b);

                SDL_SetRenderDrawColor( Renderer, 255, 255, 0, 255);
                a = x + players[2].x;
                b = y + players[2].y;
                SDL_RenderDrawPoint(Renderer, a, b);

                SDL_SetRenderDrawColor( Renderer, 255, 255, 255, 255);
                a = x + players[3].x;
                b = y + players[3].y;
                SDL_RenderDrawPoint(Renderer, a, b);
            }
        }
    }
}

void Multiplayer::quit()
{

}
