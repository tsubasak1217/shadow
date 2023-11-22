#pragma once
#include "Map.h"

class StageClear {
	enum {
		UP,
		DOWN
	};


	/*回収したアイテムの数　何かを表示　*/
	Vec2 itemCPos_[3];
	Vec2 itemSize_;
	Vec2 itemVertex_[3][4];
	float itemMaxColor_;
	float itemMinColor_;
	float itemAddColor_;

	int easeNum_;//イージングするライトの色を決定する変数

	float lightT_;
	float lightAddT_;
	float lightEaseTimer_;
	float lightEaseDir_;

	float lightMaxColor_;
	float lightMinColor_;
	float lightAddColor_;
	unsigned int lightColor_[3];
	unsigned int itemColor_[3];

	/*一つのライトが点灯してから次のライトが点灯するまでの時間*/
	int nextLightEasingTimer_;
	int nextLightEasingTimerMax_;
	/*イージング開始フラグ*/
	bool isEaseL_;

	/*上下の黒枠*/
	Vec2 outerFrameCPos_[2];
	Vec2 outerFrameSize_;

	/*ステージクリアの文字*/
	Vec2 StageClearFontCPos_;
	Vec2 StageClearFontSize_;

	/*キーを押してくださいの文字*/
	Vec2 PressKeyFontCPos_;
	Vec2 PressKeyFontSize_;

	/*プレスキーの文字をふわふわさせる*/
	float PKT_;
	float PKEaseDir_;
	float PKEaseTimer_;
	float PKAddT_;
	float PKMaxPos_;
	float PKMinPos_;
	/*Fontを透明から白に変える*/
	float FT_;
	float FAddT_;
	float FEaseTimer_;
	float FEaseDir_;
	float FMaxColor_;
	float FMinColor_;
	float FAddColor_;
	unsigned int FColor_;
	bool isAppearFont_;

	/*猫*/
	Vec2 CatCPos_;
	Vec2 CatSize_;

	int debugNum;
public:
	StageClear() {
		/*とった数に応じて表示*/
		itemCPos_[0] = { 80.0f,float(Global::windowSize_.y) / 2.2f + 40 };
		itemCPos_[1] = { 240.0f,float(Global::windowSize_.y) / 2.2f - 40 };
		itemCPos_[2] = { 400.0f,float(Global::windowSize_.y) / 2.2f + 40 };

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				itemVertex_[i][j] = { 0 };
			}

			lightColor_[i] = 0xFFFFFF00;
			itemColor_[i] = 0x00000000;
		}
		itemSize_ = { 55,55 };
		itemMaxColor_ = 0xFF;
		itemMinColor_ = 0x0;
		itemAddColor_ = 0x00;

		/*ライトの色のイージング用の変数*/
		easeNum_ = 0;//イージングするライトの色を決定する変数

		lightT_ = 0;
		lightAddT_ = 0;
		lightEaseTimer_ = 10;
		lightEaseDir_ = 1;
		lightMaxColor_ = 0x44;
		lightMinColor_ = 0x0;
		lightAddColor_ = lightMinColor_;
		isEaseL_ = false;
		nextLightEasingTimerMax_ = 20;
		nextLightEasingTimer_ = nextLightEasingTimerMax_;


		/*ステージクリアの文字*/
		StageClearFontCPos_ = { 240,145 };
		StageClearFontSize_ = { 440,110 };

		/*キーを押してくださいの文字*/
		PressKeyFontCPos_ = { 240,645 };
		PressKeyFontSize_ = { 400,60 };

		/*プレスキーの文字をふわふわさせる*/
		PKT_ = 0;
		PKEaseDir_ = 1;
		PKEaseTimer_ = 60;
		PKAddT_ = 0;
		PKMaxPos_ = 655;
		PKMinPos_ = 645;
		/*Fontを透明から白に変える*/
		FT_ = 0;
		FAddT_ = 0;
		FEaseTimer_ = 20;
		FEaseDir_ = 1;

		FMaxColor_ = 0xFF;
		FMinColor_ = 0x0;
		FAddColor_ = FMinColor_;
		FColor_ = 0xFFFFFF00;
		isAppearFont_ = false;
		/*上下の枠の初期化*/
		outerFrameSize_ = { float(Global::windowSize_.x),50.0f };
		outerFrameCPos_[UP] = { 0,0 };
		outerFrameCPos_[DOWN] = { 0,float(Global::windowSize_.y) - outerFrameSize_.y };

		/*猫*/
		CatSize_ = { 100,100 };
		CatCPos_ = { float(Global::windowSize_.x) / 2,float(Global::windowSize_.y) - CatSize_.y };

		debugNum = 0;


	}

	void Update(bool isStartScene);
	void Draw();
	void Debug(char* keys, char* preKeys);
	float GetFT() { return FT_; };
	void Reset();
};