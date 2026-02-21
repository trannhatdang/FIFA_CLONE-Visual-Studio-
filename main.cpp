#include <SDL3/SDL.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include "engine/scene.h"
#include "config.h"
#include "custom_scene.h"

static SDL_Renderer* renderer = nullptr;
static SDL_Window* window = nullptr;
static std::shared_ptr<Scene> scenes[10];
static std::shared_ptr<Scene> currScene;
static std::chrono::milliseconds frametime;
static std::chrono::time_point last_iterate_point = std::chrono::system_clock::now();
SDL_Texture* texture;
int texture_w, texture_h;
static void ChangeScene(int index)
{
	currScene = scenes[index];
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv)
{
	char windowCaption[5] = "game";

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_LoadPNG("lmao");
	
	if(!SDL_CreateWindowAndRenderer(windowCaption, GetWindowWidth(), GetWindowHeight(), SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_SetRenderLogicalPresentation(renderer, GetWindowWidth(), GetWindowHeight(), SDL_LOGICAL_PRESENTATION_LETTERBOX);

	scenes[0] = std::make_shared<Scene>("IntroScene");
	scenes[1] = std::make_shared<Scene>("MenuScene");
	scenes[2] = std::make_shared<Scene>("GameScene");
	scenes[3] = std::make_shared<Scene>("OptionsScene");

	GenerateGameScene(scenes[2]);

	ChangeScene(2); //Straight into game scene
	
	SDL_Surface* surface = SDL_LoadPNG(GetPlayerSpriteSheet().c_str());
	if(!surface)
	{
		SDL_Log("Could not create surface for texture creation: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	texture_w = surface->w;
	texture_h = surface->h;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	if(std::chrono::system_clock::now() - last_iterate_point > frametime)
	{
		currScene->OnFixedIterate();
		last_iterate_point = std::chrono::system_clock::now();
	}
	currScene->OnIterate();
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_FRect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 32;
	srcrect.h = 48;

	SDL_FRect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 32;
	dstrect.h = 48;

	SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);
	currScene->OnDraw(renderer);
	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;
	}
	currScene->OnEvent(event);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	SDL_DestroyTexture(texture);

}
