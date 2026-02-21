#include "engine/Components/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::shared_ptr<GameObject>& gameObject, SDL_Renderer* renderer, const std::string& filepath, SDL_FRect* srcrect, SDL_FRect* dstrect) : Component("SpriteRenderer", gameObject), m_srcrect(srcrect), m_dstrect(dstrect), m_texture(CreateTextureFromPNG(filepath))
{

}
SpriteRenderer::~SpriteRenderer() {};

void SpriteRenderer::OnStart()
{

};

void SpriteRenderer::OnIterate() {};
void SpriteRenderer::OnDraw(SDL_Renderer* renderer) 
{
	SDL_RenderTexture(renderer, m_texture.GetTexture(), m_srcrect.get(), m_dstrect.get());
	std::cout 
		<< m_dstrect->x << ' ' << m_dstrect->y << "\n---------------------------------";
};
void SpriteRenderer::OnEvent(SDL_Event* event) {};
