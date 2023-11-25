#pragma once
#include "stageClear.h"

const int STAR_MAX = 3;
const int EFP_MAX = 50;
class SCE {
	/*パーティクル本体*/
	Vec2 CPos_[STAR_MAX][EFP_MAX];
	float size_[STAR_MAX][EFP_MAX];
	int alpha_[STAR_MAX][EFP_MAX];
	float theta_[STAR_MAX][EFP_MAX];
	float MoveTheta_[STAR_MAX][EFP_MAX];
	float speed_[STAR_MAX][EFP_MAX];
	unsigned int color_[STAR_MAX][EFP_MAX];
	bool isAlive_[STAR_MAX][EFP_MAX];//エフェクト開始

	const int kPopTimer_=20;
	int popTimer_;


public:
	/*このフラグが立っているときシーンチェンジできるようになる*/
	bool canSceneChange;

	SCE() {
		for (int i = 0; i < STAR_MAX; i++) {
			for (int j = 0; j < EFP_MAX; j++) {
				CPos_[i][j] = { -200,-200 };
				size_[i][j] = float(rand() % 200) / 100;
				alpha_[i][j] = 0xFF;
				color_[i][j] = 0x00000000;
				theta_[i][j] = float(rand() % 128 + 1) / 256 * float(M_PI);
				MoveTheta_[i][j] = float(rand() % 200-100)/100;
				speed_[i][j] = 0;
				isAlive_[i][j] = false;
				popTimer_ = kPopTimer_;
			}
		}
		canSceneChange = false;

	}
	void Init(int i ,int j,StageClear stageColor);
	void Update(StageClear stageColor, int starGetCount);
	void Draw( int starGetCount);
};