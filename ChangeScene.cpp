#include "ChangeScene.h"

void ChangeScene::UpDate(bool& isChangeScene, Vec2 CPos[], int selectNum) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;

		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================

#pragma region"ステージ画面の終了処理(ステージからゲーム画面)"

		/*-------------------------------シーンチェンジフラグが立つと開始--------------------------------*/


#pragma region"シーンチェンジで開始"


		if (isChangeScene && !isStartChange_) {
			isStartChange_ = true;
			isSetSCPos_ = true;
			isChangeColor_ = true;
		}
#pragma endregion


		/*--------------------------------状態遷移用の扉を設置-----------------------------------------*/

		if (isStartChange_ && !isEndChange_) {
#pragma region"設置"


			//選択した扉の位置を状態遷移用の扉の座標に代入する
			if (isSetSCPos_) {
				SCCPos_ = CPos[selectNum];
				minSCSize_ = SCSize_;
				maxSCSize_ = { 480,960 };//元300,600//画面全体覆うサイズに変更
				minSCCPos_ = SCCPos_;
				maxSCCPos_ = { 240,360 };
				isSetSCPos_ = false;
			}
#pragma endregion


			/*-------------------------------------暗幕のイージング----------------------------------------*/


#pragma region"暗幕を下げる"


	//足す透明度をイージング
			if (isChangeColor_) {
				BCT_ += (1.0f / BCEaseTimer_) * BCEaseDir_;
				BCAddT_ = EaseInOutBounce(BCT_);
				addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
				if (BCT_ >= 1.0f) {
					BCT_ = 1.0f;
					isEaseSC_ = true;//状態遷移用の扉を中心へもっていくフラグを立てる（sceneChange）
					if (!isEaseO_) {
						isChangeColor_ = false;//暗幕の透明度を変化させるフラグを下す
					}
					BCEaseDir_ *= -1;
					//for (int i = 0; i < 8; i++) {
					//	isDraw_[i] = false;//描画されている他の扉を消す//扉の上のレイヤーに暗幕を下すので必要ないかも
					//}
				}
				if (BCT_ <= 0.0f) {
					BCT_ = 0.0f;
					isChangeColor_ = false;//暗幕の透明度を変化させるフラグを下す
					isEaseO_ = false;
					BCEaseDir_ *= -1;
				}


				if (addBCColor_ >= 0xFF) {
					addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addBCColor_ <= 0x10) {
					addBCColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}

				BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す
				SCColor_ = 0xFFFFFF00 + int(addBCColor_);//ここで透明度を足す
			}
#pragma endregion


			/*-------------------------態遷移用扉を中央に持っていくイージング--------------------------------*/


#pragma region"扉を中央に持っていく"
		//座標と大きさをイージング
			if (isEaseSC_) {
				SCT_ += (1 / SCEaseTimer_);
				SCAddT_ = EaseInOutCubic(SCT_);
				SCCPos_.x = (1 - SCAddT_) * minSCCPos_.x + SCAddT_ * maxSCCPos_.x;
				SCCPos_.y = (1 - SCAddT_) * minSCCPos_.y + SCAddT_ * maxSCCPos_.y;

				SCSize_.x = (1 - SCAddT_) * minSCSize_.x + SCAddT_ * maxSCSize_.x;
				SCSize_.y = (1 - SCAddT_) * minSCSize_.y + SCAddT_ * maxSCSize_.y;


				if (SCT_ >= 0.3f) {
					isSetVertexO_ = true;//扉を開けるイージングで使う変数の値を入れる
					isEaseO_ = true;//扉を空けるフラグを立てる（Open）
				}


				if (SCT_ >= 1) {
					SCT_ = 1;

					isEaseSC_ = false;////状態遷移用の扉を中心へもっていくフラグを下す（SceneChange）
					isSetVertexO_ = false;//フラグを下す
				}
			}

			VectorVertexS(SCVertex_, SCCPos_, SCSize_.x, SCSize_.y);//ここで描画用の頂点を求める

			//状態遷移用の扉を開く先の座標を指定する
			if (isSetVertexO_) {
				//posSet
				minVertexO_[0] = SCVertex_[0];
				minVertexO_[1] = SCVertex_[2];
				maxVertexO_[0] = { SCVertex_[1].x + SCSize_.x / 4,SCVertex_[0].y + SCSize_.y / 4 };
				maxVertexO_[1] = { SCVertex_[3].x + SCSize_.x / 4,SCVertex_[3].y + SCSize_.y / 4 };

			}
#pragma endregion


			/*--------------------------------状態遷移用扉を開くイージング---------------------------------*/


#pragma region"各扉の開く演出"
			if (isEaseO_) {

				openT_ += 0.01f * easeDirO_;
				if (easeDirO_ > 0) {
					openAddT_ = EaseInOutCubic(openT_);
				} else {
					openAddT_ = EaseInBounce(openT_);
				}


				if (openT_ <= 0) {
					openT_ = 0.0f;
					easeDirO_ *= -1;
				}
				if (openT_ >= 1.0f) {
					openT_ = 1.0f;
					easeDirO_ = 0;
					isChangeColor_ = true;
					isStartChange_ = false;
					isEndChange_ = true;
					Scene::sceneNum_ = GAME;
				}
				//左上頂点
				SCVertex_[0].x = (1 - openAddT_) * minVertexO_[0].x + openAddT_ * maxVertexO_[0].x;
				SCVertex_[0].y = (1 - openAddT_) * minVertexO_[0].y + openAddT_ * maxVertexO_[0].y;
				//左下頂点
				SCVertex_[2].x = (1 - openAddT_) * minVertexO_[1].x + openAddT_ * maxVertexO_[1].x;
				SCVertex_[2].y = (1 - openAddT_) * minVertexO_[1].y + openAddT_ * maxVertexO_[1].y;
			}

#pragma endregion

		}
