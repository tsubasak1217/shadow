#include "global.h"

Vector2<int> Global::windowSize_ = { 480,720 };
bool Global::isMoveShadow_ = false;
int Global::timeCount_ = 0;
int Global::controlMode_ = 0;
int Global::character_ = 0;

Vector2<int> Global::leftStickValue_ = {0,0};
Vector2<int> Global::preLeftStickValue_ = { 0,0 };
bool Global::isTriggerLeftStick_UP_ = false;
bool Global::isTriggerLeftStick_DOWN_ = false;
bool Global::isTriggerLeftStick_RIGHT_ = false;
bool Global::isTriggerLeftStick_LEFT_ = false;

Global::Global() {
}

Global::~Global() {
}

void Global::Update(const char* keys,const char* preKeys) {
	timeCount_++;

	//前フレームのスティックの状態を保存
	preLeftStickValue_ = leftStickValue_;

	//スティック関連を初期化
	leftStickValue_ = { 0,0 };
	isTriggerLeftStick_UP_ = false;
	isTriggerLeftStick_DOWN_ = false;
	isTriggerLeftStick_RIGHT_ = false;
	isTriggerLeftStick_LEFT_ = false;

	//スティックの状態を取得
	Novice::GetAnalogInputLeft(0, &leftStickValue_.x, &leftStickValue_.y);

	if (preLeftStickValue_.x == 0 && preLeftStickValue_.y == 0) {

		//右トリガー
		if (leftStickValue_.x > 0) {
			isTriggerLeftStick_RIGHT_ = true;
		} else if(leftStickValue_.x < 0) {//左トリガー
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

			if (keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT]) {
				if (character_ == 0) {
					character_ = 1;
				} else {
					character_ = 0;
				}
			}
		} else {
			if (Novice::IsTriggerButton(0, kPadButton13)) {

				if (character_ == 0) {
					character_ = 1;
				} else {
					character_ = 0;
				}
			}
		}
	}
}