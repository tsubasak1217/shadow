#include "global.h"

Vector2<int> Global::windowSize_ = { 480,720 };
bool Global::isMoveShadow_ = false;
int Global::timeCount_ = 0;

Global::Global() {
}

Global::~Global() {
}

void Global::Update() {
	timeCount_++;
}