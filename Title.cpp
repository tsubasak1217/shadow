#include "Title.h"


void Title::Draw(Resources rs) {

	float alp = 1.0f - Global::titleAlphaEase_;

	int padSizeX = 64;
	int padSizeY = 48;

	Vec2 selectSize = { 240.0f,180.0f };
	float sin = fabsf(sinf((Global::timeCount_ / 120.0f) * 3.14f));

	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		/*背景*/
		Novice::DrawSprite(0, 0, rs.titleBGGH_, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, 0x000000FD, kFillModeSolid);

		//if (Global::isFirstBoot_) {

		My::DrawQuad(
			{
				float(Global::windowSize_.x) * 0.5f,
				float(Global::windowSize_.y * 0.5f) - (selectSize.y * 0.5f + 10),
			},
			selectSize * (1.0f - 0.2f * (1.0f - EaseOutBack(Global::PADTime_ / 16.0f))),
			0, 0,
			1200,
			1600,
			1.0f, 1.0f,
			rs.padGH_,
			0.0f,
			0xffffff00 + int((0x3a + ((0x3f + (0x7f * sin)) * (Global::controlMode_ == 1))) * Global::titleAlphaEase_)
			);

		My::DrawQuad(
			{
				float(Global::windowSize_.x) * 0.5f,
				float(Global::windowSize_.y * 0.5f) + (selectSize.y * 0.5f + 10),
			},
			selectSize * (1.0f - 0.2f * (1.0f - EaseOutBack(Global::KBTime_ / 16.0f))),
			0, 0,
			960,
			1280,
			1.0f, 1.0f,
			rs.keyboardGH_,
			0.0f,
			0xffffff00 + int((0x3a + ((0x3f + (0x7f * sin)) * (Global::controlMode_ == 0))) * Global::titleAlphaEase_)
			);

		//} else {

			//ライト
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				Novice::DrawSprite(int(lightPos_[i].x - lightRadius_), int(lightPos_[i].y - lightRadius_), rs.rengaGH_, 1, 1, 0.0f, WallColor_[i]);
				Novice::DrawEllipse(
					int(lightPos_[i].x), int(lightPos_[i].y),
					int(lightRadius_ + (j * 5)), int(lightRadius_ + (j * 5)),
					0.0f, lightColor_[i], kFillModeSolid
				);
			}
		}

		//タイトルロゴ
		for (int i = 0; i < 4; i++) {

			Novice::DrawQuad(
				int(titleVertex[i][0].x + 20), int(titleVertex[i][0].y - 20),
				int(titleVertex[i][1].x + 20), int(titleVertex[i][1].y - 20),
				int(titleVertex[i][2].x + 20), int(titleVertex[i][2].y - 20),
				int(titleVertex[i][3].x + 20), int(titleVertex[i][3].y - 20),
				int(drawSize_[i]), 0, int(titleFontSize_.x), int(titleFontSize_.y), rs.titleFontGH_, titleFontShadowColor_[i]);
			//タイトルフォント影カラー変数
			//もしiが２以下なら０それ以外なら１のlightカラーを参照する

			Novice::DrawQuad(
				int(titleVertex[i][0].x), int(titleVertex[i][0].y),
				int(titleVertex[i][1].x), int(titleVertex[i][1].y),
				int(titleVertex[i][2].x), int(titleVertex[i][2].y),
				int(titleVertex[i][3].x), int(titleVertex[i][3].y),
				int(drawSize_[i]), 0, int(titleFontSize_.x), int(titleFontSize_.y), rs.titleFontGH_, 0xFFFFFF00 + int(200.0f * alp));
		}


		// クレジット
			Novice::DrawSprite(
				int(TitlefontPos_.x - TitlefontSize_.x / 2),
				int(TitlefontPos_.y - TitlefontSize_.y / 2),
				rs.creditFontGH_, 0.5f, 0.5f, 0.0f, 0xFFFFFF00 + int(255.0f * alp)
			);

		if (Global::controlMode_ == 1) {
			Novice::DrawQuad(
				10, Global::windowSize_.y - (10 + padSizeY),
				10 + padSizeX, Global::windowSize_.y - (10 + padSizeY),
				10, Global::windowSize_.y - 10,
				10 + padSizeX, Global::windowSize_.y - 10,
				0, 0,
				1600, 1200,
				rs.padGH_,
				0xffffff00 + int(255.0f * alp)
			);


			Novice::DrawSprite(
				int(spaceFontPos_.x), int(spaceFontPos_.y),
				rs.pressSpaceFontGH_, 0.5f, 0.5f, 0.0f, spaceFontColor_);

		} else {
			Novice::DrawQuad(
				10, Global::windowSize_.y - (10 + padSizeY),
				10 + padSizeX, Global::windowSize_.y - (10 + padSizeY),
				10, Global::windowSize_.y - 10,
				10 + padSizeX, Global::windowSize_.y - 10,
				0, 0,
				1280, 960,
				rs.keyboardGH_,
				0xffffff00 + int(255.0f * alp)
			);

			Novice::DrawSprite(
				int(spaceFontPos_.x), int(spaceFontPos_.y),
				rs.pressSpaceFontGH3_, 0.5f, 0.5f, 0.0f, spaceFontColor_);
		}

		//}
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
		break;

	default:
		break;
	}

}


