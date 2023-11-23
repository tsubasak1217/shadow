#pragma once
#include "Map.h"
class Player{

	Vec2 pos_;
	Vec2 prePos_;
	Vec2 size_;
	Vec2 direction_;
	Vec2 velocity_;
	Vector2<int>address_[4];
	Vector2<int>preAddress_[4];
	float speed_;

	//ブロックの移動中かどうか
	bool isMoveBlock_;
	float blockMoveT_;
	int moveTime_;
	int moveDirection_;
	Vector2<int>moveBlockAddress_;
	Vec2 moveStartPos_;
	Vec2 savedPlayerPos_;

	//スイッチを押せるかどうか
	bool isSwitchPushable_;

	//当たった回数
	bool isHitMapChip_;

public:

	Player(Map map) {
		pos_ = {
			map.firstPlayerPos_.x + map.GetPuzzleLeftTop().x,
			map.firstPlayerPos_.y + map.GetPuzzleLeftTop().y,
		};
		prePos_ = pos_;

		size_ = { 24.0f,24.0f };
		direction_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		speed_ = 4.0f;
		for (int i = 0; i < 4; i++) {
			address_[i] = {0,0};
			preAddress_[i] = address_[i];
		}

		isMoveBlock_ = false;
		blockMoveT_ = 0.0f;
		moveTime_ = 32;
		moveDirection_ = 0;
		moveBlockAddress_ = {0,0};
		moveStartPos_ = { 0.0f,0.0f };
		savedPlayerPos_ = { 0.0f,0.0f };

		isHitMapChip_ = 0;

		isSwitchPushable_ = true;
	}

	void Init(int sceneNum);

	void Update(char* keys,Map& map);

	void Draw(const Resources& rs);

	//アクセッサ
	Vec2 GetPos() { return pos_; }
	void SetSwitchPushable(bool flag) { isSwitchPushable_ = flag; }
};

