#include "custom_scene.h"

static SDL_FRect playerSprRectArr[10];

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene)
{
	gameScene->AddGameObject();
	auto gb = gameScene->GetGameObject();
	static_cast<Transform*>(gb->GetTransform())->SetPosition({500, 600, -2});

	for(int i = 0; i < 10; ++i)
	{
		playerSprRectArr[i].x = i*32;
		playerSprRectArr[i].y = 0;
		playerSprRectArr[i].w = 32;
		playerSprRectArr[i].h = 48;
	}

	gb->AddComponent(new SpriteRenderer(gb, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRectArr[0], playerSprRectArr[0]));
}	
