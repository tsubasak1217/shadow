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

	bool isAlive_;
	bool preIsAlive_;
	bool isBackToRespawnPos_;
	bool preIsBackToRespawnPos_;
	int respawnTimeCount_;

	bool isJump_;
	bool  isDrop_;
	float jumpSpeed_;
	float jumpVelocity_;
	float dropSpeed_;
	float gravity_;

	//当たり判定
	int hitCount_;
	std::vector<int>hitSurface_;
	std::vector<int>preHitSurface_;
	std::vector<int>hitSurface2_;
	std::vector<int>preHitSurface2_;
	int blockCount;

	int boardingBlock_;
	Vec2 boardingPos_;
	float preBoadingVecRatio_;
	float boadingVecRatio_;

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

	//動いていない時間を計る変数
	int waitTimer_;

	//クリア
	int starGetCount_;

	int itemGetSEHandle_;

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

		isAlive_ = true;
		preIsAlive_ = isAlive_;
		isBackToRespawnPos_ = false;
		preIsBackToRespawnPos_ = isBackToRespawnPos_;
		respawnTimeCount_ = 200;

		isJump_ = false;
		isDrop_ = false;
		jumpSpeed_ = 0.0f;
		jumpVelocity_ = -7.5f;
		dropSpeed_ = 0.0f;
		gravity_ = 0.4f;
		hitCount_ = 0;
		isHitMapChip_ = false;
		isHitRect_ = false;
		blockCount = 0;
		boardingBlock_ = -1;
		boardingPos_ = { 0.0f,0.0f };
		boadingVecRatio_ = 0.0f;
		preBoadingVecRatio_ = boadingVecRatio_;

		isInsideLightLB_ = false;
		isInsideLightRB_ = false;
		isInsideLightLT_ = false;
		isInsideLightRT_ = false;
		preIsInsideLightLB_ = false;
		preIsInsideLightRB_ = false;
		preIsInsideLightLT_ = false;
		preIsInsideLightRT_ = false;

		waitTimer_ = 0;

		starGetCount_ = 0;
		itemGetSEHandle_=-1;
	}

	void Init(int sceneNum, Screen screen, Shadow shadow);

	void Update(char* keys, char* Prekeys, const Resources& rs, ChangeScene& cs, Screen& screen, Shadow& shadow, Player& player, Map& map, Light& light, bool isPause);

	void Draw(const Resources& rs, Screen screen);

	//アクセッサ
	Vec2 GetPos() { return pos_; }
	Vec2 GetSize() { return size_; }

	bool GetIsAlive() { return isAlive_; }
	bool GetIsPreAlive() { return preIsAlive_; }

	bool GetIsBackToResPawnPos() { return isBackToRespawnPos_; }
	bool GetPreIsBackToResPawnPos() { return preIsBackToRespawnPos_; }

	int GetstarCount() { return starGetCount_; }
};

