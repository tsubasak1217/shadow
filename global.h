#pragma once
#include "Resources.h"

class Global{
public:
	static Vector2<int>windowSize_;
	static bool isMoveShadow_;
	static const int stageMAX = 8;
	static int timeCount_;

	Global();
	~Global();

	void Update();
};
