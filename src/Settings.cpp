#include "Settings.hpp"
#include "Button.hpp"
#include "TextureLoader.hpp"
#include "ConfigFile.hpp"
#include "Renderer.hpp"

int numReses = 5;
static int ResolutionsTable[5][2] =
{
    {1280, 720},
    {1366, 768},
    {1600, 900},
    {1920, 1080},
    {2560, 1440}
};

static std::string Difficulties[3] =
{
    "Easy",
    "Medium",
    "Hard"
};

Settings::~Settings()
{
    SDL_DestroyTexture(Wallpaper);
    SDL_DestroyTexture(TitleTexture);
}

void Settings::initBackground()
{
    SDL_Surface* surf = IMG_Load("data/Images/Settings/linesSettings.png");
    Wallpaper = SDL_CreateTextureFromSurface(GlobalRenderer, surf);
    SDL_FreeSurface(surf);
}

void Settings::initTitle()
{
    SDL_Color fontColor = {255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(Font, "Settings", fontColor);
    TitleTexture = SDL_CreateTextureFromSurface(GlobalRenderer, titleSurface);

    int w = GlobalConfigFile.getWidth();
    int h = GlobalConfigFile.getHeight();

    TitleRect.x = w / 2 - 100;
    TitleRect.y = 0;
    TitleRect.w = titleSurface->w;
    TitleRect.h = titleSurface->h;

    SDL_FreeSurface(titleSurface);
}

void Settings::initResolutions()
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, "Resolution:", {255,255,255});
    Resolutions.Texture = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Resolutions.Rect.x = GlobalConfigFile.getWidth()/2 - (surf->w + 16);
    Resolutions.Rect.y = 200;
    Resolutions.Rect.w = surf->w;
    Resolutions.Rect.h = surf->h;

    SDL_FreeSurface(surf);

    res = std::to_string(GlobalConfigFile.getWidth()) + "x" + std::to_string(GlobalConfigFile.getHeight());
    updateResolutions(res);
}

void Settings::updateResolutions(const std::string& text)
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, text.c_str(), {255,255,255});
    Resolutions.Current = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Resolutions.CurrRect.x = GlobalConfigFile.getWidth()/2 + 16;
    Resolutions.CurrRect.y = 200;
    Resolutions.CurrRect.w = surf->w;
    Resolutions.CurrRect.h = surf->h;

    SDL_FreeSurface(surf);
}

void Settings::initFullscreen()
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, "Fullscreen:", {255,255,255});
    Fullscreen.Texture = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Fullscreen.Rect.x = GlobalConfigFile.getWidth()/2 - (surf->w + 16);
    Fullscreen.Rect.y = 300;
    Fullscreen.Rect.w = surf->w;
    Fullscreen.Rect.h = surf->h;

    SDL_FreeSurface(surf);

    updateFullscreen((GlobalConfigFile.isFullscreen()) ? "ON" : "OFF");
}

void Settings::updateFullscreen(const std::string& text)
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, text.c_str(), {255,255,255});
    Fullscreen.Current = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Fullscreen.CurrRect.x = GlobalConfigFile.getWidth()/2 + 16;
    Fullscreen.CurrRect.y = 300;
    Fullscreen.CurrRect.w = surf->w;
    Fullscreen.CurrRect.h = surf->h;

    SDL_FreeSurface(surf);
}

void Settings::initMusic()
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, "Music:", {255,255,255});
    Music.Texture = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Music.Rect.x = GlobalConfigFile.getWidth()/2 - (surf->w + 16);
    Music.Rect.y = 400;
    Music.Rect.w = surf->w;
    Music.Rect.h = surf->h;

    SDL_FreeSurface(surf);

    updateMusic("ON");
}

void Settings::updateMusic(const std::string& text)
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, text.c_str(), {255,255,255});
    Music.Current = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Music.CurrRect.x = GlobalConfigFile.getWidth()/2 + 16;
    Music.CurrRect.y = 400;
    Music.CurrRect.w = surf->w;
    Music.CurrRect.h = surf->h;

    SDL_FreeSurface(surf);
}

void Settings::initDifficulty()
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, "Difficulty:", {255,255,255});
    Difficulty.Texture = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Difficulty.Rect.x = GlobalConfigFile.getWidth()/2 - (surf->w + 16);
    Difficulty.Rect.y = 500;
    Difficulty.Rect.w = surf->w;
    Difficulty.Rect.h = surf->h;

    SDL_FreeSurface(surf);

    updateDifficulty("Easy");
}

