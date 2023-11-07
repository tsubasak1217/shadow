#include "Light.h"

void Light::Update(char* keys,Map map, float rangeTheta,Global global) {

	lightHitSpot_.clear();

	


	aimPos_ = { emitPos_.x,emitPos_.y - global.windowSize_.y };

	leftVec_ = Multiply(
		aimPos_.operator-(emitPos_),
		AffineMatrix({ 1.0f,1.0f }, -(rangeTheta * 0.5f), emitPos_)
	);

	rightVec_ = Multiply(
		aimPos_.operator-(emitPos_),
		AffineMatrix({ 1.0f,1.0f }, rangeTheta * 0.5f, emitPos_)
	);

	leftVec_ = CrossPos(emitPos_, leftVec_, { 0,0 }, {float(global.windowSize_.x),0});
	rightVec_ = CrossPos(emitPos_, rightVec_, { 0,0 }, { float(global.windowSize_.x),0 });



	if (keys[DIK_A]) {
		emitPos_.x -= 2.0f;
	}

	if (keys[DIK_D]) {
		emitPos_.x += 2.0f;
	}
};

void Light::Draw(Map map) {

	Novice::DrawTriangle(
		int(emitPos_.x),
		int(emitPos_.y),
		int(leftVec_.x),
		int(leftVec_.y),
		int(rightVec_.x),
		int(rightVec_.y),
		0xffff003f,
		kFillModeSolid
	);

	Novice::DrawEllipse(
		int(emitPos_.x),
		int(emitPos_.y),
		32, 32, 0.0f,
		0xff0000ff,
		kFillModeSolid
	);
};