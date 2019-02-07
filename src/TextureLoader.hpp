#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP
#include <string>

extern struct SDL_Texture* loadTexture(struct SDL_Renderer* renderer, const std::string& path);

#endif