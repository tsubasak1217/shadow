#pragma once
#include "Map.h"
class Player{

	Vec2 pos_;
	Vec2 size_;
	Vec2 direction_;
	Vec2 velocity_;
	Vector2<int>address_[4];
	Vector2<int>preAddress_[4];
	float speed_;

public:

	Player(Map map) {
		pos_ = {
			map.firstPlayerPos_.x + map.GetPuzzleLeftTop().x,
			map.firstPlayerPos_.y + map.GetPuzzleLeftTop().y,
		};

		size_ = { 24.0f,24.0f };
		direction_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		speed_ = 4.0f;
		for (int i = 0; i < 4; i++) {
			address_[i] = {0,0};
			preAddress_[i] = address_[i];
		}
	}

	void Init(int sceneNum);

	void Update(char* keys,Map map);

	void Draw(const Resources& rs,Map map);

	//アクセッサ
	Vec2 GetPos() { return pos_; }
};

