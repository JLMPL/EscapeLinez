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

//< The socket has sent / received the data
//< The socket is not ready to send / receive data yet
//< The socket sent a part of the data
//< The TCP socket has been disconnected
//< An unexpected error happened

void Login::init(SDL_Window* window)
{
    Window = window;

    wallpaper = loadTexture("data/Images/Settings/linesSettings.png");

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    LoginButton.init("Login/Login2.png", "Login/LoginS.png", w / 2 - 150, h*0.6);
    Error.init("Login/ErrorLogin.png", "Login/ErrorLogin.png", w / 2 - 350, h*0.6, 700);
    NoInternet.init("Login/NoInternet.png", "Login/NoInternet.png", w / 2 - 350, h*0.6, 700);

    new (&MySocketLogin) MySocket(servers[0].ip, 8000);

    m_loginFont.loadFromFile("data/Fonts/login.ttf", 36);
    m_loginTitleFont.loadFromFile("data/Fonts/husa.ttf", 60);

    m_title.setFont(m_loginTitleFont);
    m_title.setString("Login");
    m_title.setPosition(w / 2 - (m_title.getRect().w / 2), 36);

    m_loginNick.setFont(m_loginFont);
    m_loginNick.setString("Nick:");
    m_loginNick.setPosition(w / 2 - (m_loginNick.getRect().w + 16), h * 0.4 - 70);

    m_loginPassword.setFont(m_loginFont);
    m_loginPassword.setString("Password:");
    m_loginPassword.setPosition(w / 2 - (m_loginPassword.getRect().w + 16), h * 0.5 - 70);

    m_loginNickValue.setFont(m_loginFont);
    m_loginNickValue.setPosition(w / 2, h * 0.4 - 70);
    m_loginNickValue.setCaret(true);

    m_loginPasswordValue.setTextType(TextType::Password);
    m_loginPasswordValue.setFont(m_loginFont);
    m_loginPasswordValue.setPosition(w / 2, h * 0.5-70);
}

void Login::update(float deltaTime)
{
    if (LoginButton.isPressed())
    {
        Login::send();
    }

    m_loginNickValue.update(deltaTime);
    m_loginPasswordValue.update(deltaTime);
}

void Login::draw()
{
    SDL_RenderCopy(GlobalRenderer, wallpaper, NULL, NULL);

    switch (err)
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
    m_loginNick.draw();
    m_loginPassword.draw();

    if (!m_loginData[1].empty())
    {
        m_loginNickValue.setColor({255,255,255,255});
        m_loginNickValue.setString(m_loginData[1]);
    }
    else
    {
        m_loginNickValue.setColor({255,0,0,255});
        m_loginNickValue.setString("your nick");
    }

    m_loginNickValue.draw();

    if (!m_loginData[0].empty())
    {
        m_loginPasswordValue.setTextType(TextType::Password);
        m_loginPasswordValue.setColor({255,255,255,255});
        m_loginPasswordValue.setString(m_loginData[0]);
    }
    else
    {
        m_loginPasswordValue.setTextType(TextType::Regular);
        m_loginPasswordValue.setColor({255,0,0,255});
        m_loginPasswordValue.setString("your password");
    }

    m_loginPasswordValue.draw();
}

void Login::processEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        SDL_StartTextInput();

        if (event.key.keysym.sym == SDLK_TAB)
        {
            tab = !tab;

            if (tab)
            {
                m_loginNickValue.setCaret(true);
                m_loginPasswordValue.setCaret(false);
            }
            else
            {
                m_loginNickValue.setCaret(false);
                m_loginPasswordValue.setCaret(true);
            }
        }

        if (event.key.keysym.sym == SDLK_RETURN)
        {
            Login::send();
        }

        if (event.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (m_loginData[tab].size() > 0)
            {
                m_loginData[tab].pop_back();
                err = 0;
            }
        }
    }

    if (event.type == SDL_TEXTINPUT)
    {
        m_loginData[tab] += event.text.text;
        err = 0;
    }
}

void Login::send() //<<<<<<<<<<<<<<<<-------- Network.cpp
{
    std::string LoginP = m_loginNickValue.getString() + "," + m_loginPasswordValue.getString() + "," + std::to_string(h);

    MySocketLogin.send(LoginP);

    std::string answare = MySocketLogin.get();

    json parser;

    switch(MySocketLogin.getStatus())
    {
        case SOCKET_STATUS_OK:
        {
            parser = json::parse(answare);
            if (parser["status"].get<int>() == 200)
            {
                changeState = 3;
                id = parser["id"].get<int>();
                ClientId = &id;
            }
            else
                err = 1;
        }
        break;

        case SOCKET_STATUS_NOT_READY:
            std::cout<<"Login.cpp: socket is not ready yet"<<std::endl;
            break;
        case SOCKET_STATUS_PARTIAL:
            std::cout<<"Login.cpp: The socket sent a part of the data"<<std::endl;
            break;
        case SOCKET_STATUS_DISCONNECTED:
            std::cout<<"Login.cpp: The TCP socket has been disconnected"<<std::endl;
            break;
        case SOCKET_STATUS_UNEXPECTED_ERROR:
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
