#include "ConfigFile.hpp"
#include <fstream>
#include <stdio.h>
#include <SDL2/SDL.h>

ConfigFile GlobalConfigFile;

void ConfigFile::load()
{
	std::ifstream file("config.set");
	
	if (!file.good())
	{
		printf("Error: config set is not OK!\n");
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.substr(0,5) == "Width")
		{
			sscanf(line.c_str(), "Width = %d", &Width);
			printf("width %d\n", Width);
		}
		else if (line.substr(0,6) == "Height")
		{
			sscanf(line.c_str(), "Height = %d", &Height);
			printf("height %d\n", Height);
		}
		else if (line.substr(0,10) == "Fullscreen")
		{
			sscanf(line.c_str(), "Fullscreen = %d", &Fullscreen);
			printf("Fullscreen %d\n", Fullscreen);
		}
		else if (line.substr(0,5) == "Music")
		{
			sscanf(line.c_str(), "Music = %d", &Music);
			printf("Music %d\n", Music);
		}
		else if (line.substr(0,10) == "Difficulty")
		{
			sscanf(line.c_str(), "Difficulty = %d", &Difficulty);
			printf("Difficulty %d\n", Difficulty);
		}
	}

	NumMonitors = SDL_GetNumVideoDisplays();
}

void ConfigFile::save()
{
	std::ofstream FileToSave("config.set");

	FileToSave  <<"\n" 
			<< "Width = "<< Width <<"\n"
			<< "Height = "<< Height <<"\n"
			<< "Fullscreen = "<< Fullscreen <<"\n"
			<< "Music = "<< Music <<"\n"
			<< "Difficulty = "<< Difficulty <<"\n";


	FileToSave.close();

}

void ConfigFile::setWidth(int val)
{
	Width = val;
}

void ConfigFile::setHeight(int val)
{
	Height = val;
}

void ConfigFile::setFullscreen(bool val)
{
	if (val && NumMonitors > 1)
		printf("Can't do Fullscreen with multiple monitors!\n");
	else
		Fullscreen = val;
}

void ConfigFile::setMusic(bool val)
{
	Music = val;
}

void ConfigFile::setDifficulty(int val)
{
	Difficulty = val;
}

int ConfigFile::getWidth() const
{
	return Width;
}

int ConfigFile::getHeight() const
{
	return Height;
}

bool ConfigFile::isFullscreen() const
{
	return Fullscreen;
}

bool ConfigFile::isMusic() const
{
	return Music;
}

int ConfigFile::getDifficulty() const
{
	return Difficulty;
}

