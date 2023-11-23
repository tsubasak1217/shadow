#pragma once
#include "Shadow.h"

class PlayerShadow {

	Vec2 pos_;
	Vec2 prePos_;
	Vec2 prePosCopy_;
	Vec2 size_;
	Vec2 direction_;
	Vec2 velocity_;
	Vector2<int>address_[4];
	Vector2<int>preAddress_[4];
	float speed_;

	bool isJump_;
	bool  isDrop_;
	float jumpSpeed_;
	float dropSpeed_;
	float gravity_;

	//当たり判定
	int hitCount_;
	std::vector<int>hitSurface_;
	std::vector<int>preHitSurface_;
	std::vector<int>hitSurface2_;
	std::vector<int>preHitSurface2_;
	int blockCount;
	bool isHitMapChip_;
	bool isHitRect_;
	bool isInsideLightLT_;
	bool isInsideLightRT_;
	bool isInsideLightLB_;
	bool isInsideLightRB_;
	bool preIsInsideLightLB_;
	bool preIsInsideLightRB_;
	bool preIsInsideLightLT_;
	bool preIsInsideLightRT_;

	//クリア
	int starGetCount_;

public:

	PlayerShadow(Screen screen, Shadow shadow) {
		pos_ = {
			shadow.firstPlayerPos_.x + screen.GetScreenLeftTop().x,
			shadow.firstPlayerPos_.y + screen.GetScreenLeftTop().y,
		};
		prePos_ = pos_;
		prePosCopy_ = prePos_;

		size_ = { 32.0f,32.0f };
		direction_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		speed_ = 4.0f;
		for (int i = 0; i < 4; i++) {
			address_[i] = { 0,0 };
			preAddress_[i] = address_[i];
		}

		pos_.y += (shadow.GetSize().y * 0.5f);
		pos_.y += -(size_.y * 0.5f);

		isJump_ = false;
		isDrop_ = false;
		jumpSpeed_ = 0.0f;
		dropSpeed_ = 0.0f;
		gravity_ = 0.4f;
		hitCount_ = 0;
		isHitMapChip_ = false;
		isHitRect_ = false;
		blockCount = 0;

		isInsideLightLB_ = false;
		isInsideLightRB_ = false;
		isInsideLightLT_ = false;
		isInsideLightRT_ = false;
		preIsInsideLightLB_ = false;
		preIsInsideLightRB_ = false;
		preIsInsideLightLT_ = false;
		preIsInsideLightRT_ = false;

		starGetCount_ = 0;
	}

	void Init(int sceneNum);

	void Update(char* keys,Screen screen, Shadow& shadow,Player& player);

	void Draw(Screen screen);

	//アクセッサ
	Vec2 GetPos() { return pos_; }
};

