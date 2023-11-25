#include"stageClear.h"


void StageClear::Update(bool isStartScene) {


	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
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

		/*ライトイージング*/
#pragma region"ライトの透明度のイージング"

		if (!isStartScene) {/*シーン遷移が終わったら*/
			//ライトの透明度のイージング（高速でライトがパッとつくようなイメージ&&StartSceneフラグが降りてから数秒経過後）
			if (isEaseL_) {
				lightT_ += (1.0f / lightEaseTimer_) * lightEaseDir_;

				lightAddT_ = EaseInBounce(lightT_);
				lightAddColor_ = (1 - lightAddT_) * lightMinColor_ + lightAddT_ * lightMaxColor_;
				itemAddColor_ = (1 - lightAddT_) * itemMinColor_ + lightAddT_ * itemMaxColor_;

				if (lightT_ >= 1.0f) {
					/*T関連の値をリセットして*/
					lightT_ = 0.0f;
					lightAddT_ = 0.0f;
					lightAddColor_ = 0x00;
					itemAddColor_ = 0x00;
					isEaseL_ = false;//フラグを下す

					easeNum_ += 1;//次のライトへ
				}

				if (lightAddColor_ >= lightMaxColor_) {
					lightAddColor_ = lightMaxColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (lightAddColor_ <= lightMinColor_) {
					lightAddColor_ = lightMinColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (itemAddColor_ >= itemMaxColor_) {
					itemAddColor_ = itemMaxColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (itemAddColor_ <= itemMinColor_) {
					itemAddColor_ = itemMinColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}

				if (easeNum_ <= 2) {
					lightColor_[easeNum_] = 0xFFFFFF00 + int(lightAddColor_);//ここで透明度を足す
					itemColor_[easeNum_] = 0x66666600 + int(itemAddColor_);//ここで透明度を足す
				}

			} else {
				if (easeNum_ - 1 != -1) {
					itemColor_[easeNum_ - 1] = 0x666666FF;
				}
				if (easeNum_ <= 2) {//ライトの最大数以下の時
					nextLightEasingTimer_ -= 1;//タイマー経過

					if (nextLightEasingTimer_ == 0) {//０になったら
						isEaseL_ = true;//イージング開始
						nextLightEasingTimer_ = nextLightEasingTimerMax_;//タイマーを最大値に戻す
					}
				} else {

					isAppearFont_ = true;

				}

			}
		}

#pragma endregion

		/*ライトのイージングが終了した後*/
#pragma region"CLEARと文字押せを出現させる"
		if (isAppearFont_) {
			FT_ += (1.0f / FEaseTimer_) * FEaseDir_;

			FAddT_ = EaseInBounce(FT_);
			FAddColor_ = (1 - FAddT_) * FMinColor_ + FAddT_ * FMaxColor_;

			if (FT_ >= 1.0f) {
				FT_ = 1.0f;
			}

			if (FAddColor_ >= FMaxColor_) {
				FAddColor_ = FMaxColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			if (FAddColor_ <= FMinColor_) {
				FAddColor_ = FMinColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			FColor_ = 0xFFFFFF00 + int(FAddColor_);//ここで透明度を足す
		}
#pragma endregion

		/*PRESSキーを押せが出現した後*/
#pragma region"押せの文字をイージング"
		//文字が完全に出現したら動く
		if (FT_ >= 1.0f) {
			PKT_ += (1.0f / PKEaseTimer_) * PKEaseDir_;
			PKAddT_ = EaseInOutCubic(PKT_);
			PressKeyFontCPos_.y = (1 - PKAddT_) * PKMinPos_ + PKAddT_ * PKMaxPos_;
			if (PKT_ >= 1.0f) {
				PKT_ = 1.0f;
				PKEaseDir_ *= -1;
			}
			if (PKT_ <= 0.0f) {
				PKT_ = 0.0f;
				PKEaseDir_ *= -1;
			}
		}
#pragma endregion



		break;

	default:
		break;
	}




}



void StageClear::Draw(int starGetCount_,Resources rs) {
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

		/*背景*/
		Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, 0x444444FF, kFillModeSolid);
		for (int i = 0; i < 2; i++) {
			Novice::DrawBox(int(outerFrameCPos_[i].x), int(outerFrameCPos_[i].y), int(outerFrameSize_.x), int(outerFrameSize_.y), 0.0f, 0x000000FF, kFillModeSolid);

		}

		/*ライト*/
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				Novice::DrawEllipse(static_cast<int>(itemCPos_[i].x), static_cast<int>(itemCPos_[i].y),
					static_cast<int>(itemSize_.x + (j * itemSize_.x / 8)), static_cast<int>(itemSize_.y + (j * itemSize_.y / 8)), 0.0f, lightColor_[i], kFillModeSolid);
			}
		}
		for (int i = 0; i < starGetCount_; i++) {
			/*とったアイテム*/
			//Novice::DrawBox(int(itemCPos_[i].x - (itemSize_.x + 20) / 2), int(itemCPos_[i].y - (itemSize_.y + 20) / 2), int(itemSize_.x + 20), int(itemSize_.y + 20), 0.0f, itemColor_[i], kFillModeWireFrame);
			My::DrawStar(
				itemCPos_[i],
				itemSize_.x * 0.7f,
				0.0f,
				itemColor_[i]
			);
		}

		/*ステージクリアの文字*/
		//Novice::DrawBox(int(StageClearFontCPos_.x - StageClearFontSize_.x / 2), int(StageClearFontCPos_.y - StageClearFontSize_.y / 2), int(StageClearFontSize_.x), int(StageClearFontSize_.y), 0.0f, FColor_, kFillModeWireFrame);
		Novice::DrawSprite(int(StageClearFontCPos_.x - StageClearFontSize_.x / 2), int(StageClearFontCPos_.y - StageClearFontSize_.y / 2), rs.stageClearFontGH_, 1, 1, 0.0f, FColor_);

		/*猫*/
		DrawCat(CatCPos_, CatSize_.x, CatSize_.y, 0x000000FF);

		/*押してくださいの文字*/
		//Novice::DrawBox(int(PressKeyFontCPos_.x - PressKeyFontSize_.x / 2), int(PressKeyFontCPos_.y - PressKeyFontSize_.y / 2), int(PressKeyFontSize_.x), int(PressKeyFontSize_.y),
			//0.0f, FColor_, kFillModeWireFrame);
		Novice::DrawSprite(int(PressKeyFontCPos_.x - PressKeyFontSize_.x / 2), int(PressKeyFontCPos_.y - PressKeyFontSize_.y / 2),rs.pressSpaceFontGH_, 1, 1, 0.0f, FColor_);


		break;

	default:
		break;
	}

#pragma endregion

}
#if _DEBUG
void StageClear::Debug(char* keys, char* preKeys) {

#pragma region"デバック用"


	//操作したい番号選択
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		debugNum += 1;
		//[1]=originPos_
		//[2]=size_
		//[3]=length_
		if (debugNum == 4) {
			debugNum = 0;
		}

	}
	switch (debugNum)
	{
	case 0:
		if (keys[DIK_W]) {
			PressKeyFontCPos_.y -= 1;
		}
		if (keys[DIK_S]) {
			PressKeyFontCPos_.y += 1;
		}
		if (keys[DIK_A]) {
			PressKeyFontCPos_.x -= 1;
		}
		if (keys[DIK_D]) {
			PressKeyFontCPos_.x += 1;
		}
		break;

	case 1:
		if (keys[DIK_W]) {
			PressKeyFontSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			PressKeyFontSize_.y += 1;
		}
		if (keys[DIK_A]) {
			PressKeyFontSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			PressKeyFontSize_.x += 1;
		}
		break;

	case 2:
		if (keys[DIK_W]) {
			StageClearFontCPos_.y -= 1;
		}
		if (keys[DIK_S]) {
			StageClearFontCPos_.y += 1;
		}
		if (keys[DIK_A]) {
			StageClearFontCPos_.x -= 1;
		}
		if (keys[DIK_D]) {
			StageClearFontCPos_.x += 1;
		}
		break;
	case 3:
		if (keys[DIK_W]) {
			StageClearFontSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			StageClearFontSize_.y += 1;
		}
		if (keys[DIK_A]) {
			StageClearFontSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			StageClearFontSize_.x += 1;
		}
		break;


	default:
		break;
	}

	Novice::ScreenPrintf(0, 20, "debugNum=%d", debugNum);
	Novice::ScreenPrintf(0, 40, "PressKeyFontCPos_ x=%f,y=%f", PressKeyFontCPos_.x, PressKeyFontCPos_.y);
	Novice::ScreenPrintf(0, 60, "PressKeyFontSize_ x=%f,y=%f", PressKeyFontSize_.x, PressKeyFontSize_.y);
	Novice::ScreenPrintf(0, 80, "StageClearFontCPos_ x=%f,y=%f", StageClearFontCPos_.x, StageClearFontCPos_.y);
	Novice::ScreenPrintf(0, 100, "StageClearFontSize_x = %f, y = %f", StageClearFontSize_.x, StageClearFontSize_.y);


#pragma endregion

}
#endif // _DEBUG
void StageClear::Reset() {
#pragma region"リセット"
	for (int i = 0; i < 3; i++) {
		lightColor_[i] = 0xFFFFFF00;
		itemColor_[i] = 0x00000000;
	}
	itemMaxColor_ = 0xFF;
	itemMinColor_ = 0x0;
	itemAddColor_ = 0x00;

	/*ライトの色のイージング用の変数*/
	easeNum_ = 0;//イージングするライトの色を決定する変数
	lightT_ = 0;
	lightAddT_ = 0;
	lightEaseDir_ = 1;
	lightMaxColor_ = 0x44;
	lightMinColor_ = 0x0;
	lightAddColor_ = lightMinColor_;
	isEaseL_ = false;
	nextLightEasingTimerMax_ = 20;
	nextLightEasingTimer_ = nextLightEasingTimerMax_;


	/*キーを押してくださいの文字*/
	PressKeyFontCPos_ = { 240,645 };
	PressKeyFontSize_ = { 240,120 };

	/*プレスキーの文字をふわふわさせる*/
	PKT_ = 0;
	PKEaseDir_ = 1;
	PKEaseTimer_ = 60;
	PKAddT_ = 0;

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















#pragma endregion

};