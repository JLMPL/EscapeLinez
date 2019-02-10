#include "Mouse.hpp"
#include <SDL2/SDL.h>

Mouse GlobalMouse;

void Mouse::update()
{
    GlobalMouse.left = false;
    GlobalMouse.right = false;

    Uint32 button = SDL_GetMouseState(&GlobalMouse.x, &GlobalMouse.y);

    if (button & SDL_BUTTON(SDL_BUTTON_LEFT))
        GlobalMouse.left = true;

    if (button & SDL_BUTTON(SDL_BUTTON_RIGHT))
        GlobalMouse.right = true;
}
