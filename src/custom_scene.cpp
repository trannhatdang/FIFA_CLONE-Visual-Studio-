#include "custom_scene.h"

void GenerateGameScene(const std::shared_ptr<Scene>& gameScene)
{
	gameScene->AddGameObject();
	auto gb = gameScene->GetGameObject();
	std::shared_ptr<SDL_FRect> dstrect = std::make_shared<SDL_FRect>();
	dstrect->x = 50;
	dstrect->y = 50;
	dstrect->w = 800;
	dstrect->h = 600;

	gb->AddComponent(std::make_shared<SpriteRenderer>(gb, gameScene->GetRenderer(), GetPlayerSpriteSheet(), nullptr, dstrect));
}
