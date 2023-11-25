#include "Title.h"


void Title::Draw(Resources rs) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		/*背景*/
		Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, 0x000000FF, kFillModeSolid);

		//ライト
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
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
				int(titleVertex[i][0].x+20), int(titleVertex[i][0].y - 20),
				int(titleVertex[i][1].x + 20), int(titleVertex[i][1].y - 20),
				int(titleVertex[i][2].x + 20), int(titleVertex[i][2].y - 20),
				int(titleVertex[i][3].x+20), int(titleVertex[i][3].y-20),
				int(drawSize_[i]), 0, int(titleFontSize_.x), int(titleFontSize_.y), rs.titleFontGH_, titleFontColor_ - 0x99999999);

			Novice::DrawQuad(
				int(titleVertex[i][0].x), int(titleVertex[i][0].y),
				int(titleVertex[i][1].x), int(titleVertex[i][1].y),
				int(titleVertex[i][2].x), int(titleVertex[i][2].y),
				int(titleVertex[i][3].x), int(titleVertex[i][3].y),
				int(drawSize_[i]), 0, int(titleFontSize_.x), int(titleFontSize_.y), rs.titleFontGH_, titleFontColor_);
		}

		Novice::DrawSprite(
			int(spaceFontPos_.x), int(spaceFontPos_.y),
			rs.pressSpaceFontGH_, 1, 1, 0.0f, spaceFontColor_);

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
void Title::Update(char* keys, char* preKeys) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================

#pragma region"ライトの処理"
		for (int i = 0; i < 4; i++) {
			if (timeCount_ == (120 / 4) * i + 0) {
				isBlinking[i] = true;
			}
		}
		timeCount_++;
		if (timeCount_ >= 120) {
			timeCount_ = 0;
		}


		//足す透明度をイージング
		for (int i = 0; i < 4; i++) {
			if (isBlinking[i]) {
				lightT_[i] += (1.0f / lightEaseTimer_) * lightEaseDir_[i];
				lightAddT_[i] = EaseInOutBounce(lightT_[i]);
				addLightColor_[i] = (1 - lightAddT_[i]) * minLightColor_ + lightAddT_[i] * maxLightColor_;

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
				//Novice::ScreenPrintf(0, 150, "SCColor=%x", SCColor_);
				lightColor_[i] = 0xFFFFFF00 + int(addLightColor_[i]);//で透明度を足す

			}
		}
#pragma endregion

#pragma region"タイトルロゴの処理"
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			isTMove = true;
		}



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

#pragma endregion


#pragma region"プレスキーの処理"
		spaceFontPos_.y = sinf(theta_) * amplitude_ + 600;
		theta_ += 1.0f / 70.0f * (float)M_PI;

		if (isPush_) {
			if (SFT_ < 1.0f) {
				SFT_ += (1.0f / 24.0f);
			} else {
				SFT_ = 1.0f;
			}

			opacity_ = (1 - SFT_) * startOpacity_ + SFT_ * endOpacity_;
		}
		spaceFontColor_ = 0xFFFFFF00 + int(opacity_);
#pragma endregion
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

};