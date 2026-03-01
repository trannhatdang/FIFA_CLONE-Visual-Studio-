#include "CustomScene/GameScene/GameScene.h"

static SDL_FRect playerSprRect = {0, 0, 80, 80};
static SDL_FRect ballSprRect = {0, 0, 48, 48};

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene)
{
	//tilemap
	gameScene->AddGameObject("Tilemap", "Tilemap");
	auto tilemap_gb = gameScene->GetGameObject(0);

	std::vector<std::vector<int>> map = 
		{{6, 2, 2, 2, 2, 2, 7},
		{10, 0, 0, 0, 0, 0, 11},
		{4, 0, 0, 1, 0, 0, 5},
		{10, 0, 0, 0, 0, 0, 11},
		{9, 3, 3, 3, 3, 3, 8}};

	tilemap_gb->AddComponent(new Tilemap(tilemap_gb, gameScene->GetRenderer(), GetGrassSpriteSheet(), map, 160, 160));

	//walls
	auto twall = gameScene->AddGameObject("TWall", "Wall");
	static_cast<Transform*>(twall->GetTransform())->SetPosition({0, -100, -2});
	twall->AddComponent(new Rigidbody(twall, true, 1, 100000));
	twall->AddComponent(new BoxCollider(twall, {1120, 110}));

	auto bwall = gameScene->AddGameObject("BWall", "Wall");
	static_cast<Transform*>(bwall->GetTransform())->SetPosition({0, 790, -2});
	bwall->AddComponent(new BoxCollider(bwall, {1120, 110}));

	auto lwall = gameScene->AddGameObject("LWall", "Wall");
	static_cast<Transform*>(lwall->GetTransform())->SetPosition({-100, 10, -2});
	lwall->AddComponent(new BoxCollider(lwall, {110, 780}));

	auto rwall = gameScene->AddGameObject("RWall", "Wall");
	static_cast<Transform*>(rwall->GetTransform())->SetPosition({1110, 10, -2});
	rwall->AddComponent(new BoxCollider(rwall, {110, 780}));

	//players
	auto striker1 = gameScene->AddGameObject("Striker1", "Player");
	static_cast<Transform*>(striker1->GetTransform())->SetPosition({500 - 20, 400 - 20, -2});
	striker1->AddComponent(new SpriteRenderer(striker1, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	striker1->AddComponent(new Rigidbody(striker1, true, 100, 60));
	striker1->AddComponent(new BoxCollider(striker1, {40, 40}));
	striker1->AddComponent(new Movement(striker1, 50.0f, true, true));

	auto midfielder10 = gameScene->AddGameObject("Midfielder10", "Player");
	static_cast<Transform*>(midfielder10->GetTransform())->SetPosition({350 - 20, 400 - 150 - 20, -2});
	midfielder10->AddComponent(new SpriteRenderer(midfielder10, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	midfielder10->AddComponent(new Rigidbody(midfielder10, true, 100, 60));
	midfielder10->AddComponent(new BoxCollider(midfielder10, {40, 40}));
	midfielder10->AddComponent(new Movement(midfielder10, 50.0f, false, true));

	auto midfielder11 = gameScene->AddGameObject("Midfielder11", "Player");
	static_cast<Transform*>(midfielder11->GetTransform())->SetPosition({350 - 20, 400 + 150 - 20, -2});
	midfielder11->AddComponent(new SpriteRenderer(midfielder11, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	midfielder11->AddComponent(new Rigidbody(midfielder11, true, 100, 60));
	midfielder11->AddComponent(new BoxCollider(midfielder11, {40, 40}));
	midfielder11->AddComponent(new Movement(midfielder11, 50.0f, false, true));

	auto defender1 = gameScene->AddGameObject("Defender1", "Player");
	static_cast<Transform*>(defender1->GetTransform())->SetPosition({200 - 20, 400 - 20, -2});
	defender1->AddComponent(new SpriteRenderer(defender1, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	defender1->AddComponent(new Rigidbody(defender1, true, 100, 60));
	defender1->AddComponent(new BoxCollider(defender1, {40, 40}));
	defender1->AddComponent(new Movement(defender1, 50.0f, false, true));

	auto goalkeeper1 = gameScene->AddGameObject("Goalkeeper1", "Player");
	static_cast<Transform*>(goalkeeper1->GetTransform())->SetPosition({100 - 20, 400 - 20, -2});
	goalkeeper1->AddComponent(new SpriteRenderer(goalkeeper1, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	goalkeeper1->AddComponent(new Rigidbody(goalkeeper1, true, 100, 60));
	goalkeeper1->AddComponent(new BoxCollider(goalkeeper1, {40, 40}));
	goalkeeper1->AddComponent(new Movement(goalkeeper1, 50.0f, false, true));

	auto striker2 = gameScene->AddGameObject("Striker2", "Player");
	static_cast<Transform*>(striker2->GetTransform())->SetPosition({620 - 20, 400 - 20, -2});
	striker2->AddComponent(new SpriteRenderer(striker2, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	striker2->AddComponent(new Rigidbody(striker2, true, 100, 60));
	striker2->AddComponent(new BoxCollider(striker2, {40, 40}));
	striker2->AddComponent(new Movement(striker2, 50.0f, true, true));

	auto midfielder20 = gameScene->AddGameObject("Midfielder20", "Player");
	static_cast<Transform*>(midfielder20->GetTransform())->SetPosition({770 - 20, 400 - 150 - 20, -2});
	midfielder20->AddComponent(new SpriteRenderer(midfielder20, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	midfielder20->AddComponent(new Rigidbody(midfielder20, true, 100, 60));
	midfielder20->AddComponent(new BoxCollider(midfielder20, {40, 40}));
	midfielder20->AddComponent(new Movement(midfielder20, 50.0f, false, true));

	auto midfielder21 = gameScene->AddGameObject("Midfielder21", "Player");
	static_cast<Transform*>(midfielder21->GetTransform())->SetPosition({770 - 20, 400 + 150 - 20, -2});
	midfielder21->AddComponent(new SpriteRenderer(midfielder21, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	midfielder21->AddComponent(new Rigidbody(midfielder21, true, 100, 60));
	midfielder21->AddComponent(new BoxCollider(midfielder21, {40, 40}));
	midfielder21->AddComponent(new Movement(midfielder21, 50.0f, false, true));

	auto defender2 = gameScene->AddGameObject("Defender2", "Player");
	static_cast<Transform*>(defender2->GetTransform())->SetPosition({920 - 20, 400 - 20, -2});
	defender2->AddComponent(new SpriteRenderer(defender2, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	defender2->AddComponent(new Rigidbody(defender2, true, 100, 60));
	defender2->AddComponent(new BoxCollider(defender2, {40, 40}));
	defender2->AddComponent(new Movement(defender2, 50.0f, false, true));

	auto goalkeeper2 = gameScene->AddGameObject("Goalkeeper2", "Player");
	static_cast<Transform*>(goalkeeper2->GetTransform())->SetPosition({1020 - 20, 400 - 20, -2});
	goalkeeper2->AddComponent(new SpriteRenderer(goalkeeper2, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	goalkeeper2->AddComponent(new Rigidbody(goalkeeper2, true, 100, 60));
	goalkeeper2->AddComponent(new BoxCollider(goalkeeper2, {40, 40}));
	goalkeeper2->AddComponent(new Movement(goalkeeper2, 50.0f, false, true));

	auto ball = gameScene->AddGameObject("Ball", "Ball");
	static_cast<Transform*>(ball->GetTransform())->SetPosition({560 - 24, 400 - 24, -2});
	ball->AddComponent(new SpriteRenderer(ball, gameScene->GetRenderer(), GetBallSprite(), ballSprRect, ballSprRect));
	ball->AddComponent(new Rigidbody(ball, true, 1));
	ball->AddComponent(new BoxCollider(ball, {48, 48}));

	//gameScene->DEBUG_PrintGameObjAdd();

	//static_cast<Rigidbody*>(gb->GetComponent("Rigidbody"))->AddForce({10, 0, 0});
}
