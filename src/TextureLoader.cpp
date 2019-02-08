#include "TextureLoader.hpp"
#include "Renderer.hpp"
#include <SDL2/SDL_image.h>

SDL_Texture* loadTexture(const std::string& path)
{
	SDL_Surface* surf = IMG_Load(path.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(GlobalRenderer, surf);
	SDL_FreeSurface(surf);

	return tex;
}