#pragma endregion

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

#pragma region"ゲーム本編の開始処理（ステージからゲーム画面）"


#pragma region"暗幕を上げる"

		if (isEndChange_ && !isStartChange_) {
			//足す透明度をイージング
			if (isChangeColor_) {
				BCT_ += (1.0f / BCEaseTimer_) * BCEaseDir_;
				//BCAddT_ = EaseInOutBounce(BCT_);
				if (BCEaseDir_ > 0) {
					BCAddT_ = EaseInBounce(BCT_);
				} else {
					BCAddT_ = EaseInOutCubic(BCT_);
				}

				addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
				if (BCT_ >= 1.0f) {
					BCT_ = 1.0f;
					isEaseSC_ = true;//状態遷移用の扉を中心へもっていくフラグを立てる（sceneChange）
					if (!isEaseO_) {
						isChangeColor_ = false;//暗幕の透明度を変化させるフラグを下す
					}
					BCEaseDir_ *= -1;
					//for (int i = 0; i < 8; i++) {
					//	isDraw_[i] = false;//描画されている他の扉を消す//扉の上のレイヤーに暗幕を下すので必要ないかも
					//}
				}
				if (BCT_ <= 0.0f) {
					BCT_ = 0.0f;
					isChangeColor_ = false;//暗幕の透明度を変化させるフラグを下す
					isChangeScene = false;
					isEndChange_ = false;
					isEaseO_ = false;
					BCEaseDir_ *= -1;
				}


				if (addBCColor_ >= 0xFF) {
					addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addBCColor_ <= 0x10) {
					addBCColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}

				BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す
				SCColor_ = 0xFFFFFF00 + int(addBCColor_);//ここで透明度を足す
			}
		}

#pragma endregion


#pragma endregion

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;

	}
}

void  ChangeScene::Draw(int GH, unsigned int DoorColor) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;

		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================

#pragma region"ステージ選択の描画"


				/*------------------------------状態遷移時の暗幕----------------------------------------*/
		Novice::DrawBox(0, 0, 480, 720, 0.0f, BCColor_, kFillModeSolid);



		/*------------------------------状態遷移用の扉----------------------------------------*/

		//扉の欄間から見える光
		Novice::DrawBox(static_cast<int>(SCCPos_.x - SCSize_.x / 2), static_cast<int>(SCCPos_.y - SCSize_.y / 2),
			static_cast<int>(SCSize_.x), static_cast<int>(SCSize_.y), 0.0f, SCColor_, kFillModeSolid);

		//ドア本体
		Novice::DrawQuad(static_cast<int>(SCVertex_[0].x), static_cast<int>(SCVertex_[0].y), static_cast<int>(SCVertex_[1].x), static_cast<int>(SCVertex_[1].y),
			static_cast<int>(SCVertex_[2].x), static_cast<int>(SCVertex_[2].y), static_cast<int>(SCVertex_[3].x), static_cast<int>(SCVertex_[3].y),
			0, 0, 100, 200, GH, DoorColor);

#pragma endregion

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

#pragma region"ゲーム本編の描画"


		/*------------------------------状態遷移時の暗幕----------------------------------------*/
		Novice::DrawBox(0, 0, 480, 720, 0.0f, BCColor_, kFillModeSolid);



		/*------------------------------状態遷移用の扉----------------------------------------*/

		//扉の欄間から見える光
		Novice::DrawBox(static_cast<int>(SCCPos_.x - SCSize_.x / 2), static_cast<int>(SCCPos_.y - SCSize_.y / 2),
			static_cast<int>(SCSize_.x), static_cast<int>(SCSize_.y), 0.0f, SCColor_, kFillModeSolid);

		//ドア本体
		Novice::DrawQuad(static_cast<int>(SCVertex_[0].x), static_cast<int>(SCVertex_[0].y), static_cast<int>(SCVertex_[1].x), static_cast<int>(SCVertex_[1].y),
			static_cast<int>(SCVertex_[2].x), static_cast<int>(SCVertex_[2].y), static_cast<int>(SCVertex_[3].x), static_cast<int>(SCVertex_[3].y),
			0, 0, 100, 200, GH, DoorColor);
#pragma endregion

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}



void ChangeScene::Reset(bool& isChangeScene) {
#pragma region"リセット"
	if (!isChangeScene) {

		//isChangeSelect_ = false;

		//状態遷移イージング用
		SCCPos_ = { -200,-100 };
		SCSize_ = { 50,100 };
		for (int i = 0; i < 4; i++) {
			SCVertex_[i] = { 0 };
		}
		SCT_ = 0;
		SCAddT_ = 0;
		SCColor_ = 0xFFFFFF00;
		minSCSize_ = { 0 };
		maxSCSize_ = { 0 };
		minSCCPos_ = { 0 };
		maxSCCPos_ = { 0 };
		SCEaseTimer_ = 120;
		isSetSCPos_ = false;
		isEaseSC_ = false;

		//ドアを開くイージング用
		openT_ = 0;
		openAddT_ = 0;
		easeDirO_ = 1;
		for (int j = 0; j < 2; j++) {
			minVertexO_[j] = { 0,0 };
			maxVertexO_[j] = { 0,0 };
		}
		isEaseO_ = false;
		isSetVertexO_ = false;

		//暗幕変数(blackoutCurtainと呼称	BC)
		BCT_ = 0;
		BCAddT_ = 0;
		BCEaseTimer_ = 51;
		BCEaseDir_ = 1;
		maxBCColor_ = 0xff;
		minBCColor_ = 0x0;
		addBCColor_ = 0x0;
		isChangeColor_ = false;
		BCColor_ = 0xFFFFFF00;
	}
#pragma endregion
}