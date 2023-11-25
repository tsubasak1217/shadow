#include"stageClear.h"


void StageClear::Update(bool isStartScene, int starGetCount) {


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
		starGet_ = starGetCount;

		//中心（オリジンポス）を基準とした角度
		for (int i = 0; i < 3; i++) {
			starTheta_[i] += (1.0f / 60.0f);//回転させる	
			rotateLength_[i] = rotateVect(length_, sinf(starTheta_[i]), cosf(starTheta_[i]));
			starPos_[i] = getVectAdd(rotateLength_[i], starOriginPos_);
		}
		if (!isStartScene) {

			//文字が完全に出現したら動く
			if (FT_ >= 1.0f) {
				MoveStarT_ += (1.0f / MoveStarEaseTimer_);
				MoveStarAddT_ = EaseInOutCubic(MoveStarT_);
				length_.x = (1 - MoveStarAddT_) * minLength_.x + MoveStarAddT_ * maxLength_.x;
				if (MoveStarT_ >= 1.0f) {
					MoveStarT_ = 1.0f;
				}
			}
		}



#pragma region"CLEARと文字押せを出現させる"

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



void StageClear::Draw(Resources rs) {
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
		Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, 0x000000FF, kFillModeSolid);

		/*上下の黒幕*/
		for (int i = 1; i < 2; i++) {
			//Novice::DrawBox(int(outerFrameCPos_[i].x), int(outerFrameCPos_[i].y), int(outerFrameSize_.x), int(outerFrameSize_.y), 0.0f, 0xFFFFFFFF, kFillModeSolid);

		}

		/*星*/
		for (int i = 0; i < starGet_; i++) {
			My::DrawStar(starPos_[i], starSize_, 0.0f, starColor_);
		}
		/*ゲットできなかった星（ワイヤーフレームにする）*/
		for (int i = starGet_; i < (3 - starGet_); i++) {
			My::DrawStar(starPos_[i], starSize_, 0.0f, 0x444444FF);
		}


		if (starGet_ >= 2) {
			Novice::DrawLine(int(starPos_[0].x), int(starPos_[0].y), int(starPos_[1].x), int(starPos_[1].y), starColor_);
			if (starGet_ >= 3) {
				Novice::DrawLine(int(starPos_[0].x), int(starPos_[0].y), int(starPos_[2].x), int(starPos_[2].y), starColor_);
				Novice::DrawLine(int(starPos_[1].x), int(starPos_[1].y), int(starPos_[2].x), int(starPos_[2].y), starColor_);
			}
		}


		if (debugNum % 2 == 0) {
			/*ステージクリアの文字*/
			Novice::DrawSprite(int(StageClearFontCPos_.x - StageClearFontSize_.x / 2), int(StageClearFontCPos_.y - StageClearFontSize_.y / 2), rs.stageClearFontGH_, 1, 1, 0.0f, FColor_);
		} else {
			Novice::DrawSprite(int(StageClearFontCPos_.x - 220 / 2),
				int(StageClearFontCPos_.y + 150 - 220 / 2), rs.stageClearFont2GH_, 1, 1, 0.0f, FColor_);
		}


		/*猫*/
		//DrawCat(CatCPos_, CatSize_.x, CatSize_.y, 0x000000FF);

		/*押してくださいの文字*/
		Novice::DrawSprite(int(PressKeyFontCPos_.x - PressKeyFontSize_.x / 2), int(PressKeyFontCPos_.y - PressKeyFontSize_.y / 2), rs.pressSpaceFontGH_, 0.5f, 0.5f, 0.0f, FColor_);


		break;

	default:
		break;
	}

#pragma endregion

}

void StageClear::Debug(char* keys, char* preKeys) {
	keys, preKeys;
#if _DEBUG
#pragma region"デバック用"

	if (keys[DIK_R] && !preKeys[DIK_R]) {
		length_ = minLength_;
		MoveStarT_ = 0;
		MoveStarAddT_ = 0;

	}

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
			length_.x -= 1;
		}
		if (keys[DIK_S]) {
			length_.x += 1;
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
			maxLength_.y -= 1;
		}
		if (keys[DIK_S]) {
			maxLength_.y += 1;
		}
		if (keys[DIK_A]) {
			maxLength_.x -= 1;
		}
		if (keys[DIK_D]) {
			maxLength_.x += 1;
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
	/*
	Novice::ScreenPrintf(0, 20, "debugNum=%d", debugNum);
	Novice::ScreenPrintf(0, 40, "length x=%f,y=%f", length_.x, length_.y);
	Novice::ScreenPrintf(0, 60, "maxLength_ x=%f,y=%f", maxLength_.x, maxLength_.y);
	Novice::ScreenPrintf(0, 80, "StageClearFontCPos_ x=%f,y=%f", StageClearFontCPos_.x, StageClearFontCPos_.y);
	Novice::ScreenPrintf(0, 100, "StageClearFontSize_x = %f, y = %f", StageClearFontSize_.x, StageClearFontSize_.y);
	*/

#pragma endregion
#endif // _DEBUG
}

void StageClear::Reset() {
	length_ = minLength_;
	MoveStarT_ = 0;
	MoveStarAddT_ = 0;

};