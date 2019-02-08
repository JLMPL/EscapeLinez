#include "Login.hpp"
#include "Button.hpp"
#include "Settings.hpp"
#include "TextureLoader.hpp"
#include "Network.hpp"
#include <time.h>
#include <vector>
#include "jsonP.hpp"

using json = nlohmann::json;

void Login::init(SDL_Window* window, SDL_Renderer* renderer)
{
    Renderer = renderer;
    Window = window;

    wallpaper = IMG_Load("data/Images/Settings/linesSettings.png");

    tex = SDL_CreateTextureFromSurface(Renderer, wallpaper);

    Font = TTF_OpenFont("data/Fonts/login.ttf", 36);
    FontColor = {255, 255, 254};
    FontColorRed = {192, 0, 0};
    FontSurface = TTF_RenderText_Solid(Font, "Login", FontColor);
    FontTexture = SDL_CreateTextureFromSurface(Renderer, FontSurface);

    FontSurfaceLoginNick = TTF_RenderText_Solid(Font, "Nick:", FontColor);
    FontTextureLoginNick = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginNick);

    FontSurfaceLoginPassword = TTF_RenderText_Solid(Font, "Password:", FontColor);
    FontTextureLoginPassword = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginPassword);

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    TitleRect.x = w / 2 - FontSurface->w / 2;
    TitleRect.y = 0;
    TitleRect.w = FontSurface->w;
    TitleRect.h = FontSurface->h;

    RectLoginNick.x = w / 2 - (FontSurfaceLoginNick->w + 16);
    RectLoginNick.y = h * 0.3 - 70;
    RectLoginNick.w = FontSurfaceLoginNick->w;
    RectLoginNick.h = FontSurfaceLoginNick->h;

    RectLoginPassword.x = w / 2 - (FontSurfaceLoginPassword->w + 16);
    RectLoginPassword.y = h * 0.3 + 70;
    RectLoginPassword.w = FontSurfaceLoginPassword->w;
    RectLoginPassword.h = FontSurfaceLoginPassword->h;

    NickRect.x = w / 2;
    NickRect.y = h * 0.3 - 70;
    NickRect.w = 10;
    NickRect.h = 10;

    PasswordReck.x = w / 2;
    PasswordReck.y = h * 0.3 + 70;
    PasswordReck.w = 10;
    PasswordReck.h = 10;

    singleButton.init("Login/Login2.png", "Login/LoginS.png", w / 2 - 150, h*0.6);
    Error.init("Login/ErrorLogin.png", "Login/ErrorLogin.png", w / 2 - 350, h*0.6, 700);
    NoInternet.init("Login/NoInternet.png", "Login/NoInternet.png", w / 2 - 350, h* 0.6, 700);

    new (&MySocketLogin) MySocket(servers[0].ip, 8000);
}

void Login::update(float deltaTime)
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);

    SDL_RenderCopy(Renderer, tex, NULL, NULL);
    SDL_RenderCopy(Renderer, FontTexture, NULL, &TitleRect);
    SDL_RenderCopy(Renderer, FontTextureLoginNick, NULL, &RectLoginNick);
    SDL_RenderCopy(Renderer, FontTextureLoginPassword, NULL, &RectLoginPassword);
    SDL_RenderCopy(Renderer, FontTextureLoginNickValue, NULL, &NickRect);
    SDL_RenderCopy(Renderer, FontTextureLoginPasswordValue, NULL, &PasswordReck);

    switch(err)
    {
        case 0:
            singleButton.draw();
            break;
        case 1:
            Error.draw();
            break;
        case 2:
            NoInternet.draw();
            break;
    }
}

void Login::AfterRendering()
{

}

