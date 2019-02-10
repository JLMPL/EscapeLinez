#include "Login.hpp"
#include "Button.hpp"
#include "Settings.hpp"
#include "TextureLoader.hpp"
#include "Network.hpp"
#include "Renderer.hpp"
#include "json.hpp"
#include "Text.hpp"
#include <time.h>
#include <math.h>
#include <vector>

using json = nlohmann::json;

void Login::init(SDL_Window* window)
{
    Window = window;

    wallpaper = IMG_Load("data/Images/Settings/linesSettings.png");

    tex = SDL_CreateTextureFromSurface(GlobalRenderer, wallpaper);

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    LoginButton.init("Login/Login2.png", "Login/LoginS.png", w / 2 - 150, h*0.6);
    Error.init("Login/ErrorLogin.png", "Login/ErrorLogin.png", w / 2 - 350, h*0.6, 700);
    NoInternet.init("Login/NoInternet.png", "Login/NoInternet.png", w / 2 - 350, h* 0.6, 700);

    new (&MySocketLogin) MySocket(servers[0].ip, 8000);

    m_login_font.loadFromFile("data/Fonts/login.ttf", 36);
    m_login_title_font.loadFromFile("data/Fonts/husa.ttf", 60);

    m_title.setFont(m_login_title_font);
    m_title.setString("Login");
    m_title.setColor({255,255,255,255});
    m_title.setPosition(w / 2 - (m_title.getRect().w / 2), 36);

    m_login_nick.setFont(m_login_font);
    m_login_nick.setString("Nick:");
    m_login_nick.setColor({255,255,255,255});
    m_login_nick.setPosition(w / 2 - (m_login_nick.getRect().w + 16), h * 0.4 - 70);

    m_login_password.setFont(m_login_font);
    m_login_password.setString("Password:");
    m_login_password.setColor({255,255,255,255});
    m_login_password.setPosition(w / 2 - (m_login_password.getRect().w + 16), h * 0.5 - 70);
    std::cout<<h*0.5-70<<std::endl;

    m_login_nick_value.setFont(m_login_font);
    m_login_nick_value.setPosition(w / 2, h * 0.4 - 70);
    m_login_nick_value.setColor({255, 255, 255, 255});

    m_login_password_value.setFont(m_login_font);
    m_login_password_value.setPosition(w / 2, h * 0.5 + 70);
    m_login_password_value.setColor({255, 255, 255, 255});
    std::cout<<h*0.5-70<<std::endl;

    m_login_nick_value_err.setFont(m_login_font);
    m_login_nick_value_err.setPosition(w / 2, h * 0.4 - 70);
    m_login_nick_value_err.setColor({255, 0, 0, 255});
    m_login_nick_value_err.setString("Type your nick");

    m_login_password_value_err.setFont(m_login_font);
    m_login_password_value_err.setPosition(w / 2, h * 0.5 + 70);
    m_login_password_value_err.setColor({255, 0, 0, 255});
    m_login_password_value_err.setString("Type your password");
}

void Login::update(float deltaTime)
{
    if (LoginButton.isPressed())
    {
        Login::send();
    }
    m_time += deltaTime;

    int f = m_time;
    if(f%2 == 1)
    {
        if(tab)
        {
            m_login_nick_value.setInputMark();
        }
        else
        {
            m_login_password_value.setInputMark();
        }
    }
    else
    {
        if(tab)
        {
            m_login_nick_value.deleteInputMark();
        }
        else
        {
            m_login_password_value.deleteInputMark();
        }
    }
}

void Login::draw()
{
    SDL_RenderCopy(GlobalRenderer, tex, NULL, NULL);

    switch(err)
    {
        case 0:
            LoginButton.draw();
            break;
        case 1:
            Error.draw();
            break;
        case 2:
            NoInternet.draw();
            break;
    }
    m_title.draw();
    m_login_nick.draw();
    m_login_password.draw();

    if (m_login_nick_value.getString() != "")
    {
        m_login_nick_value.draw();
    }
    else
    {
        m_login_nick_value_err.draw();
    }

    if (m_login_password_value.getString() != "")
    {
        m_login_password_value.draw();
    }
    else
    {
        m_login_password_value_err.draw();
    }

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
                if (m_login_nick_value.getString().size() > 0)
                {
                    m_login_nick_value.popBack();
                    err = 0;
                }
            }

            else
            {
                if (m_login_password_value.getString().size() > 0)
                {
                    m_login_password_value.popBack();
                    err = 0;
                }
            }
        }
    }

    if (event.type == SDL_TEXTINPUT)
    {
        if (tab)
        {
            m_login_nick_value.pushBack(*event.text.text);
            err = 0;
        }
        else
        {
            m_login_password_value.pushBack(*event.text.text);
            err = 0;

            if (m_login_password_value.getString().size() > 0)
            {
                m_login_password_value.hide();
            }
        }
    }
}

void Login::send() //<<<<<<<<<<<<<<<<-------- Network.cpp
{
    std::string LoginP = m_login_nick_value.getString() + "," + m_login_password_value.getString() + "," + std::to_string(h);

    MySocketLogin.send(LoginP);

    std::string answare = MySocketLogin.get();

    json parser;

    switch(MySocketLogin.getStatus())
    {
        case 0://< The socket has sent / received the data
            parser = json::parse(answare);
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
