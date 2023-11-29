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
				starSize_ = (1 - MoveStarAddT_) * minSize_ + MoveStarAddT_ * maxSize_;
				if (MoveStarT_ >= 1.0f) {
					MoveStarT_ = 1.0f;
					canSceneChange = true;
				}
			}
		}



#pragma region"CLEARと文字押せを出現させる"
		if (!isStartScene) {
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



void StageClear::Draw(Resources rs) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================

		//Novice::DrawBox(int(TitlefontPos_.x - TitlefontSize_.x / 2), int(TitlefontPos_.y - TitlefontSize_.y / 2), int(TitlefontSize_.x), int(TitlefontSize_.y), 0.0f, 0xFFFFFFFF, kFillModeWireFrame);

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
		Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, 0x666666FF, kFillModeSolid);

		Novice::DrawBox(int(Global::windowSize_.x / 2 - 250), int(Global::windowSize_.y / 2 - 50 - 250), 500, 500, 0.0f, windowColor_, kFillModeSolid);
		Novice::DrawBox(int(Global::windowSize_.x / 2 - 200), int(Global::windowSize_.y / 2 - 50 - 200), 400, 400, 0.0f, skyColor_, kFillModeSolid);
		//Novice::DrawSprite(int(Global::windowSize_.x / 2 - 200), int(Global::windowSize_.y / 2 - 50 - 200), rs.WindowGH_, 2, 2, 0, 0xFFFFFFFF);


		/*左のドア*/
		Novice::DrawQuad(
			30, 105, 105, 170,
			30, 510, 105, 475,

			0, 0, 1, 1, rs.whiteGH_, windowColor_
		);
		Novice::DrawQuad(
			40, 140, 85, 175,
			40, 305, 85, 292,
			0, 0, 1, 1, rs.whiteGH_, skyColor_
		);
		Novice::DrawQuad(
			40, 340, 85, 325,
			40, 472, 85, 450,
			0, 0, 1, 1, rs.whiteGH_, skyColor_
		);

		/*右のドア*/
		Novice::DrawQuad(
			375, 170, 450, 105,
			375, 475, 450, 510,
			0, 0, 1, 1, rs.whiteGH_, windowColor_
		);
		Novice::DrawQuad(
			395, 175, 440, 140,
			395, 292, 440, 305,
			0, 0, 1, 1, rs.whiteGH_, skyColor_
		);
		Novice::DrawQuad(
			395, 325, 440, 340,
			395, 450, 440, 472,
			0, 0, 1, 1, rs.whiteGH_, skyColor_
		);


		Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, 0x00000099, kFillModeSolid);

		/*星*/
		for (int i = 0; i < starGet_; i++) {
			My::DrawStar(starPos_[i], starSize_, 0.0f, starColor_);
		}
		/*ゲットできなかった星（ワイヤーフレームにする）*/
		for (int i = starGet_; i < 3; i++) {
			My::DrawStarWire(starPos_[i], starSize_, 0.0f, 0x444444FF);
		}


		if (starGet_ >= 2) {
			Novice::DrawLine(int(starPos_[0].x), int(starPos_[0].y), int(starPos_[1].x), int(starPos_[1].y), starColor_);
			if (starGet_ >= 3) {
				Novice::DrawLine(int(starPos_[0].x), int(starPos_[0].y), int(starPos_[2].x), int(starPos_[2].y), starColor_);
				Novice::DrawLine(int(starPos_[1].x), int(starPos_[1].y), int(starPos_[2].x), int(starPos_[2].y), starColor_);
			}
		}



		/*ステージクリアの文字*/
		Novice::DrawSprite(int(StageClearFontCPos_.x - StageClearFontSize_.x / 2), int(StageClearFontCPos_.y - StageClearFontSize_.y / 2), rs.stageClearFontGH_, 1, 1, 0.0f, FColor_);


		/*猫*/
		DrawCat(
			{
			CatCPos_.x,
			(CatCPos_.y + 4.0f) - fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI)))
			},
			(CatSize_.x + 4.0f) - fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))),
			(CatSize_.y - 4.0f) + fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))),
			0x000000FF
		);

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
	switch (Scene::sceneNum_) {

	case TITLE:

#if _DEBUG
#pragma region"デバック用"

		if (keys[DIK_R] && !preKeys[DIK_R]) {
			length_ = minLength_;
			MoveStarT_ = 0;
			MoveStarAddT_ = 0;

		}

		//操作したい番号選択
		if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
			debugNum += 1;
			//[1]=originPos_
			//[2]=size_
			//[3]=length_
			if (debugNum == 4) {
				debugNum = 0;
			}
		}

		switch (debugNum) {
		case 0:
			/*
			if (keys[DIK_W]) {
				TitlefontPos_.y -= 1;
			}
			if (keys[DIK_S]) {
				TitlefontPos_.y += 1;
			}
			if (keys[DIK_A]) {
				TitlefontPos_.x -= 1;
			}
			if (keys[DIK_D]) {
				TitlefontPos_.x += 1;
			}
			*/
			break;

		case 1:
			/*
			if (keys[DIK_W]) {
				TitlefontSize_.y -= 1;
			}
			if (keys[DIK_S]) {
				TitlefontSize_.y += 1;
			}
			if (keys[DIK_A]) {
				TitlefontSize_.x -= 1;
			}
			if (keys[DIK_D]) {
				TitlefontSize_.x += 1;
			}
			*/
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
				CatCPos_.y -= 1;
			}
			if (keys[DIK_S]) {
				CatCPos_.y += 1;
			}
			if (keys[DIK_A]) {
				CatCPos_.x -= 1;
			}
			if (keys[DIK_D]) {
				CatCPos_.x += 1;
			}
			break;


		default:
			break;
		}

		//		Novice::ScreenPrintf(0, 20, "debugNum=%d", debugNum);
		//Novice::ScreenPrintf(0, 40, "titleFont x=%f,y=%f", TitlefontPos_.x, TitlefontPos_.y);
		//Novice::ScreenPrintf(0, 60, "size x=%f,y=%f", TitlefontSize_.x, TitlefontSize_.y);
		//		Novice::ScreenPrintf(0, 80, "StageClearFontCPos_ x=%f,y=%f", StageClearFontCPos_.x, StageClearFontCPos_.y);
		//		Novice::ScreenPrintf(0, 100, "StageClearFontSize_x = %f, y = %f", CatCPos_.x, CatCPos_.y);


#pragma endregion
#endif // _DEBUG
		break;
}

}

void StageClear::Reset() {

	starGet_ = 0;
	starSize_ = 1;//32


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
};