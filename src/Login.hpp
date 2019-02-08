#ifndef LOGIN_HPP
#define LOGIN_HPP
#include "Button.hpp"
#include "ConfigFile.hpp"
#include "Settings.hpp"
#include "State.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SFML/Network.hpp>
#include <iostream>

class Login : public State
{
    public:
        void init(SDL_Window* window, SDL_Renderer* renderer) override final;
        void quit() override final;

        void processEvent(const SDL_Event& event) override final;
        void update(float deltaTime) override final;
        void draw() override final;

        void send();

        StateType getType() const override final
        {
            return StateType::Login;
        }

        StateType nextState() override final;

        //const extern std::string ClientId;

    private:
        struct mouse
        {
            int x, y;
        };

        mouse m;

        int id;
        int changeState = 0;

        int w = GlobalConfigFile.getWidth(), h = GlobalConfigFile.getHeight();

        bool tab = 1;
        int err = 0;

        SDL_Surface     *wallpaper;

        SDL_Texture*    tex;

        TTF_Font*       Font;
        SDL_Color       FontColor;
        SDL_Color       FontColorRed;
        SDL_Surface*    FontSurface;
        SDL_Texture*    FontTexture;
        SDL_Rect        TitleRect;

        SDL_Surface*    FontSurfaceLoginNick;
        SDL_Texture*    FontTextureLoginNick;
        SDL_Rect        RectLoginNick;

        SDL_Surface*    FontSurfaceLoginPassword;
        SDL_Texture*    FontTextureLoginPassword;
        SDL_Rect        RectLoginPassword;

        SDL_Surface*    FontSurfaceLoginNickValue;
        SDL_Texture*    FontTextureLoginNickValue;

        SDL_Surface*    FontSurfaceLoginPasswordValue;
        SDL_Texture*    FontTextureLoginPasswordValue;

        std::string     Nick = "";
        std::string     Password = "";
        std::string     NickStandard = "Type your nick";
        std::string     PasswordStandard = "Type your password";
        std::string     PasswordCopy = "";
        SDL_Rect        NickRect;
        SDL_Rect        PasswordReck;

        Button          singleButton;
        Button          singleButtonS;
        Button          Error;
        Button          NoInternet;

};

#endif

