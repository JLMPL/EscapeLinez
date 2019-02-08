#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include "State.hpp"
#include "Button.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
//#include <X11/Xlib.h>

class Settings : public State
{
    public:
        ~Settings();
        void init(SDL_Window* win, SDL_Renderer* rend) override final;
        void quit() override final;

        void processEvent(const SDL_Event& event) override final;
        void update(float deltaTime) override final;
        void draw() override final;

        void setRenderer(SDL_Renderer* renderer);

        StateType nextState() override final;

        StateType getType() const override final
        {
            return StateType::Settings;
        }

    private:

        void initBackground();
        void initTitle();

        void initResolutions();
        void updateResolutions(const std::string& text);

        void initFullscreen();
        void updateFullscreen(const std::string& text);

        void initMusic();
        void updateMusic(const std::string& text);

        void initDifficulty();
        void updateDifficulty(const std::string& text);

        void updateSelectionRect();

    public:
        void setWindow(SDL_Window* window);

    private:
        struct Text
        {
            SDL_Texture* Texture;
            SDL_Rect Rect;

            SDL_Texture* Current;
            SDL_Rect CurrRect;
        };

        int changeState = 0;

        std::string     res;

        SDL_Texture*    Wallpaper;

        TTF_Font*       Font;

        SDL_Texture*    TitleTexture;
        SDL_Rect        TitleRect;

        Text            Resolutions;
        Text            Fullscreen;
        Text            Music;
        Text            Difficulty;

        SDL_Rect        SelectionRect;

        int             Selection = 0;
        int             CurrentResolution;
        int             CurrentDifficulty = 0;
        int             w,h;
        int             toUpdateWidth = 0;
        int             toUpdateHeight = 0;

        Button          Save;
        Button          SaveS;

        SDL_DisplayMode dm;

        // Display*        d = XOpenDisplay(NULL);
        // Screen*         screen = DefaultScreenOfDisplay(d);

};

#endif

/*

Resolution
Fullscreen
Music ON/OFF
Difficulty
*/
