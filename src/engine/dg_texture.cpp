#include "engine/DG_Texture.h"

DG_Texture::DG_Texture(SDL_Texture* texture) : m_texture(texture)
{
	
}

DG_Texture::~DG_Texture()
{
	SDL_DestroyTexture(m_texture);
}

SDL_Texture* DG_Texture::GetTexture() const
{
	return m_texture;
}

SDL_Texture* CreateTextureFromPNG(SDL_Renderer* renderer, const std::string& filepath)
{
	SDL_Surface* surface = SDL_LoadPNG(filepath.c_str());
	if(!surface)
	{
		SDL_Log("Could not create surface for texture creation :%s", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
	return texture;
}
