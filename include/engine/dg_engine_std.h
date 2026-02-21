#ifndef DG_ENGINE_STD_
#define DG_ENGINE_STD_

#include <vector>
#include <memory>
#include <iostream>
#include <SDL3/SDL.h>

typedef struct Vector2
{
	int x;
	int y;
} Vector2;

typedef struct Vector3
{
	int x;
	int y;
	int z;
} Vector3;

const int ON_COLLISION_ENTER_EVENT = SDL_RegisterEvents(1);

#endif
