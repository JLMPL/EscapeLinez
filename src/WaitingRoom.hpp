#ifndef WAITINGROOM_HPP
#define WAITINGROOM_HPP
#include "ConfigFile.hpp"
#include "Settings.hpp"
#include "State.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <time.h>

class WaitingRoom : public State
{
public:
    void init(SDL_Window* win) override final;
    void quit() override final;

    void processEvent(const SDL_Event& event) override final;
    void update(float deltaTime) override final;
    void draw() override final;

    StateType nextState() override final;
    StateType getType() const override final
    {
        return StateType::WaitingRoom;
    }

private:
    StateType changeState = StateType::None;

    int w = GlobalConfigFile.getWidth(), h = GlobalConfigFile.getHeight();

    TTF_Font*       Font;
    SDL_Color       FontColor;

//-----------------------left-----------------------------

    SDL_Surface*    FontSurfaceTime;
    SDL_Texture*    FontTextureTime;

    SDL_Surface*    FontSurfacePlayers;
    SDL_Texture*    FontTexturePlayers;

    SDL_Surface*    FontSurfaceHour;
    SDL_Texture*    FontTextureHour;

    SDL_Rect        RectTime;
    SDL_Rect        RectPlayers;
    SDL_Rect        RectHour;

//--------------------------Right---------------------------

    SDL_Surface*    FontSurfaceTimeData;
    SDL_Texture*    FontTextureTimeData;

    SDL_Surface*    FontSurfacePlayersData;
    SDL_Texture*    FontTexturePlayersData;

    SDL_Surface*    FontSurfaceHourData;
    SDL_Texture*    FontTextureHourData;

    SDL_Rect        RectTimeData;
    SDL_Rect        RectPlayersData;
    SDL_Rect        RectHourData;

    //-----------------net---------------------------

    std::string MessageTime;
    std::string MessageTimeCopy;
    std::string MessagePlayers;
    std::string ToBattle = "0";
};

#endif /* WAITINGROOM_HPP */

