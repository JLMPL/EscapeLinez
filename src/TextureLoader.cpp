#include "TextureLoader.hpp"
#include <SDL2/SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path)
{
	SDL_Surface* surf = IMG_Load(path.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);

	return tex;
}
