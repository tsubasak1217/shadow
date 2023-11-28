#pragma once
#include "Map.h"

class Title {
public:
	int timeCount_;
	//ライトの変数[4]
	Vec2 lightPos_[2];
	float lightRadius_;
	/*イージングDrawLight*/
	float lightT_[2];
	float lightAddT_[2];
	/*イージングの時間*/
	float lightEaseTimer_;
	/*方向*/
	float lightEaseDir_[2];
	/*イージング最大最小加える値*/
	float maxLightColor_;
	float minLightColor_;
	float addLightColor_[2];
	/*表示され続ける時間*/
	float lightWaitTimer_[2];
	float lightWaitTimerMax_;
	/*色*/
	unsigned int lightColor_[2];
	bool isBlinking[2];


	//タイトルの文字[4]
	Vec2 titleFontPos_[4];
	Vec2 titleVertex[4][4];
	Vec2 maxTitleFontPos_[4];
	Vec2 minTitleFontPos_[4];
	Vec2 titleFontSize_;
	float drawSize_[4];
	/*イージング用*/
	float TFT_;
	float TFAddT_;
	float TFEaseDir_;
	unsigned int titleFontColor_;
	unsigned int titleFontShadowColor_[4];
	bool isTMove = true;

	//スペースの文字
	Vec2 spaceFontPos_;
	float opacity_;//色？
	float endOpacity_;
	float startOpacity_;
	float amplitude_;//振れ幅？
	float theta_;
	bool isPush_;//SPACEキーが押されたときの変数

	float SFT_;
	float SFAddT_;
	unsigned int spaceFontColor_;


	/*イージング最大最小加える値*/
	float maxWallColor_;
	float minWallColor_;
	float addWallColor_[2];
	unsigned int WallColor_[2];

	Vec2 TitlefontPos_ = { 380,20 };
	Vec2 TitlefontSize_ = { 300,40 };

	int titlePushSEHandle_;//タイトル画面でプレスキーを押したときの音

	Title() {
		timeCount_ = 0;
		/*表示され続ける時間*/
		lightWaitTimerMax_ = 600;
		lightRadius_ = 144.0f;
		lightPos_[0] = { 20.0f + lightRadius_,30.0f + lightRadius_ };
		lightPos_[1] = { 180.0f + lightRadius_,300.0f + lightRadius_ };//暗

		for (int i = 0; i < 2; i++) {
			/*イージングDrawLight*/
			lightT_[i] = 0;
			lightAddT_[i] = 0;
			/*方向*/
			lightEaseDir_[i] = 1;
			addLightColor_[i] = 0x00;
			lightWaitTimer_[i] = lightWaitTimerMax_;
			/*色*/
			lightColor_[i] = 0xFFFFFF00;
			isBlinking[i] = false;

		}
		/*イージングの時間*/
		lightEaseTimer_ = 60;
		/*イージング最大最小加える値*/
		maxLightColor_ = 0x44;
		minLightColor_ = 0x0;
		//タイトルの文字[4]

		minTitleFontPos_[0] = { -240.0f,lightPos_[0].y };
		minTitleFontPos_[1] = { 720.0f,lightPos_[0].y };
		minTitleFontPos_[2] = { -240.0f,lightPos_[1].y };
		minTitleFontPos_[3] = { 720.0f,lightPos_[1].y };

		for (int i = 0; i < 4; i++) {
			titleFontPos_[i] = minTitleFontPos_[i];

			titleFontShadowColor_[i] = 0xFFFFFF00;
			for (int j = 0; j < 4; j++) {
				titleVertex[i][j] = { 0 };
			}
		}
		titleFontSize_ = { 240,240 };

		for (int i = 0; i < 4; i++) {
			if (i < 2) {
				drawSize_[i] = 0;
				maxTitleFontPos_[i] = lightPos_[0];// { 160.0f,220.0f };//迷
			} else {
				drawSize_[i] = 240;
				maxTitleFontPos_[i] = lightPos_[1]; //{ 320.0f,470.0f };//暗
			}

		}
		TFT_ = 0;
		TFAddT_ = 0;
		TFEaseDir_ = 1;
		titleFontColor_ = 0xFFFFFFFF;
		isTMove = true;

		//スペースの文字
		spaceFontPos_ = { 120.0f,400.0f };
		opacity_ = 0xFF;
		endOpacity_ = 0x00;
		startOpacity_ = 0xFF;
		amplitude_ = 5.0f;
		theta_ = 0.0f;
		isPush_ = false;

		SFT_ = 0;
		SFAddT_ = 0;

		spaceFontColor_ = 0xFFFFFF00;


		/*イージング最大最小加える値*/
		maxWallColor_ = 0xFF;
		minWallColor_ = 0x00;
		for (int i = 0; i < 2; i++) {
			addWallColor_[i] = minWallColor_;
			WallColor_[i] = 0xFFFFFF00;
		}

		titlePushSEHandle_ = -1;
	}

	void Draw(Resources rs);
	void Update(char* keys, char* preKeys, const Resources& rs);
	void Reset();
};