void Settings::updateDifficulty(const std::string& text)
{
    SDL_Surface* surf = TTF_RenderText_Solid(Font, text.c_str(), {255,255,255});
    Difficulty.Current = SDL_CreateTextureFromSurface(GlobalRenderer, surf);

    Difficulty.CurrRect.x = GlobalConfigFile.getWidth()/2 + 16;
    Difficulty.CurrRect.y = 500;
    Difficulty.CurrRect.w = surf->w;
    Difficulty.CurrRect.h = surf->h;

    SDL_FreeSurface(surf);
}

void Settings::init(SDL_Window* win)
{
    Window = win;

    changeState = 0;
    w = GlobalConfigFile.getWidth();
    h = GlobalConfigFile.getHeight();

    switch(w)
    {
        case 1280: CurrentResolution = 0;
        case 1366: CurrentResolution = 1;
        case 1600: CurrentResolution = 2;
        case 1920: CurrentResolution = 3;
        case 2560: CurrentResolution = 4;
    }



    Font = TTF_OpenFont("data/Fonts/husa.ttf", 36);
    if (!Font)
    {
        std::cout << "Error: Could not load husa.ttf" << std::endl;
    }

    initBackground();
    initTitle();

    initResolutions();
    initFullscreen();
    initMusic();
    initDifficulty();

    SelectionRect = {0,0,512,48};

    Save.init("Settings/savee.png", "Settings/saveee.png", w / 2 - 150, h*0.8);

    // updateResolutions(
    //     std::to_string(ResolutionsTable[CurrentResolution][0]) +
    //     "x" +
    //     std::to_string(ResolutionsTable[CurrentResolution][1])
    // );

    // updateFullscreen((GlobalConfigFile.isFullscreen()) ? "ON" : "OFF");
    updateMusic((GlobalConfigFile.isMusic()) ? "ON" : "OFF");

    updateDifficulty(Difficulties[GlobalConfigFile.getDifficulty()]);
}

void Settings::processEvent(const SDL_Event& event)
{
    SDL_GetDesktopDisplayMode(0, &dm);
    // GetWindowRect(hDesktop, &desktop);

    if (Save.isPressed())
    {
        GlobalConfigFile.setWidth(toUpdateWidth);
        GlobalConfigFile.setHeight(toUpdateHeight);

        SDL_SetWindowSize(Window, GlobalConfigFile.getWidth(), GlobalConfigFile.getHeight());
        // SDL_RenderSetLogicalSize(Renderer, GlobalConfigFile.getWidth(), GlobalConfigFile.getHeight());
        // SDL_RenderSetScale(Renderer, float(GlobalConfigFile.getWidth()) / 1366.f, float(GlobalConfigFile.getHeight()) / 768.f);
        GlobalConfigFile.save();
        changeState = 3;
        //system("./script.sh");
        //printf("%s1\n");

    }

    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_RETURN)
        {
            GlobalConfigFile.setWidth(toUpdateWidth);
            GlobalConfigFile.setHeight(toUpdateHeight);
            SDL_SetWindowSize(Window, GlobalConfigFile.getWidth(), GlobalConfigFile.getHeight());
            GlobalConfigFile.save();
            changeState = 3;
        }
        if (event.key.keysym.sym == SDLK_UP)
        {
            Selection--;

            if (Selection < 0)
                Selection = 0;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            Selection++;

            if (Selection > 3)
                Selection = 3;
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            switch (Selection)
            {
                case 0:
                {
                    CurrentResolution--;

                    if (CurrentResolution < 0)
                        CurrentResolution = 0;



                    // while (ResolutionsTable[CurrentResolution][0] > desktop.right)
                    //     CurrentResolution--;

                    toUpdateWidth = ResolutionsTable[CurrentResolution][0];
                    toUpdateHeight = ResolutionsTable[CurrentResolution][1];

                    updateResolutions(
                        std::to_string(ResolutionsTable[CurrentResolution][0]) +
                        "x" +
                        std::to_string(ResolutionsTable[CurrentResolution][1])
                    );
                }
                break;
                case 1:
                    GlobalConfigFile.setFullscreen(!GlobalConfigFile.isFullscreen());
                    updateFullscreen((GlobalConfigFile.isFullscreen()) ? "ON" : "OFF");
                    break;
                case 2:
                    GlobalConfigFile.setMusic(!GlobalConfigFile.isMusic());
                    updateMusic((GlobalConfigFile.isMusic()) ? "ON" : "OFF");
                    break;
                case 3:
                {
                    GlobalConfigFile.setDifficulty(GlobalConfigFile.getDifficulty() -1);

                    if (GlobalConfigFile.getDifficulty() < 0)
                        GlobalConfigFile.setDifficulty(0);

                    updateDifficulty(Difficulties[GlobalConfigFile.getDifficulty()]);
                }
                break;
            }
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            switch (Selection)
            {
                case 0:
                {
                    CurrentResolution++;

                    SDL_DisplayMode dm;
                    SDL_GetCurrentDisplayMode(0, &dm);

                    if (CurrentResolution > 4)
                        CurrentResolution = 4;


                    toUpdateWidth = ResolutionsTable[CurrentResolution][0];
                    toUpdateHeight = ResolutionsTable[CurrentResolution][1];

                    updateResolutions(
                        std::to_string(ResolutionsTable[CurrentResolution][0]) +
                        "x" +
                        std::to_string(ResolutionsTable[CurrentResolution][1])
                    );
                }
                break;
                case 1:
                    GlobalConfigFile.setFullscreen(!GlobalConfigFile.isFullscreen());
                    updateFullscreen((GlobalConfigFile.isFullscreen()) ? "ON" : "OFF");
                    break;
                case 2:
                    GlobalConfigFile.setMusic(!GlobalConfigFile.isMusic());
                    updateMusic((GlobalConfigFile.isMusic()) ? "ON" : "OFF");
                    break;
                case 3:
                {
                    GlobalConfigFile.setDifficulty(GlobalConfigFile.getDifficulty() +1);

                    if (GlobalConfigFile.getDifficulty() > 2)
                        GlobalConfigFile.setDifficulty(2);

                    updateDifficulty(Difficulties[GlobalConfigFile.getDifficulty()]);
                }
                break;
            }
        }
        GlobalConfigFile.save();
    }
}

