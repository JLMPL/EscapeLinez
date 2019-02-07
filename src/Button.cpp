#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.hpp"

void Button::init(SDL_Texture* texture, int x, int y, int w)
{    
    this->texture = texture;

    DownR.w = w;
    DownR.h = 70;
    DownR.x = x;
    DownR.y = y;
}

void Button::updateButton(SDL_Renderer *renderer)
{  
    SDL_RenderCopy(renderer, texture, NULL, &DownR);
}

bool Button::isHover(int x, int y) const
{
	if (x < DownR.x)
		return false;
	if (x > DownR.x + DownR.w)
		return false;
	if (y < DownR.y)
		return false;
	if (y > DownR.y + DownR.h)
		return false;
	return true;
}

Button::~Button()
{
    SDL_DestroyTexture(this->texture);
}
