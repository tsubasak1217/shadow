#pragma once
#include "selectDoor.h"

class SelectLightParticle {
	static const int kLifeTime_ = 120;

	int lifeTime_;
	bool isAlive_;
	int particleMax_;

	Vec2 pos_;
	float radius_;
	int alpha_;
	float theta_;
	float speed_;

	Vec2 startPos_;
	Vec2 moveVec_;

	//描画する範囲
	Vec2 DrawStartPos;
	Vec2 DrawEndPosL;
	Vec2 DrawEndPosR;

	bool isDraw;//立ってる時だけ描画される


public:

	void Init(float theta, Vec2 pos, float radius, float speed);
	void Update(const SelectDoor& Door);
	void Draw();
};