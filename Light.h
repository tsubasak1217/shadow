#pragma once
#include "Map.h"

class Light {

	Vec2 emitPos_;
	Vec2 aimPos_;
	Vec2 leftVec_;
	Vec2 rightVec_;
	std::vector<Vec2>lightHitSpot_;
	float rangeTheta_;
	Vec2 firstEmitPos_[Global::stageMAX];


public:

	Light(Map map) {

		//ステージごとのライトの初期座標
		firstEmitPos_[0] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[1] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[2] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[3] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[4] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[5] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[6] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[7] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };

		emitPos_ = {
		Global::windowSize_.x * 0.5f,
		Global::windowSize_.y - map.GetSize().y * 0.2f
		};
		aimPos_ = { -100.0f,-100.0f };
		lightHitSpot_.clear();
		rangeTheta_ = 0.0f;
		leftVec_ = { 0.0f,0.0f };
		rightVec_ = { 0.0f,0.0f };
	}

	void Init(int stageNum,Map map);

	void Update(char* keys,const ChangeScene& cs,Map map, float rangeTheta,bool isPause);

	void Draw(const Resources& rs, Map map, ChangeScene CS);

	//アクセッサ
	Vec2 GetEmitPos() { return emitPos_; }

};

