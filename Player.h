#pragma once
#include "Map.h"
class Player{

	Vec2 pos_;
	Vec2 size_;
	Vec2 direction_;
	Vec2 velocity_;
	float speed_;

public:

	Player(Map map) {
		pos_ = {
			map.firstPlayerPos_.x,
			map.firstPlayerPos_.y,
		};

		size_ = { 24.0f,24.0f };
		direction_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		speed_ = 4.0f;


	}

	void Init(int sceneNum);

	void Update(char* keys);

	void Draw(Resources rs,Map map);

	//アクセッサ
	Vec2 GetPos() { return pos_; }
};

