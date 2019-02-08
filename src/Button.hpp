#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Button
{
    public:
        Button() = default;
        ~Button();

        void init(SDL_Texture* texture, int x, int y, int w = 300);
        void updateButton(SDL_Renderer *renderer);

        bool isHover(int x, int y) const;
        bool isClicked(int x, int y, const SDL_Event& event);

    private:
    	SDL_Surface 		*imcopy;
        SDL_Texture         *texture;
        SDL_Rect            DownR;

};

struct mouse
{
    int x, y;
    void start()
    {
        SDL_GetMouseState(&this->x, &this->y);
    }
};

extern mouse m;

#endif /* BUTTON_HPP */
