#include "Menu.hpp"
#include "Button.hpp"
#include "Settings.hpp"
#include "ConfigFile.hpp"
#include "TextureLoader.hpp"
#include "Renderer.hpp"
#include "OfflineMod.hpp"

void OfflineMod::init(SDL_Window* win)
{
    Window = win;

    m_background = loadTexture("data/Images/Main/lines.png");

    changeState = StateType::None;

    CatchMeIfYouCanButton.init("OfflineMod/CatchMe.png", "OfflineMod/CatchMeS.png", w / 2 - 150, h * 0.3);
    FindTheWayInsideButton.init("OfflineMod/FindThe.png", "OfflineMod/FindTheS.png", w / 2 - 150, h*0.4);
}

void OfflineMod::processEvent(const SDL_Event& event)
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
                    changeState = StateType::CatchMe;
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

void OfflineMod::update(float deltaTime)
{
    if (CatchMeIfYouCanButton.isPressed())
    {
        changeState = StateType::CatchMe;
    }
    else if (FindTheWayInsideButton.isPressed())
    {
        changeState = StateType::FindTheWayInside;
    }

}

void OfflineMod::draw()
{
    SDL_RenderCopy(GlobalRenderer, m_background, NULL, NULL);

    CatchMeIfYouCanButton.draw();
    FindTheWayInsideButton.draw();
}

void OfflineMod::quit()
{
    SDL_DestroyTexture(m_background);
}

StateType OfflineMod::nextState()
{
    return changeState;
}