void Login::processEvent(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        SDL_StartTextInput();

        if (event.key.keysym.sym == SDLK_TAB)
        {
            tab = !tab;
        }

        if( event.key.keysym.sym == SDLK_RETURN)
        {
            Login::send();
        }

        if( event.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (tab)
            {
                if (Nick.size() > 0)
                {
                    Nick.pop_back();
                    err = 0;
                }

                if (Nick != "")
                {
                    FontSurfaceLoginNickValue = TTF_RenderText_Solid(Font, Nick.c_str(), FontColor);
                    FontTextureLoginNickValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginNickValue);
                }
                else
                {
                    FontSurfaceLoginNickValue = TTF_RenderText_Solid(Font, NickStandard.c_str(), FontColorRed);
                    FontTextureLoginNickValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginNickValue);
                }

                NickRect.w = FontSurfaceLoginNickValue->w;
                NickRect.h = FontSurfaceLoginNickValue->h;
            }

            else
            {
                if (Password.size() > 0)
                {
                    Password.pop_back();
                    PasswordCopy.pop_back();
                    err = 0;
                }

                if (Password != "")
                {
                    FontSurfaceLoginPasswordValue = TTF_RenderText_Solid(Font, PasswordCopy.c_str(), FontColor);
                    FontTextureLoginPasswordValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginPasswordValue);
                }
                else
                {
                    FontSurfaceLoginPasswordValue = TTF_RenderText_Solid(Font, PasswordStandard.c_str(), FontColorRed);
                    FontTextureLoginPasswordValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginPasswordValue);
                }

                PasswordReck.w = FontSurfaceLoginPasswordValue->w;
                PasswordReck.h = FontSurfaceLoginPasswordValue->h;
            }
        }
    }

    if (event.type == SDL_TEXTINPUT)
    {
        if (tab)
        {
            Nick += event.text.text;
            err = 0;
        }
        else
        {
            Password += event.text.text;
            PasswordCopy = Password;
            err = 0;

            if (PasswordCopy.size() > 1)
            {
                for (int i = PasswordCopy.size() - 2; i >= 0; i--)
                {
                    PasswordCopy[i] = '#';
                }
            }
        }

        if (Nick != "")
        {
            FontSurfaceLoginNickValue = TTF_RenderText_Solid(Font, Nick.c_str(), FontColor);
            FontTextureLoginNickValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginNickValue);
        }
        else
        {
            FontSurfaceLoginNickValue = TTF_RenderText_Solid(Font, NickStandard.c_str(), FontColorRed);
            FontTextureLoginNickValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginNickValue);
        }

        if (Password != "")
        {
            FontSurfaceLoginPasswordValue = TTF_RenderText_Solid(Font, PasswordCopy.c_str(), FontColor);
            FontTextureLoginPasswordValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginPasswordValue);
        }
        else
        {
            FontSurfaceLoginPasswordValue = TTF_RenderText_Solid(Font, PasswordStandard.c_str(), FontColorRed);
            FontTextureLoginPasswordValue = SDL_CreateTextureFromSurface(Renderer, FontSurfaceLoginPasswordValue);
        }

        NickRect.w = FontSurfaceLoginNickValue->w;
        NickRect.h = FontSurfaceLoginNickValue->h;
        PasswordReck.w = FontSurfaceLoginPasswordValue->w;
        PasswordReck.h = FontSurfaceLoginPasswordValue->h;
    }
}

void Login::send() //<<<<<<<<<<<<<<<<-------- Network.cpp
{
    std::string LoginP = Nick + "," + Password + "," + std::to_string(h);

    MySocketLogin.send(LoginP);

    std::string answare = MySocketLogin.get();

    json parser = json::parse(answare);

    switch(MySocketLogin.getStatus())
    {
        case 0://< The socket has sent / received the data
            if (parser["status"].get<int>() == 200)
            {
                changeState = 3;
                id = parser["id"].get<int>();
                ClientId = &id;
            }
            else
                err = 1;
        break;
        case 1://< The socket is not ready to send / receive data yet
            std::cout<<"Login.cpp: socket is not ready yet"<<std::endl;
        break;
        case 2://< The socket sent a part of the data
            std::cout<<"Login.cpp: The socket sent a part of the data"<<std::endl;
        break;
        case 3://< The TCP socket has been disconnected
            std::cout<<"Login.cpp: The TCP socket has been disconnected"<<std::endl;
        break;
        case 4://< An unexpected error happened
            std::cout<<"Login.cpp: An unexpected error happened"<<std::endl;
            err = 2;
        break;
    }
}

void Login::quit()
{

}

StateType Login::nextState()
{
    if (changeState == 1)
        return StateType::Singleplayer;
    if (changeState == 2)
        return StateType::Multiplayer;
    if (changeState == 3)
        return StateType::Menu;
    if (changeState == 4)
        return StateType::Exit;
    if (changeState == 0)
        return StateType::None;
}

