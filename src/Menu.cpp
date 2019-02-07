#include "Menu.hpp"
#include "Button.hpp"
#include "Settings.hpp"
#include "TextureLoader.hpp"
#include "ConfigFile.hpp"

void Menu::init(SDL_Window* win, SDL_Renderer* rend)
{    
    Window = win;
    Renderer = rend;

    wallpaper = IMG_Load("IMG/Main/lines.png");

    tex = SDL_CreateTextureFromSurface(Renderer, wallpaper);

    changeState = StateType::None;
    
    singleButton.init(loadTexture(Renderer, "IMG/Menu/sin.png"), w / 2 - 150, h*0.3);
    multiButton.init(loadTexture(Renderer, "IMG/Menu/mul.png"), w / 2 - 150, h*0.4);
    settingsButton.init(loadTexture(Renderer, "IMG/Menu/sett.png"), w / 2 - 150, h*0.5);
    exitButton.init(loadTexture(Renderer, "IMG/Menu/ex.png"), w / 2 - 150, h*0.6);

    singleButtonS.init(loadTexture(Renderer, "IMG/Menu/sinS.png"), w / 2 - 150, h*0.3);
    multiButtonS.init(loadTexture(Renderer, "IMG/Menu/mulS.png"), w / 2 - 150, h*0.4);
    settingsButtonS.init(loadTexture(Renderer, "IMG/Menu/settS.png"), w / 2 - 150, h*0.5);
    exitButtonS.init(loadTexture(Renderer, "IMG/Menu/exS.png"), w / 2 - 150, h*0.6);
}

void Menu::update(float deltaTime)
{    
    SDL_RenderCopy(Renderer, tex, NULL, NULL);

    singleButton.updateButton(Renderer);
    multiButton.updateButton(Renderer);
    settingsButton.updateButton(Renderer);
    exitButton.updateButton(Renderer);
    
    struct mouse
    {
        int x, y;
    };
    
    mouse m;
    
    Uint32 buton = SDL_GetMouseState(&m.x, &m.y); //przenieść do processEvent i zmienic wartowco hower dla przełącznika

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
        

    if (buton & SDL_BUTTON(SDL_BUTTON_LEFT) && singleButtonS.isHover(m.x, m.y))
        changeState = StateType::Singleplayer;
    
    if (buton & SDL_BUTTON(SDL_BUTTON_LEFT) && multiButtonS.isHover(m.x, m.y))
        changeState = StateType::WaitingRoom;
    
    if (buton & SDL_BUTTON(SDL_BUTTON_LEFT) && settingsButtonS.isHover(m.x, m.y))
        changeState = StateType::Settings;
    
    if (buton & SDL_BUTTON(SDL_BUTTON_LEFT) && exitButtonS.isHover(m.x, m.y))
        changeState = StateType::Exit;
    
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