void Settings::updateSelectionRect()
{
    SelectionRect.y = 200 + Selection * 100;
    SelectionRect.x = GlobalConfigFile.getWidth()/2 - 256;
}

void Settings::update(float deltaTime)
{
    bool green = false;

    SDL_Rect confirm;

    updateSelectionRect();

    if (Save.isPressed())
    {
        GlobalConfigFile.setWidth(toUpdateWidth);
        GlobalConfigFile.setHeight(toUpdateHeight);

        SDL_SetWindowSize(Window, GlobalConfigFile.getWidth(), GlobalConfigFile.getHeight());
        // SDL_RenderSetLogicalSize(Renderer, GlobalConfigFile.getWidth(), GlobalConfigFile.getHeight());
        // SDL_RenderSetScale(Renderer, float(GlobalConfigFile.getWidth()) / 1366.f, float(GlobalConfigFile.getHeight()) / 768.f);
        GlobalConfigFile.save();
        changeState = 3;
        //system("./script.sh");
        //printf("%s1\n");
    }
}

void Settings::draw()
{
    SDL_SetRenderDrawColor(GlobalRenderer, 0, 100, 100, 0);

    SDL_RenderCopy(GlobalRenderer, Wallpaper, NULL, NULL);
    SDL_RenderCopy(GlobalRenderer, TitleTexture, NULL, &TitleRect);

    SDL_SetRenderDrawColor(GlobalRenderer, 32, 64, 192, 0);
    SDL_RenderFillRect(GlobalRenderer, &SelectionRect);

    SDL_RenderCopy(GlobalRenderer, Resolutions.Texture, NULL, &Resolutions.Rect);
    SDL_RenderCopy(GlobalRenderer, Resolutions.Current, NULL, &Resolutions.CurrRect);

    SDL_RenderCopy(GlobalRenderer, Fullscreen.Texture, NULL, &Fullscreen.Rect);
    SDL_RenderCopy(GlobalRenderer, Fullscreen.Current, NULL, &Fullscreen.CurrRect);

    SDL_RenderCopy(GlobalRenderer, Music.Texture, NULL, &Music.Rect);
    SDL_RenderCopy(GlobalRenderer, Music.Current, NULL, &Music.CurrRect);

    SDL_RenderCopy(GlobalRenderer, Difficulty.Texture, NULL, &Difficulty.Rect);
    SDL_RenderCopy(GlobalRenderer, Difficulty.Current, NULL, &Difficulty.CurrRect);

    SDL_SetRenderDrawColor(GlobalRenderer, 0, 0, 0, 0);

    Save.draw();
}

void Settings::quit()
{

}

StateType Settings::nextState()
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
