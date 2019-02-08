#include "Menu.hpp"
#include "Button.hpp"
#include "Settings.hpp"
#include "TextureLoader.hpp"
#include "ConfigFile.hpp"

void Menu::init(SDL_Window* win, SDL_Renderer* rend)
{
    Window = win;
    Renderer = rend;

    wallpaper = IMG_Load("data/Images/Main/lines.png");

    tex = SDL_CreateTextureFromSurface(Renderer, wallpaper);

    changeState = StateType::None;

    singleButton.init(loadTexture(Renderer, "data/Images/Menu/sin.png"), w / 2 - 150, h*0.3);
    multiButton.init(loadTexture(Renderer, "data/Images/Menu/mul.png"), w / 2 - 150, h*0.4);
    settingsButton.init(loadTexture(Renderer, "data/Images/Menu/sett.png"), w / 2 - 150, h*0.5);
    exitButton.init(loadTexture(Renderer, "data/Images/Menu/ex.png"), w / 2 - 150, h*0.7);

    singleButtonS.init(loadTexture(Renderer, "data/Images/Menu/sinS.png"), w / 2 - 150, h*0.3);
    multiButtonS.init(loadTexture(Renderer, "data/Images/Menu/mulS.png"), w / 2 - 150, h*0.4);
    settingsButtonS.init(loadTexture(Renderer, "data/Images/Menu/settS.png"), w / 2 - 150, h*0.5);
    exitButtonS.init(loadTexture(Renderer, "data/Images/Menu/exS.png"), w / 2 - 150, h*0.7);
}

void Menu::update(float deltaTime)
{
    SDL_RenderCopy(Renderer, tex, NULL, NULL);

    m.start();

    singleButton.updateButton(Renderer);
    multiButton.updateButton(Renderer);
    settingsButton.updateButton(Renderer);
    exitButton.updateButton(Renderer);

    if (singleButtonS.isHover(m.x, m.y))
    {
        singleButtonS.updateButton(Renderer);
        hover = 0;
    }

    if (multiButtonS.isHover(m.x, m.y))
    {
        multiButtonS.updateButton(Renderer);
        hover = 0;
    }

    if (settingsButtonS.isHover(m.x, m.y))
    {
        settingsButtonS.updateButton(Renderer);
        hover = 0;
    }

    if (exitButtonS.isHover(m.x, m.y))
    {
        exitButtonS.updateButton(Renderer);
        hover = 0;
    }

    if (hover % 5 != 0)
    {
        switch(hover % 5)
        {
            case 1:
                singleButtonS.updateButton(Renderer);
            break;
            case 2:
                multiButtonS.updateButton(Renderer);
            break;
            case 3:
                settingsButtonS.updateButton(Renderer);
            break;
            case 4:
                exitButtonS.updateButton(Renderer);
            break;
        }
    }

}

void Menu::processEvent(const SDL_Event& event)
{
    if (singleButtonS.isClicked(m.x, m.y, event))
        changeState = StateType::Singleplayer;

    if (multiButtonS.isClicked(m.x, m.y, event))
        changeState = StateType::WaitingRoom;

    if (settingsButtonS.isClicked(m.x, m.y, event))
        changeState = StateType::Settings;

    if (exitButtonS.isClicked(m.x, m.y, event))
        changeState = StateType::Exit;

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

}

void Menu::AfterRendering()
{

}

void Menu::quit()
{
    SDL_DestroyTexture(tex);
}

StateType Menu::nextState()
{
    return changeState;
}
