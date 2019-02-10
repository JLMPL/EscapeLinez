#include "Menu.hpp"
#include "Button.hpp"
#include "Settings.hpp"
#include "ConfigFile.hpp"
#include "TextureLoader.hpp"
#include "Renderer.hpp"

void Menu::init(SDL_Window* win)
{
    Window = win;

    m_background = loadTexture("data/Images/Main/lines.png");

    changeState = StateType::None;

    singleButton.init("Menu/sin.png", "Menu/sinS.png", w / 2 - 150, h * 0.3);
    multiButton.init("Menu/mul.png", "Menu/mulS.png", w / 2 - 150, h*0.4);
    settingsButton.init("Menu/sett.png", "Menu/settS.png", w / 2 - 150, h*0.5);
    exitButton.init("Menu/ex.png", "Menu/exS.png", w / 2 - 150, h*0.6);
}

void Menu::processEvent(const SDL_Event& event)
{
    /*
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_TAB)
        {
            hover++;
        }
        if (event.key.keysym.sym == SDLK_DOWN)
        {
            hover++;
        }
        if (event.key.keysym.sym == SDLK_UP)
        {
            hover--;
        }
        if (event.key.keysym.sym == SDLK_RETURN)
        {
            switch(hover % 5)
            {
                case 1:
                    changeState = StateType::Singleplayer;
                break;
                case 2:
                    changeState = StateType::WaitingRoom;
                break;
                case 3:
                    changeState = StateType::Settings;
                break;
                case 4:
                    changeState = StateType::Exit;
                break;
            }
        }
    }
    */
}

void Menu::update(float deltaTime)
{
    if (singleButton.isPressed())
    {
        changeState = StateType::Singleplayer;
    }
    else if (multiButton.isPressed())
    {
        changeState = StateType::WaitingRoom;
    }
    else if (settingsButton.isPressed())
    {
        changeState = StateType::Settings;
    }
    else if (exitButton.isPressed())
    {
        changeState = StateType::Exit;
    }
}

void Menu::draw()
{
    SDL_RenderCopy(GlobalRenderer, m_background, NULL, NULL);

    singleButton.draw();
    multiButton.draw();
    settingsButton.draw();
    exitButton.draw();
}

void Menu::quit()
{
    SDL_DestroyTexture(m_background);
}

StateType Menu::nextState()
{
    return changeState;
}
