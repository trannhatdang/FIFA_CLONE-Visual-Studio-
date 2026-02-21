#include "engine/Components/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::shared_ptr<GameObject>& gameObject, SDL_Renderer* renderer, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect) : Component("SpriteRenderer", gameObject), m_srcrect(srcrect), m_dstrect(dstrect)
{
	SDL_Surface* surface = SDL_LoadPNG(filepath.c_str());
	if(!surface)
	{
		SDL_Log("Could not create surface for texture creation: %s", SDL_GetError());
	}

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!m_texture)
	{
		SDL_Log("Could not create texture: %s", SDL_GetError());
	}
	SDL_DestroySurface(surface);
}

SpriteRenderer::~SpriteRenderer() 
{
	SDL_DestroyTexture(m_texture);
};

void SpriteRenderer::OnStart()
{

};

void SpriteRenderer::OnIterate() {};
void SpriteRenderer::OnDraw(SDL_Renderer* renderer) 
{
	SDL_RenderTexture(renderer, m_texture, &m_srcrect, &m_dstrect);
};
void SpriteRenderer::OnEvent(SDL_Event* event) {};
