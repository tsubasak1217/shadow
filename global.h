#pragma once
#include "Scene.h"

class Global{
public:
	static Vector2<int>windowSize_;
	static bool isMoveShadow_;
	static const int stageMAX = 16;
	static int timeCount_;
	static int controlMode_;
	static int character_;

	static Vector2<int> leftStickValue_;
	static Vector2<int> preLeftStickValue_;
	static bool isTriggerLeftStick_UP_;
	static bool isTriggerLeftStick_DOWN_;
	static bool isTriggerLeftStick_RIGHT_;
	static bool isTriggerLeftStick_LEFT_;

	static bool preIsB_;
	static bool isB_;
	static bool isReleaseB_;

	static int aliveTimer_;

	Global();
	~Global();

	void Update(const char* keys, const char* preKeys);
	void Draw(const Resources& rs);
};
