#pragma once
#include "MyFunc.h"

class Player;
class PlayerShadow;
class Light;
class Map;

class SaveData {
	
public:

	// 保存されたマップ
	static std::vector<std::vector<int>>savedMap_;
	static  std::vector<std::vector<int>>savedShadowMap_;

	// その他いろいろ保存
	static Vec2 savedPlayerPos_;
	static Vec2 savedPlayerShadowPos_;
	static Vec2 savedLightPos_;

	// 
	static Vec2 playerPos_;
	static Vec2 playerShadowPos_;
	static Vec2 lightPos_;
	static std::vector<std::vector<int>>map_;
	static std::vector<std::vector<int>>shadowMap_;

	void Init();
};

