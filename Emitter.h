#pragma once
#include "PlayerShadow.h"
class Emitter {

	Vec2 pos_;
	Vec2 range_;

public:

	Emitter() {
		pos_ = { -100.0f,-100.0f };
		range_ = { 0.0f,0.0f };
	}

	Vec2 GetPos_() { return pos_; }
	Vec2 GetRange_() { return range_; }

	void Set(Vec2 pos, Vec2 range) {
		range_ = range;
		pos_ = pos;
	}

};

