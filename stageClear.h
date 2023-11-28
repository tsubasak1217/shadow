#pragma once
#include "Map.h"

class StageClear {
	enum {//mado
		Left,
		Right
	};

	enum {//garasu
		LeftTop,
		LeftBottom,
		RightTop,
		RightBottom
	};

	/*星の変数*/


	float minSize_;
	float maxSize_;
	unsigned int starColor_;
	Vec2 starOriginPos_;
	float starTheta_[3];
	Vec2 length_;

	float MoveStarT_;
	float MoveStarAddT_;
	Vec2 maxLength_;
	Vec2 minLength_;
	float MoveStarEaseTimer_;

	Vec2 rotateLength_[3];

	bool isDrawStar_[3];

	/*窓*/
	Vec2 windowVertex_[2][4];
	Vec2 glassVertex_[4][4];
	unsigned int windowColor_;
	unsigned int skyColor_;


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

	int starGet_;

	int debugNum;
public:
	Vec2 starPos_[3];
	float starSize_;
	/*このフラグが立っているときシーンチェンジできるようになる*/
	bool canSceneChange;
	StageClear() {
		starSize_ = 1;//32
		minSize_ = 1;
		maxSize_ = 25;


		starColor_ = 0xFFFFFFFF;
		starOriginPos_ = { float(Global::windowSize_.x / 2),300 };

		/*星の変数*/
		for (int i = 0; i < 3; i++) {
			starPos_[i] = { float(Global::windowSize_.x / 2),300 };
			starTheta_[i] = 0;

			rotateLength_[i] = { 0 };
			isDrawStar_[i] = { 0 };
			starTheta_[i] = starTheta_[0] + (-2.0f / 3.0f * float(M_PI)) * i;
		}
		MoveStarT_ = 0;
		MoveStarAddT_ = 0;
		maxLength_ = { 110,0 };//200,0
		minLength_ = { 0,0 };
		length_ = minLength_;
		MoveStarEaseTimer_ = 60;



		windowColor_ = 0x444444FF;
		skyColor_ = 0x222222FF;


		/*ステージクリアの文字*/
		StageClearFontCPos_ = { 240,145 };//240,145
		StageClearFontSize_ = { 440,250 };//440,110

		/*キーを押してくださいの文字*/
		PressKeyFontCPos_ = { 240,645 };
		PressKeyFontSize_ = { 240,120 };

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



		/*猫*/
		CatSize_ = { 100,100 };
		CatCPos_ = { 110,490 };//{ float(Global::windowSize_.x) / 2,float(Global::windowSize_.y) - CatSize_.y };


		debugNum = 0;

		starGet_ = 0;
		canSceneChange = false;
	}

	void Update(bool isStartScene, int starGetCount);
	void Draw(Resources rs);
	void Debug(char* keys, char* preKeys);
	float GetFT() { return FT_; };
	void Reset();
};