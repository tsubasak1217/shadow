#pragma once
#include "Player.h"

class Light{

	Vec2 emitPos_;
	Vec2 aimPos_;
	Vec2 leftVec_;
	Vec2 rightVec_;
	std::vector<Vec2>lightHitSpot_;
	float rangeTheta_;

public:

	Light(Global global,Map map) {
		emitPos_ = {
		global.windowSize_.x * 0.5f,
		global.windowSize_.y - map.GetSize().y * 0.2f,
		};
		aimPos_ = { -100.0f,-100.0f };
		lightHitSpot_.clear();
		rangeTheta_ = 0.0f;
		leftVec_ = {0.0f,0.0f};
		rightVec_ = {0.0f,0.0f};
	}

	void Update(char* keys,Map map, float rangeTheta, Global global);

	void Draw(Map map);

//アクセッサ
	Vec2 GetEmitPos() { return emitPos_; }

};

