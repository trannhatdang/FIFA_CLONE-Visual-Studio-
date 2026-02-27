#include "engine/Components/SpriteRenderer.h"
#include "engine/GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject, SDL_Renderer* renderer, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect) : Component("SpriteRenderer", gameObject), m_srcrect(srcrect), m_dstrect(dstrect), filepath(filepath), m_renderer(renderer)
{
	m_texture = CreateTextureFromPNG(renderer, filepath);
}

SpriteRenderer::~SpriteRenderer() 
{
	SDL_DestroyTexture(m_texture);
}

void SpriteRenderer::OnStart()
{

}

void SpriteRenderer::OnIterate() 
{

}

void SpriteRenderer::OnDraw(SDL_Renderer* renderer)
{
	//i'm not managing that!
	Vector3 pos = static_cast<Transform*>(this->gameObject->GetTransform())->GetPosition();
	SDL_Rect viewport;
	//god what would happen if we go 3d?
	Vector3 cameraPos = GetCameraPos();

	if(pos.x > 10e3 || pos.y > 10e3 || pos.z > 10e3)
	{
		return;
	}

	viewport.x = std::min(std::max(pos.x - cameraPos.x, -1000), 1000);
	viewport.y = std::min(std::max(pos.y - cameraPos.y, -1000), 1000);
	viewport.w = m_dstrect.w;
	viewport.h = m_dstrect.h;

	DrawTexture(renderer, m_texture, viewport, m_srcrect, m_dstrect);
}

void SpriteRenderer::OnEvent(SDL_Event* event) 
{

}

std::unique_ptr<Component> SpriteRenderer::copy()
{
	return std::make_unique<SpriteRenderer>(gameObject, m_renderer, filepath, m_srcrect, m_dstrect);
}
