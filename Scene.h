#pragma once
#include "Resources.h"

enum SCENENAME {
	TITLE,
	SELECT,
	GAME,
	CLEAR
};

class Scene{
	int sceneNum_ = GAME;
	
public:
	int GetSceneNum() { return sceneNum_; }
};