void Title::Update(char* keys, char* preKeys, Resources& rs) {

	float alp = 1.0f - Global::titleAlphaEase_;

	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================

		if (Global::firstBootLimit_ <= 0) {

			if (Global::controlMode_ == 0) {
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					if (!isTMove && !isPush_) {
						isTMove = true;//タイトルロゴを移動
						isPush_ = true;//スペースキーの透明度低下
						titlePushSEHandle_ = Novice::PlayAudio(rs.titlePushSE_, 0, 0.4f);

						rs.tutorial_[0] = Novice::LoadTexture("./Resources/images/tutorial1.png");
						rs.tutorial_[1] = Novice::LoadTexture("./Resources/images/tutorial2.png");
						rs.keysGH_ = Novice::LoadTexture("./Resources/images/keys1.png");
						//Global::controlMode_ = 0;
					}

				}
			}
			
			if (Global::controlMode_ == 1) {
				if (
					Novice::IsPressButton(0, kPadButton10) or
					Novice::IsPressButton(0, kPadButton11)
					) {

					if (!isTMove && !isPush_) {
						isTMove = true;//タイトルロゴを移動
						isPush_ = true;//スペースキーの透明度低下
						titlePushSEHandle_ = Novice::PlayAudio(rs.titlePushSE_, 0, 0.4f);

						rs.tutorial_[0] = Novice::LoadTexture("./Resources/images/tutorial2_1.png");
						rs.tutorial_[1] = Novice::LoadTexture("./Resources/images/tutorial2_2.png");
						rs.keysGH_ = Novice::LoadTexture("./Resources/images/keys2.png");
						//Global::controlMode_ = 1;
					}
				}
			}

			if (keys[DIK_ESCAPE] or Novice::IsTriggerButton(0, kPadButton4) or Novice::IsTriggerButton(0, kPadButton5)) {
				Global::isFirstBoot_ = true;
			}
		}

#pragma region"ライトの処理"
		for (int i = 0; i < 2; i++) {
			if (timeCount_ == (60 / 2) * i + 0) {
				isBlinking[i] = true;
			}
		}
		timeCount_++;
		if (timeCount_ >= 120) {
			timeCount_ = 0;
		}


		//足す透明度をイージング
		for (int i = 0; i < 2; i++) {
			if (isBlinking[i]) {
				lightT_[i] += (1.0f / lightEaseTimer_) * lightEaseDir_[i];
				lightAddT_[i] = EaseInOutBounce(lightT_[i]);
				addLightColor_[i] = (1 - lightAddT_[i]) * minLightColor_ + lightAddT_[i] * maxLightColor_;
				addWallColor_[i] = (1 - lightAddT_[i]) * minWallColor_ + lightAddT_[i] * maxWallColor_;

				if (lightT_[i] >= 1.0f) {
					lightT_[i] = 1.0f;
					lightWaitTimer_[i] -= 1;
					if (lightWaitTimer_[i] == 0) {
						lightEaseDir_[i] *= -1;
						lightWaitTimer_[i] = lightWaitTimerMax_;
					}
				}

				if (lightT_[i] <= 0.0f) {
					lightT_[i] = 0.0f;
					lightEaseDir_[i] *= -1;
					isBlinking[i] = false;
				}

				if (addLightColor_[i] >= maxLightColor_) {
					addLightColor_[i] = maxLightColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addLightColor_[i] <= minLightColor_) {
					addLightColor_[i] = minLightColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addWallColor_[i] >= maxWallColor_) {
					addWallColor_[i] = maxWallColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addWallColor_[i] <= minWallColor_) {
					addWallColor_[i] = minWallColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}


				//Novice::ScreenPrintf(0, 150, "SCColor=%x", SCColor_);
				lightColor_[i] = 0xFFFFFF00 + int(addLightColor_[i] * alp);//で透明度を足す
				WallColor_[i] = 0xFFFFFF00 + int(addWallColor_[i] * alp);//で透明度を足す

			}
		}
#pragma endregion

#pragma region"タイトルロゴの処理"




		if (isTMove) {
			TFT_ += (1.0f / 120) * TFEaseDir_;

			if (TFT_ >= 1.0f) {
				TFT_ = 1.0f;
				TFEaseDir_ *= -1;
				isTMove = false;
			}

			if (TFT_ <= 0.0f) {
				TFT_ = 0.0f;
				TFEaseDir_ *= -1;
				isTMove = false;
			}
		}
		TFAddT_ = EaseInOutQuint(TFT_);

		for (int i = 0; i < 4; i++) {
			titleFontPos_[i].x = (1 - TFAddT_) * minTitleFontPos_[i].x + TFAddT_ * maxTitleFontPos_[i].x;
			titleFontPos_[i].y = (1 - TFAddT_) * minTitleFontPos_[i].y + TFAddT_ * maxTitleFontPos_[i].y;
			VectorVertexS(titleVertex[i], titleFontPos_[i], titleFontSize_.x, titleFontSize_.y);
		}
		for (int i = 0; i < 4; i++) {
			if (i < 2) {
				titleFontShadowColor_[i] = lightColor_[0];
			} else {
				titleFontShadowColor_[i] = lightColor_[1];

			}
		}


#pragma endregion

#pragma region"プレスキーの処理"
		spaceFontPos_.y = sinf(theta_) * amplitude_ + 620;
		theta_ += 1.0f / 70.0f * (float)M_PI;

		if (isPush_) {
			if (SFT_ < 1.0f) {
				SFT_ += (1.0f / 24.0f);
			} else {
				SFT_ = 1.0f;

			}

			opacity_ = (1 - SFT_) * startOpacity_ + SFT_ * endOpacity_;
		}
		spaceFontColor_ = 0xFFFFFF00 + int(opacity_ * alp);
#pragma endregion



		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		Reset();
		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================
		Reset();
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		Reset();
		break;

	default:
		break;
	}

};


void Title::Reset() {

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


}