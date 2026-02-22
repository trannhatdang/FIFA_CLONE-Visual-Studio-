#include "Config.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const std::string PLAYER_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\megaman-left.png";

int GetWindowWidth(){
	return WINDOW_WIDTH;
}

int GetWindowHeight(){
	return WINDOW_HEIGHT;
}

std::string GetPlayerSpriteSheet()
{
	return PLAYER_FILEPATH;
}
