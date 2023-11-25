#include"Pause.h"


void Pause::Draw(Resources rs) {
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

		if (isPause_ || isStartPause_ || isEndPause_) {
			Novice::DrawBox(0, 0, int(Global::windowSize_.x), int(Global::windowSize_.y), 0.0f, BCColor_, kFillModeSolid);

			//Novice::DrawBox(int(pauseFontPos_.x - pauseFontSize_.x / 2), int(pauseFontPos_.y - pauseFontSize_.y / 2),
			//	int(pauseFontSize_.x), int(pauseFontSize_.y), 0.0f, elseColor_, kFillModeWireFrame);
			Novice::DrawSprite(int(pauseFontPos_.x - pauseFontSize_.x / 2), int(pauseFontPos_.y - pauseFontSize_.y / 2),
				rs.pauseGH_, 1.0f, 1.0f, 0.0f, elseColor_);



			for (int i = 0; i < 3; i++) {
				//Novice::DrawBox(int(buttonPos_[i].x - buttonSize_[i].x / 2), int(buttonPos_[i].y - buttonSize_[i].y / 2),
					//int(buttonSize_[i].x), int(buttonSize_[i].y), 0.0f, buttonColor_[i], kFillModeWireFrame);

				Novice::DrawSpriteRect(int(buttonPos_[i].x - buttonSize_[i].x / 2), int(buttonPos_[i].y - buttonSize_[i].y / 2),
					int(buttonDrawSize_[i].x * i), 0,
					int(buttonDrawSize_[i].x), int(buttonDrawSize_[i].y), rs.pauseMenuGH_, 0.33f * buttonDrawScale_[i].x, 1.0f * buttonDrawScale_[i].y, 0.0f, buttonColor_[i]);

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
void Pause::Update(ChangeScene& cs, char* keys, char* preKeys) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================

		if (!cs.isEndChange_ && !cs.isStartChange_) {
			Reset();
		}

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================
#pragma region"ESCAPEキーでポーズ切り替え"

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
#pragma endregion

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

#pragma region"猫の移動処理&&指定したボタンの色サイズ処理"
		if (isPause_ || isStartPause_ || isEndPause_) {
			//猫の回転軌道の処理
			rotateLength_ = rotateVect(length_, sinf(theta_), cosf(theta_));
			catPos_ = getVectAdd(rotateLength_, originPos_);
			//指定したボタンが大きくなり光る
			for (int i = 0; i < 3; i++) {
				buttonColor_[i] = 0x66666600 + int(addElseColor_);
				buttonSize_[i] = { 265,75 };
				buttonDrawScale_[i] = { 1.0f,1.0f };
			}
			buttonColor_[selectNum_] = 0xFFFFFF00 + int(addElseColor_);
			buttonSize_[selectNum_] = { 318,90 };
			buttonDrawScale_[selectNum_] = { 1.2f,1.2f };//{ 1.134f,1.34f };
		}
#pragma endregion

#pragma region"ポーズ画面の選択処理"
		//PAUSE画面の時
		if (isPause_) {
			if (!isSelect_) {//選択されていない時

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
				//SPACEキーで選択できる
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					isSelect_ = true;
				}
			}


			//選択した時の処理
			if (isSelect_) {
				switch (selectNum_) {
				case 0://セレクト画面へ戻る
					if (!cs.isStartChange_ && !cs.isEndChange_) {//クリア画面で全ての処理が終わったとき
						cs.isEndChange_ = true;
					}
					break;
				case 1://ステージをリセット
					if (isStageReset_) {
						isStageReset_ = false;
					}
					isStageReset_ = true;
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
#pragma endregion

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================


		if (!cs.isEndChange_ && !cs.isStartChange_) {
			Reset();
		}
		break;

	default:
		break;
	}
}





void Pause::Reset() {
#pragma region"リセット"
	//PAUSEの文字
	pauseFontSize_ = { 265,75 };
	pauseFontPos_ = { 345 ,60 };

	//選択する場所
	BOffset_ = 200;
	BSpace_ = 150;

	for (int i = 0; i < 3; i++) {
		buttonSize_[i] = { 265,75 };
		buttonDrawSize_[i] = { 265,75 };
		buttonDrawScale_[i] = { 1.0f,1.0f };
		buttonPos_[i] = { float(Global::windowSize_.x) / 2,(BSpace_ * i + BOffset_) };
		//全体の色
		buttonColor_[i] = 0x66666600;//灰色
	}


	//選択された範囲
	selectNum_ = 0;//選択する番号
	selectColor_ = 0xFFFFFF00;//選択したところの色（白）


	isSelect_ = false;//選択するフラグ

	/*装飾*/

	//地面
	lineStart_ = { 0,650 };
	lineEnd_ = { float(Global::windowSize_.x),650 };

	//猫
	catSize_ = { 100,100 };
	catPos_ = { -catSize_.x,lineStart_.y - catSize_.y / 2 };
	catDir_ = 1;
	theta_ = 0.0f;
	originPos_ = { -catSize_.x,lineStart_.y - catSize_.y / 2 };//{640,1490}
	length_ = { 200,0 };//{1150,0}
	rotateLength_ = { 0 };
	maxTheta_ = 0;
	minTheta_ = (float(-M_PI));

	BCT_ = 0;
	BCAddT_ = 0;
	BCEaseTimer_ = 30;
	BCEaseDir_ = 1;

	minColor_ = 0x0;
	maxBCColor_ = 0xFD;
	addBCColor_ = minColor_;

	maxElseColor_ = 0xFF;
	addElseColor_ = minColor_;

	BCColor_ = 0x00000000;
	elseColor_ = 0xFFFFFF00;

	isPause_ = false;//PAUSE画面か否か
	isStartPause_ = false;//PAUSE画面か否か
	isEndPause_ = false;//PAUSE画面か否か
	isStageReset_ = false;
#pragma endregion

};