#pragma once
#include "Map.h"

const int EFP_MAX = 20;
class SCE {
	/*パーティクル本体*/
	Vec2 CPos_[EFP_MAX];
	Vec2 vertex_[EFP_MAX][4];
	Vec2 affineVertex_[EFP_MAX][4];
	float size_[EFP_MAX];
	Vec2 vel_[EFP_MAX];
	Vec2 Dirvel_[EFP_MAX];
	Vec2 acc_;
	float moveSpeed[EFP_MAX];


	/*イージング*/
	float t_;
	float addT_;
	float easeTimer_;
	Vec2 scale_;
	/*回転*/
	float rotateTheta_[EFP_MAX];
	float theta_[EFP_MAX];

	Matrix3x3 affineMatrix_[EFP_MAX];
	int GH;
	unsigned int color_;

	int EffectCount;//エフェクトが地面に落ちた数をカウントする
	bool isEffect_;//エフェクト開始

public:
	/*このフラグが立っているときシーンチェンジできるようになる*/
	bool canSceneChange;

	SCE() {
		for (int i = 0; i < EFP_MAX; i++) {
			CPos_[i] = { 0 };
			size_[i] = float(rand() % 30 + 15);

			t_ = 0;
			addT_ = 0;
			easeTimer_ = 30.0f;
			scale_ = { 1,1 };

			rotateTheta_[i] = { 0 };
			theta_[i] = (1.0f / static_cast<int>(rand() % 30 + 10) * float(M_PI));
			for (int j = 0; j < 4; j++) {
				vertex_[i][j] = { 0 };
				affineVertex_[i][j] = { 0 };
			}
			vel_[i] = { 0 };
			Dirvel_[i] = { 0 };
			acc_ = { 0,0.6f };
			isEffect_ = false;
			moveSpeed[i] = float(rand() % 5 + 20);
			GH = Novice::LoadTexture("./NoviceResources/white1x1.png");
			EffectCount = 0;
			canSceneChange = false;
			color_=0x000000FF;
		}


	}
	void Init();
	void Update(float FT);
	void Draw();
};