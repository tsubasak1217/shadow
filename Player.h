#pragma once
#include "Map.h"
class Player {

	Vec2 pos_;
	Vec2 prePos_;
	Vec2 size_;
	Vec2 direction_;
	Vec2 velocity_;
	Vector2<int>address_[4];
	Vector2<int>preAddress_[4];
	Vector2<int>centerAddress_;
	float speed_;

	//ブロックの移動中かどうか
	bool isMoveBlock_;
	bool isStopMove_;
	int moveStopTime_;
	float blockMoveT_;
	int moveTime_;
	int moveDirection_;
	Vector2<int>moveBlockAddress_;
	Vec2 moveStartPos_;
	Vec2 savedPlayerPos_;
	bool isSwappped_;

	//スイッチを押せるかどうか
	bool isSwitchPushable_;
	//ブロックを押せるかどうか
	bool isBlockPushable_;
	bool isViewTelop_;
	//当たった回数
	bool isHitMapChip_;

	//動いていない時間を取得
	int waitTimer_;
	//操作説明画像の透明度
	int tutorialSpriteAlpha_;

	int moveBoxSEHandle_;//木箱を押すときの音
	int switchSEHandle_ ;//スイッチを押すときの音

public:

	int swapTimeCount_;
	bool killSwitch_;

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
			address_[i] = { 0,0 };
			preAddress_[i] = address_[i];
		}
		centerAddress_.x = int((pos_.x - map.GetPuzzleLeftTop().x) / map.GetSize().x);
		centerAddress_.y = int((pos_.y - map.GetPuzzleLeftTop().y) / map.GetSize().y);

		isMoveBlock_ = false;
		isStopMove_ = false;
		moveStopTime_ = 32;
		blockMoveT_ = 0.0f;
		moveTime_ = 32;
		moveDirection_ = 0;
		moveBlockAddress_ = { 0,0 };
		moveStartPos_ = { 0.0f,0.0f };
		savedPlayerPos_ = { 0.0f,0.0f };
		isSwappped_ = false;
		swapTimeCount_ = 2;

		isHitMapChip_ = 0;

		isSwitchPushable_ = true;
		isBlockPushable_ = false;
		isViewTelop_ = false;
		waitTimer_ = 0;
		tutorialSpriteAlpha_ = 0;
		killSwitch_ = false;
		moveBoxSEHandle_ = -1;
		switchSEHandle_ = -1;
	}

	void Init(int sceneNum, Map map);

	void Update(char* keys, const ChangeScene& cs, Map& map, bool isPause, const Resources& rs);

	void Draw(const char* keys, const Resources& rs);

	//アクセッサ
	Vec2 GetPos() { return pos_; }
	void SetSwitchPushable(bool flag) { isSwitchPushable_ = flag; }
	bool GetIsSwapped() { return isSwappped_; }
	bool GetIsMoveBlock() { return isMoveBlock_; }

	void ReturnSavePoint(Map map);
};

