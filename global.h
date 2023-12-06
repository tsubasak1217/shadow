#pragma once
#include "Scene.h"

class Global{
public:
	static Vector2<int>windowSize_;
	static bool isMoveShadow_;
	static const int stageMAX = 8;
	static int timeCount_;
	static int controlMode_;
	static int character_;

	Global();
	~Global();

	void Update(const char* keys);
};
