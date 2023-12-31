﻿#include"stageClearEffect.h"

void SCE::Init(int i, int j, StageClear stageColor) {

	CPos_[i][j] = stageColor.starPos_[i];
	size_[i][j] = float(rand() % 500/*1000*/) / 100 * (stageColor.starSize_ / 25);
	alpha_[i][j] = 0xFF;
	color_[i][j] = 0x00000000;
	MoveTheta_[i][j] = float(rand() % 200 - 100) / 100;

	isAlive_[i][j] = true;

}

void SCE::Update(StageClear stageColor, int starGetCount) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		for (int i = 0; i < starGetCount; i++) {
			for (int j = 0; j < EFP_MAX; j++) {


				if (!isAlive_[i][j]) {
					popTimer_--;
					if (popTimer_ <= 0) {
						Init(i, j, stageColor);
						speed_[i][j] = size_[i][j] / 5;
						popTimer_ = kPopTimer_;
						break;
					}
				}
			}
		}

		for (int i = 0; i < starGetCount; i++) {
			for (int j = 0; j < EFP_MAX; j++) {
				if (isAlive_[i][j]) {
					alpha_[i][j] -= int((float(0xff) / 40));//透明度を下げていく

					CPos_[i][j].x += MoveTheta_[i][j] * speed_[i][j];
					CPos_[i][j].y += MoveTheta_[i][j] * speed_[i][j];
					if (alpha_[i][j] <= 0x00) {
						alpha_[i][j] = 0x00;
						isAlive_[i][j] = false;
					}
				}
				color_[i][j] = 0xFFFFFF00 + alpha_[i][j];

			}
		}



		break;
	}
	if (Scene::sceneNum_ != CLEAR) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < EFP_MAX; j++) {
				isAlive_[i][j] = false;
			}
		}
	}
}


void SCE::Draw(int starGetCount) {

	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
#pragma region"描画"
		for (int i = 0; i < starGetCount; i++) {
			for (int j = 0; j < EFP_MAX; j++) {
				if (isAlive_[i][j]) {
					My::DrawTriangle(CPos_[i][j], size_[i][j], float(theta_[i][j]), color_[i][j]);
				}
			}
		}
#pragma endregion

		break;
	}

}