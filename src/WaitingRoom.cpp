#include "ConfigFile.hpp"
#include "Login.hpp"
#include "Network.hpp"
#include "Settings.hpp"
#include "State.hpp"
#include "WaitingRoom.hpp"
#include "TextureLoader.hpp"
#include "Renderer.hpp"
#include "json.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SFML/Network.hpp>
#include <iostream>
#include <time.h>
#include <vector>

using json = nlohmann::json;

void WaitingRoom::init(SDL_Window* win)
{
	Font = TTF_OpenFont("data/Fonts/husa.ttf", 48);
	FontColor = {255, 255, 255};

	m_background = loadTexture("data/Images/WaitingRoom/tlo.jpg");

    MessageTime[2] = '\0';

    //----------------------------------left-------------------------------------------

	FontSurfaceTime = TTF_RenderText_Solid(Font, "Stopwatch: ", FontColor);
	FontSurfacePlayers = TTF_RenderText_Solid(Font, "Players: ", FontColor);
	FontSurfaceHour = TTF_RenderText_Solid(Font, "Time: ", FontColor);

    FontTextureTime = SDL_CreateTextureFromSurface(GlobalRenderer, FontSurfaceTime);
    FontTexturePlayers = SDL_CreateTextureFromSurface(GlobalRenderer, FontSurfacePlayers);
    FontTextureHour = SDL_CreateTextureFromSurface(GlobalRenderer, FontSurfaceHour);

    RectTime.x = w / 2 - (FontSurfaceTime->w + 16);
    RectTime.y = h * 0.3 - 70;
    RectTime.w = FontSurfaceTime->w;
    RectTime.h = FontSurfaceTime->h;

    RectPlayers.x = w / 2 - (FontSurfacePlayers->w + 16);
    RectPlayers.y = h * 0.4 - 70;
    RectPlayers.w = FontSurfacePlayers->w;
    RectPlayers.h = FontSurfacePlayers->h;

    RectHour.x = w / 2 - (FontSurfaceHour->w + 16);
    RectHour.y = h * 0.5 - 70;
    RectHour.w = FontSurfaceHour->w;
    RectHour.h = FontSurfaceHour->h;

    SDL_FreeSurface(FontSurfaceTime);
    SDL_FreeSurface(FontSurfacePlayers);
    SDL_FreeSurface(FontSurfaceHour);

    //--------------------------Rigth----------------------------------------

    RectTimeData.x = w / 2;
    RectTimeData.y = h * 0.3 - 70;

    RectPlayersData.x = w / 2;
    RectPlayersData.y = h * 0.4 - 70;

    RectHourData.x = w / 2;
    RectHourData.y = h * 0.5 - 70;

    //-------------------net---------------

	new (&MySocketTime) MySocket(servers[0].ip, 8001);
	new (&MySocketPlayers) MySocket(servers[0].ip, 8002);
	new (&MySocketToBattle) MySocket(servers[0].ip, 8003);
}

void WaitingRoom::processEvent(const SDL_Event& event)
{
}

void WaitingRoom::update(float deltaTime)
{
    time_t now = time(0);
    char* dt = ctime(&now);

    FontSurfaceHourData = TTF_RenderText_Solid(Font, dt, FontColor);
    RectHourData.w = FontSurfaceHourData->w;
    RectHourData.h = FontSurfaceHourData->h;
    FontTextureHourData = SDL_CreateTextureFromSurface(GlobalRenderer, FontSurfaceHourData);

    MessagePlayers = "0";

	MessageTime = MySocketTime.get();
	MessagePlayers = MySocketPlayers.get();
	ToBattle = MySocketToBattle.get();

	json JsonTime  = json::parse(MessageTime);
	json JsonPlayers = json::parse(MessagePlayers);
	json JsonToBattle = json::parse(ToBattle);

    const    int IntTime = JsonTime["body"].get<int>();
    const    int IntPlayers = JsonPlayers["body"].get<int>();
    const    int IntToBattle = JsonToBattle["body"].get<int>();

    std::string StringTime = std::to_string(IntTime);
    std::string StringPlayers = std::to_string(IntPlayers);

    FontSurfaceTimeData = TTF_RenderText_Solid(Font, StringTime.c_str(), FontColor);
    RectTimeData.w = FontSurfaceTimeData->w;
    RectTimeData.h = FontSurfaceTimeData->h;
    FontTextureTimeData = SDL_CreateTextureFromSurface(GlobalRenderer, FontSurfaceTimeData);

    FontSurfacePlayersData = TTF_RenderText_Solid(Font, StringPlayers.c_str(), FontColor);
    RectPlayersData.w = FontSurfacePlayersData->w;
    RectPlayersData.h = FontSurfacePlayersData->h;
    FontTexturePlayersData = SDL_CreateTextureFromSurface(GlobalRenderer, FontSurfacePlayersData);

    SDL_FreeSurface(FontSurfaceTimeData);
    SDL_FreeSurface(FontSurfacePlayersData);
    SDL_FreeSurface(FontSurfaceHourData);

    if (IntToBattle == 1)
        changeState = StateType::Multiplayer;
}

void WaitingRoom::draw()
{
	SDL_RenderCopy(GlobalRenderer, m_background, NULL, NULL);

    SDL_RenderCopy(GlobalRenderer, FontTextureTime, NULL, &RectTime);
    SDL_RenderCopy(GlobalRenderer, FontTexturePlayers, NULL, &RectPlayers);
    SDL_RenderCopy(GlobalRenderer, FontTextureHour, NULL, &RectHour);

    SDL_RenderCopy(GlobalRenderer, FontTextureTimeData, NULL, &RectTimeData);
    SDL_RenderCopy(GlobalRenderer, FontTexturePlayersData, NULL, &RectPlayersData);
    SDL_RenderCopy(GlobalRenderer, FontTextureHourData, NULL, &RectHourData);

    SDL_DestroyTexture(FontTextureTimeData);
    SDL_DestroyTexture(FontTexturePlayersData);
    SDL_DestroyTexture(FontTextureHourData);
}

void WaitingRoom::quit()
{
    SDL_DestroyTexture(FontTextureTime);
    SDL_DestroyTexture(FontTexturePlayers);
    SDL_DestroyTexture(FontTextureHour);
	SDL_DestroyTexture(m_background);
}

StateType WaitingRoom::nextState()
{
    return changeState;
}
