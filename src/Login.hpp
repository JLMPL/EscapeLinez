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

#include "Text.hpp"

class Login : public State
{
public:
    void init(SDL_Window* window) override final;
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

private:
    int id;
    int changeState = 0;
    float m_time = 0.f;

    int w = GlobalConfigFile.getWidth(), h = GlobalConfigFile.getHeight();

    bool tab = 1;
    int err = 0;

    std::string m_loginData[2];

    std::string m_loginString;
    std::string m_passwordString;

    Font m_loginFont;
    Font m_loginTitleFont;

    Text m_title;
    Text m_loginNick;
    Text m_loginPassword;

    Text m_loginNickValue;
    Text m_loginPasswordValue;

    SDL_Texture*    wallpaper;

    Button          LoginButton;
    Button          Error;
    Button          NoInternet;
};

#endif
