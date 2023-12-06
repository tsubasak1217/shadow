#include "global.h"

Vector2<int> Global::windowSize_ = { 480,720 };
bool Global::isMoveShadow_ = false;
int Global::timeCount_ = 0;
int Global::controlMode_ = 0;
int Global::character_ = 0;

Global::Global() {
}

Global::~Global() {
}

void Global::Update(const char* keys) {
	timeCount_++;

	if (Scene::sceneNum_ == GAME) {

		if (controlMode_ == 0) {

			if (keys[DIK_LSHIFT]) {
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