#include "global.h"

Vector2<int> Global::windowSize_ = { 480,720 };
bool Global::isMoveShadow_ = false;
int Global::timeCount_ = 0;
int Global::controlMode_ = 0;
int Global::character_ = 0;

Vector2<int> Global::leftStickValue_ = { 0,0 };
Vector2<int> Global::preLeftStickValue_ = { 0,0 };
bool Global::isTriggerLeftStick_UP_ = false;
bool Global::isTriggerLeftStick_DOWN_ = false;
bool Global::isTriggerLeftStick_RIGHT_ = false;
bool Global::isTriggerLeftStick_LEFT_ = false;
bool Global::isReleaseB_ = false;
bool Global::isB_ = false;
bool Global::preIsB_ = false;

Global::Global() {
}

Global::~Global() {
}

void Global::Update(const char* keys, const char* preKeys) {
	timeCount_++;

	//前フレームのスティックの状態を保存
	preLeftStickValue_ = leftStickValue_;

	//スティック関連を初期化
	leftStickValue_ = { 0,0 };
	isTriggerLeftStick_UP_ = false;
	isTriggerLeftStick_DOWN_ = false;
	isTriggerLeftStick_RIGHT_ = false;
	isTriggerLeftStick_LEFT_ = false;

	isReleaseB_ = false;

	//前フレームの状態保存
	preIsB_ = isB_;

	//スティックの状態を取得
	Novice::GetAnalogInputLeft(0, &leftStickValue_.x, &leftStickValue_.y);

	//キーの状態取得
	isB_ = Novice::IsPressButton(0, kPadButton11);

	//リリースフラグを立てる
	if (!isB_ && preIsB_) {
		isReleaseB_ = true;
	}

	if (preLeftStickValue_.x == 0 && preLeftStickValue_.y == 0) {

		//右トリガー
		if (leftStickValue_.x > 0) {
			isTriggerLeftStick_RIGHT_ = true;
		} else if (leftStickValue_.x < 0) {//左トリガー
			isTriggerLeftStick_LEFT_ = true;
		}

		//下トリガー
		if (leftStickValue_.y > 0) {
			isTriggerLeftStick_DOWN_ = true;
		} else if (leftStickValue_.y < 0) {//上トリガー
			isTriggerLeftStick_UP_ = true;
		}
	}

	if (Scene::sceneNum_ == GAME) {

		if (controlMode_ == 0) {

			if (character_ == 0) {
				if (keys[DIK_S] && !preKeys[DIK_S]) {
					character_ = 1;
				}
			} else {
				if (keys[DIK_S] && !preKeys[DIK_S]) {
					character_ = 0;
				}
			}
		} else {
			/*if (Novice::IsTriggerButton(0,kPadButton11)) {

				if (character_ == 0) {
					character_ = 1;
				} else {
					character_ = 0;
				}
			}*/

			if (character_ == 0) {
				if (Novice::IsTriggerButton(0, kPadButton1)) {
					character_ = 1;
				}
			} else {
				if (Novice::IsTriggerButton(0, kPadButton0)) {
					character_ = 0;
				}
			}
		}
	}
}

void Global::Draw(const Resources& rs) {

	if (Scene::sceneNum_ == GAME) {

		float sin = sinf((float(timeCount_) / 64.0f) * float(M_PI));
		Vec2 pos = { 436.0f,415.0f };

		// 右側のキャラ切り替えの十字キー説明表示
		Novice::DrawSpriteRect(
			int(pos.x),
			int(pos.y),
			0, 0,
			1121, 1121,
			rs.crossKeyGH_[character_ == 0],
			0.03f,
			0.03f,
			0.0f,
			0xffffff5f + int(32.0f * sin)
		);


		My::DrawTriangle(
			pos.operator+({
				17.0f,
				-17.0f + (68.0f * (character_ == 0)) + (fabsf(-6.0f * sin) * Opp((character_ == 0)))
				}),
			8.0f,
			3.14f * (character_ == 0),
			0xffffff5f + int(32.0f * sin)
		);
	}
}
