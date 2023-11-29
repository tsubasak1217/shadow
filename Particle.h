#pragma once
#include "Emitter.h"

class Particle {
	static const int kLifeTime_ = 120;

	int lifeTime_;
	bool isAlive_;
	int particleMax_;

	Vec2 pos_;
	Vec2 size_;
	int alpha_;
	float theta_;
	float speed_;

	Vec2 startPos_;
	Vec2 moveVec_;

public:

	Particle() {

		lifeTime_ = kLifeTime_;
		isAlive_ = false;
		particleMax_ = 120;

		pos_ = {-100.0f,-100.0f};
		size_ = {8.0f,8.0f};
		alpha_ = 0xff;
		theta_ = 0.0f;
		speed_ = float(rand()%30)/10.0f;
		startPos_ = { -100.0f,-100.0f };
		moveVec_ = { 0.0f,0.0f };

	}

	void Init();
	void Init(float theta, Vec2 pos, Vec2 size, float speed);
	void Update(Emitter emitter,PlayerShadow pShadow,const Shadow& shadow, Screen screen, const char* keys);
	void Draw();
};

