#include"Pause.h"


void Pause::Draw() {
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
		if (isPause_ ||
			isStartPause_ ||
			isEndPause_) {
			Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, BCColor_, kFillModeSolid);

			Novice::DrawBox(int(pauseFontPos_.x - pauseFontSize_.x / 2), int(pauseFontPos_.y - pauseFontSize_.y / 2),
				int(pauseFontSize_.x), int(pauseFontSize_.y), 0.0f, elseColor_, kFillModeWireFrame);
			for (int i = 0; i < 3; i++) {
				Novice::DrawBox(int(buttonPos_[i].x - buttonSize_[i].x / 2), int(buttonPos_[i].y - buttonSize_[i].y / 2),
					int(buttonSize_[i].x), int(buttonSize_[i].y), 0.0f, buttonColor_[i], kFillModeWireFrame);
			}


			DrawCat(catPos_, catSize_.x, catSize_.y, 0xFFFFFFFF);
			Novice::DrawLine(int(lineStart_.x), int(lineStart_.y), int(lineEnd_.x), int(lineEnd_.y), elseColor_);
		}
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}
void Pause::Update(ChangeScene cs, char* keys, char* preKeys) {
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

		/*ESCAPEキーでPAUSEのONOFFを可能にする*/
		if (!preKeys[DIK_ESCAPE] && keys[DIK_ESCAPE]) {
			if (!cs.isStartChange_ && !cs.isEndChange_) {

				if (!isPause_) {
					isStartPause_ = true;
					selectNum_ = 0;
				} else {
					isEndPause_ = true;
				}

			}
		}

#pragma region"ポーズ画面開始終了の処理"
		/*ポーズ開始終了の処理*/
		if (isStartPause_ ||
			isEndPause_) {
			//足す透明度をイージング
			BCT_ += (1.0f / BCEaseTimer_) * BCEaseDir_;
			BCAddT_ = EaseInOutCubic(BCT_);

			addBCColor_ = (1 - BCAddT_) * minColor_ + BCAddT_ * maxBCColor_;
			addElseColor_ = (1 - BCAddT_) * minColor_ + BCAddT_ * maxElseColor_;
			//イージング
			theta_ = (1 - BCAddT_) * minTheta_ + BCAddT_ * maxTheta_;

			if (BCT_ >= 1.0f) {
				BCT_ = 1.0f;
				isStartPause_ = false;
				isEndPause_ = false;
				isPause_ = true;
				BCEaseDir_ *= -1;
				theta_ = maxTheta_;
			}
			if (BCT_ <= 0.0f) {
				BCT_ = 0.0f;
				isStartPause_ = false;
				isEndPause_ = false;
				isPause_ = false;
				BCEaseDir_ *= -1;
				theta_ = minTheta_;
			}
			if (addBCColor_ >= 0xFD) {
				addBCColor_ = 0xFD;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			if (addBCColor_ <= 0x10) {
				addBCColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}

			if (addElseColor_ >= 0xFF) {
				addElseColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			if (addElseColor_ <= 0x10) {
				addElseColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}

			BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す
			elseColor_ = 0xFFFFFF00 + int(addElseColor_);//ここで透明度を足す
			selectColor_ = 0xFFFFFF00 + int(addElseColor_);//ここで透明度を足す
			for (int i = 0; i < 3; i++) {
				buttonColor_[i] = 0xFFFFFF00 + int(addElseColor_);//ここで透明度を足す
			}
		}
#pragma endregion


		//猫の回転軌道の処理
		rotateLength_ = rotateVect(length_, sinf(theta_), cosf(theta_));
		catPos_ = getVectAdd(rotateLength_, originPos_);
		//指定したボタンが大きくなり光る
		for (int i = 0; i < 3; i++) {
			buttonColor_[i] = 0x66666600 + int(addElseColor_);
			buttonSize_[i] = { 265,75 };
		}
		buttonColor_[selectNum_] = 0xFFFFFF00 + int(addElseColor_);
		buttonSize_[selectNum_] = { 300,100 };


		//PAUSE画面の時
		if (isPause_) {

			//選択範囲の移動
			if (!preKeys[DIK_W] && keys[DIK_W] ||
				keys[DIK_UP] && !preKeys[DIK_UP]) {
				selectNum_--;
			}
			if (!preKeys[DIK_S] && keys[DIK_S] ||
				keys[DIK_DOWN] && !preKeys[DIK_DOWN]) {
				selectNum_++;
			}

			//clamp
			if (selectNum_ == 3) {
				selectNum_ = 0;
			}
			if (selectNum_ == -1) {
				selectNum_ = 2;
			}

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] ||
				keys[DIK_RETURN] && !preKeys[DIK_RETURN] &&
				!isSelect_) {
				isSelect_ = true;
			}


			//選択した時の処理
			if (isSelect_) {
				switch (selectNum_)
				{
				case 0://セレクト画面へ戻る
					break;
				case 1://ステージヲリセット
					cs.isEndChange_;
					break;

				case 2://ゲーム画面へ戻る
					isEndPause_ = true;
					isSelect_ = false;
					break;

				default:
					break;
				}

			}

		}

		//Debug(keys, preKeys);





		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}





/*
void Pause::Debug(char* keys, char* preKeys) {

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


	for (int i = 0; i < 3; i++) {
		buttonPos_[i] = { float(Global::windowSize_.x) / 2,(BSpace_ * i + BOffset_) };
		//全体の色
		Color_[i] = 0x666666FF;//灰色
	}

	switch (debugNum)
	{
	case 0:
		if (keys[DIK_W]) {
			pauseFontPos_.y -= 1;
		}
		if (keys[DIK_S]) {
			pauseFontPos_.y += 1;
		}
		if (keys[DIK_A]) {
			pauseFontPos_.x -= 1;
		}
		if (keys[DIK_D]) {
			pauseFontPos_.x += 1;
		}
		break;

	case 1:
		if (keys[DIK_W]) {
			pauseFontSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			pauseFontSize_.y += 1;
		}
		if (keys[DIK_A]) {
			pauseFontSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			pauseFontSize_.x += 1;
		}
		break;

	case 2:
		if (keys[DIK_W]) {
			BSpace_ -= 1;
		}
		if (keys[DIK_S]) {
			BSpace_ += 1;
		}

		break;
	case 3:
		if (keys[DIK_W]) {
			buttonSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			buttonSize_.y += 1;
		}
		if (keys[DIK_A]) {
			buttonSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			buttonSize_.x += 1;
		}
		break;


	default:
		break;
	}

	Novice::ScreenPrintf(0, 20, "debugNum=%d", debugNum);
	Novice::ScreenPrintf(0, 40, "pauseFontPos_ x=%f,y=%f", pauseFontPos_.x, pauseFontPos_.y);
	Novice::ScreenPrintf(0, 60, " pauseFontSize_ x=%f,y=%f", pauseFontSize_.x, pauseFontSize_.y);
	Novice::ScreenPrintf(0, 80, "BSpace_=%f", BSpace_);
	Novice::ScreenPrintf(0, 100, "buttonSize_x = %f, y = %f", buttonSize_.x, buttonSize_.y);


#pragma endregion

}
*/