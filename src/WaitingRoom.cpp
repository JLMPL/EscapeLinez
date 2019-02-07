#include "WaitingRoom.hpp"
#include "State.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Settings.hpp"
#include <iostream>
#include "ConfigFile.hpp"
#include <SFML/Network.hpp>
#include <vector>
#include <time.h>
#include "Login.hpp"
#include "jsonP.hpp"
#include "Network.hpp"

using json = nlohmann::json;


void WaitingRoom :: init(SDL_Window* win, SDL_Renderer* rend)
{    
	Renderer = rend;

	Font = TTF_OpenFont("husa.ttf", 36);
	FontColor = {255, 255, 255};
        
        MessageTime[2] = '\0';


    //----------------------------------left-------------------------------------------

	FontSurfaceTime = TTF_RenderText_Solid(Font, "Stopwatch: ", FontColor);
	FontSurfacePlayers = TTF_RenderText_Solid(Font, "Players: ", FontColor);
	FontSurfaceHour = TTF_RenderText_Solid(Font, "Time: ", FontColor);

    FontTextureTime = SDL_CreateTextureFromSurface(Renderer, FontSurfaceTime);
    FontTexturePlayers = SDL_CreateTextureFromSurface(Renderer, FontSurfacePlayers);
    FontTextureHour = SDL_CreateTextureFromSurface(Renderer, FontSurfaceHour);

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

    sf::IpAddress ip(127, 0, 0, 1);  //ip serwera
	
	new (&MySocketTime) MySocket(ip, 8001);
	new (&MySocketPlayers) MySocket(ip, 8002);
	new (&MySocketToBattle) MySocket(ip, 8003);

}

void WaitingRoom :: update(float deltaTime)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    std:size_t received;

    FontSurfaceHourData = TTF_RenderText_Solid(Font, dt, FontColor);
    RectHourData.w = FontSurfaceHourData->w;
    RectHourData.h = FontSurfaceHourData->h;
    FontTextureHourData = SDL_CreateTextureFromSurface(Renderer, FontSurfaceHourData);

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
        FontTextureTimeData = SDL_CreateTextureFromSurface(Renderer, FontSurfaceTimeData);

        

        FontSurfacePlayersData = TTF_RenderText_Solid(Font, StringPlayers.c_str(), FontColor);
        RectPlayersData.w = FontSurfacePlayersData->w;
        RectPlayersData.h = FontSurfacePlayersData->h;
        FontTexturePlayersData = SDL_CreateTextureFromSurface(Renderer, FontSurfacePlayersData);




    SDL_RenderCopy(Renderer, FontTextureTime, NULL, &RectTime);
    SDL_RenderCopy(Renderer, FontTexturePlayers, NULL, &RectPlayers);
    SDL_RenderCopy(Renderer, FontTextureHour, NULL, &RectHour);

    SDL_RenderCopy(Renderer, FontTextureTimeData, NULL, &RectTimeData);
    SDL_RenderCopy(Renderer, FontTexturePlayersData, NULL, &RectPlayersData);
    SDL_RenderCopy(Renderer, FontTextureHourData, NULL, &RectHourData);
    
    SDL_FreeSurface(FontSurfaceTimeData);
    SDL_FreeSurface(FontSurfacePlayersData);
    SDL_FreeSurface(FontSurfaceHourData);

    if (IntToBattle == 1)
        changeState = StateType::Multiplayer;
}

void WaitingRoom::AfterRendering()
{

    SDL_DestroyTexture(FontTextureTimeData);
    SDL_DestroyTexture(FontTexturePlayersData);
    SDL_DestroyTexture(FontTextureHourData);

}

void WaitingRoom :: processEvent(const SDL_Event& event)
{

}

void WaitingRoom :: quit()
{
    SDL_DestroyTexture(FontTextureTime);
    SDL_DestroyTexture(FontTexturePlayers);
    SDL_DestroyTexture(FontTextureHour);
}

StateType WaitingRoom :: nextState()
{
    return changeState;
}