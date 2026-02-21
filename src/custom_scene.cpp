#include "custom_scene.h"

void GenerateGameScene(const std::shared_ptr<Scene>& gameScene)
{
	gameScene->AddGameObject();
	auto gb = gameScene->GetGameObject();

	SDL_FRect* srcrect = new SDL_FRect;
	srcrect->x = 0;
	srcrect->y = 0;
	srcrect->w = 32;
	srcrect->h = 48;

	SDL_FRect* dstrect = new SDL_FRect;
	dstrect->x = 0;
	dstrect->y = 0;
	dstrect->w = 32;
	dstrect->h = 48;

	gb->AddComponent(std::make_shared<SpriteRenderer>(gb, gameScene->GetRenderer(), GetPlayerSpriteSheet(), srcrect, dstrect));
}	
