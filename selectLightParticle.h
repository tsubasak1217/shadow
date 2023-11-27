#pragma once
#include "selectDoor.h"
#include "Light.h"

class SelectLightParticle {
	static const int kLifeTime_ = 120;

	int lifeTime_;
	bool isAlive_;
	int particleMax_;

	Vec2 pos_;
	float radius_;
	int alpha_;
	int alphaDir_;
	float theta_;
	float speed_;

	//描画する範囲
	Vec2 DrawStartPos;
	Vec2 DrawEndPosL;
	Vec2 DrawEndPosR;

	bool isDraw;//立ってる時だけ描画される


public:
	SelectLightParticle() {

		lifeTime_ = kLifeTime_;
		isAlive_ = false;
		particleMax_ = 240;

		theta_ = float((rand() % 200) - 100) / 100;
		pos_ = { float(rand() % Global::windowSize_.x), float(rand() % Global::windowSize_.y) };
		radius_ = float(rand() % 200) / 100;
		speed_ = float(rand() % 200) / 100;


		pos_ = { 0 };
		radius_ = { 0 };
		alpha_ = 0x00;
		alphaDir_ = 1;
		theta_ = 0;
		speed_ = { 0 };

		//描画する範囲
		DrawStartPos = { 0 };
		DrawEndPosL = { 0 };
		DrawEndPosR = { 0 };

		isDraw = false;//立ってる時だけ描画される

	}


	void Init(float theta, Vec2 pos, float radius, float speed);
	void Update(const SelectDoor& Door, Light light);
	void Draw(char* keys);
};