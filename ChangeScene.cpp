#include "ChangeScene.h"

void ChangeScene::UpDate(char* keys, char* preKeys, bool& isChangeScene, Vec2 CPos[],
	int selectNum, bool& CanCS, Vec2 goalPos, Vec2 goalSize, bool& isPauseSelect, bool& isTitlePush, bool& stageReset,const Resources &rs,int& selectLightSEHandle,
	int BGMHandle_[3],float soundVolume_[3],bool &isEaseM) {
	
	preIsStartChange_ = isStartChange_;
	preIsEndChange_ = isEndChange_;

	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		Reset();
#pragma region"セレクトからタイトル（開始処理)"

		//足す透明度をイージング
		if (isStartChange_) {
			BCT_ += (1.0f / BCEaseTimer_) * BCEaseDir_;
			BCAddT_ = EaseInOutBounce(BCT_);
			addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
			soundVolume_[2] = (1 - BCAddT_) * 0.06f + BCAddT_ * 0;
			Novice::SetAudioVolume(BGMHandle_[2], soundVolume_[2]);

			if (BCT_ <= 0.0f) {
				BCT_ = 0.0f;
				soundVolume_[2] = 0.06f;
				isStartChange_ = false;//暗幕の透明度を変化させるフラグを下す
				isChangeScene = false;
			}

			if (addBCColor_ >= 0xFF) {
				addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			if (addBCColor_ <= 0x10) {
				addBCColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す
		}

#pragma endregion



#pragma region"タイトルからセレクトへの状態遷移"


		if (isTitlePush) {
			isEndChange_ = true;
		}
		//足す透明度をイージング
		if (!isStartChange_ && isEndChange_) {
			BCT_ += (1.0f / (BCEaseTimer_ / 1.0f)) * BCEaseDir_;
			BCAddT_ = EaseInCubic(BCT_);
			addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
			soundVolume_[2] = (1 - BCAddT_) * 0.06f + BCAddT_ * 0;
			Novice::SetAudioVolume(BGMHandle_[2], soundVolume_[2]);
			if (BCT_ >= 1.0f) {
				BCT_ = 1.0f;
				BCWaitTimer_ -= 1;
				if (BCWaitTimer_ == 0) {
					isEndChange_ = false;//暗幕の透明度を変化させるフラグを下す
					isStartChange_ = true;//暗幕の透明度を変化させるフラグを下す
					isTitlePush = false;
					Novice::StopAudio(BGMHandle_[2]);
					BCEaseDir_ *= -1;
					Scene::sceneNum_ = SELECT;
				}
			}
			if (addBCColor_ >= 0xFF) {
				addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す

		}

#pragma endregion


		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		Reset();
#pragma region"ステージ選択の開始処理（クリアからセレクト||ゲームポーズ画面からセレクト）"

		//足す透明度をイージング
		if (isStartChange_) {
			BCT_ += (1.0f / BCEaseTimer_) * BCEaseDir_;
			BCAddT_ = EaseInOutBounce(BCT_);
			addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
			soundVolume_[0] = (1 - BCAddT_) * 0.12f + BCAddT_ * 0;
			Novice::SetAudioVolume(BGMHandle_[0], soundVolume_[0]);

			if (BCT_ <= 0.0f) {
				BCT_ = 0.0f;

				isStartChange_ = false;//暗幕の透明度を変化させるフラグを下す
			}

			if (addBCColor_ >= 0xFF) {
				addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			if (addBCColor_ <= 0x10) {
				addBCColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す
		}


#pragma endregion

#pragma region"ステージ画面の終了処理(ステージからゲーム画面||ステージからタイトル画面)"

		/*-------------------------------シーンチェンジフラグが立つと開始--------------------------------*/

#pragma region"シーンチェンジで開始"

		if (Global::controlMode_ == 0) {
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] ||
				keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				if (!isPushEscape_) {//ESCAPE押されていないとき
					if (!isChangeScene && !isEndChange_ && !isStartChange_) {
						isChangeScene = true;
						isEndChange_ = true;
						isSetSCPos_ = true;
						isChangeColor_ = true;
						pushSEHandle_ = Novice::PlayAudio(rs.selectPushSE_, 0, 0.5f);
						Novice::StopAudio(selectLightSEHandle);
					}
				}
			}
		} else {
			if (Novice::IsTriggerButton(0, kPadButton10) or
				Novice::IsTriggerButton(0, kPadButton11)) {
				if (!isPushEscape_) {//ESCAPE押されていないとき
					if (!isChangeScene && !isEndChange_ && !isStartChange_) {
						isChangeScene = true;
						isEndChange_ = true;
						isSetSCPos_ = true;
						isChangeColor_ = true;
						pushSEHandle_ = Novice::PlayAudio(rs.selectPushSE_, 0, 0.5f);
						Novice::StopAudio(selectLightSEHandle);
					}
				}
			}

		}

		if (Global::controlMode_ == 0) {
			if (keys[DIK_ESCAPE] && !preKeys[DIK_ESCAPE]) {
				if (!isPushEscape_) {//ESCAPE押されていないとき
					if (!isChangeScene && !isEndChange_ && !isStartChange_) {
						isChangeScene = true;
						isEndChange_ = true;
						isPushEscape_ = true;
						Novice::StopAudio(selectLightSEHandle);
					}
				}
			}
		} else {
			if (Novice::IsTriggerButton(0,kPadButton4) or Novice::IsTriggerButton(0, kPadButton5)) {
				if (!isPushEscape_) {//ESCAPE押されていないとき
					if (!isChangeScene && !isEndChange_ && !isStartChange_) {
						isChangeScene = true;
						isEndChange_ = true;
						isPushEscape_ = true;
						Novice::StopAudio(selectLightSEHandle);
					}
				}
			}

		}




#pragma endregion
		if (isEndChange_) {


			//タイトルに戻る処理
			if (isPushEscape_) {
				//足す透明度をイージング
				if (!isStartChange_ && isEndChange_) {
					BCT_ += (1.0f / (BCEaseTimer_ / 1.0f)) * BCEaseDir_;
					BCAddT_ = EaseInCubic(BCT_);
					addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
					soundVolume_[0] = (1 - BCAddT_) * 0.12f + BCAddT_ * 0;
					Novice::SetAudioVolume(BGMHandle_[0], soundVolume_[0]);
					if (BCT_ >= 1.0f) {
						BCT_ = 1.0f;
						BCWaitTimer_ -= 1;
						if (BCWaitTimer_ == 0) {
							isEndChange_ = false;//暗幕の透明度を変化させるフラグを下す
							isStartChange_ = true;//暗幕の透明度を変化させるフラグを下す
							BCEaseDir_ *= -1;
							isPushEscape_ = false;
							Scene::sceneNum_ = TITLE;
						}
					}
					if (addBCColor_ >= 0xFF) {
						addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
					}
					BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す

				}




			} else {//ESCAPE押されていないとき

				/*--------------------------------状態遷移用の扉を設置-----------------------------------------*/

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

						if (!Novice::IsPlayingAudio(openDoorSEHandle_) || openDoorSEHandle_ == -1) {
							if (SECount_ == 0) {
								openDoorSEHandle_ = Novice::PlayAudio(rs.openDoorSE_, 0, 0.12f);
								SECount_++;
							}
						}
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
						isEndChange_ = false;
						isStartChange_ = true;
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
		}
#pragma endregion

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

		Reset();

#pragma region"ゲーム本編の開始処理（ステージからゲーム画面とステージリセット）"


#pragma region"暗幕を上げる"

		if (!isEndChange_ && isStartChange_) {
			if (!stageReset) {
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

					}
					if (BCT_ <= 0.0f) {
						BCT_ = 0.0f;
						isChangeColor_ = false;//暗幕の透明度を変化させるフラグを下す
						isChangeScene = false;
						isStartChange_ = false;
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
			} else {
				//足す透明度をイージング
				BCT_ += (1.0f / BCEaseTimer_) * BCEaseDir_;
				BCAddT_ = EaseInOutBounce(BCT_);
				addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
				soundVolume_[0] = (1 - BCAddT_) * 0.12f + BCAddT_ * 0;
				Novice::SetAudioVolume(BGMHandle_[0], soundVolume_[0]);
				if (BCT_ <= 0.0f) {
					BCT_ = 0.0f;
					isStartChange_ = false;//暗幕の透明度を変化させるフラグを下す
					stageReset = false;
				}

				if (addBCColor_ >= 0xFF) {
					addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addBCColor_ <= 0x10) {
					addBCColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す

			}
		}


#pragma endregion


#pragma endregion

#pragma region"ゲーム本編!(開始&&終了)"
		if (!isStartChange_ && !isEndChange_) {

			//ゴールのドアの位置
			VectorVertexS(GCVertex_, goalPos, goalSize.x, goalSize.y);
			minVertexGO_[0] = GCVertex_[0];
			minVertexGO_[1] = GCVertex_[2];
			maxVertexGO_[0] = { GCVertex_[1].x + goalSize.x / 4,GCVertex_[0].y + goalSize.y / 4 };
			maxVertexGO_[1] = { GCVertex_[3].x + goalSize.x / 4,GCVertex_[3].y + goalSize.y / 4 };


		}




#pragma endregion

#pragma region"ゲーム本編の終了処理"
		if (isPauseSelect) {
#pragma region"ゲームポーズ画面からセレクト画面へ"

			//足す透明度をイージング
			if (isEndChange_) {
				BCT_ += (1.0f / (BCEaseTimer_ / 2.0f)) * BCEaseDir_;
				BCAddT_ = EaseInCubic(BCT_);
				addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;

				if (BCT_ >= 1.0f) {
					BCT_ = 1.0f;
					BCWaitTimer_ -= 1;
					if (BCWaitTimer_ == 0) {
						isEndChange_ = false;//暗幕の透明度を変化させるフラグを下す
						isStartChange_ = true;//暗幕の透明度を変化させるフラグを下す
						isPauseSelect = false;
						BCEaseDir_ *= -1;
						if (stageReset) {
							Scene::sceneNum_ = GAME;

						} else {
							Scene::sceneNum_ = SELECT;
						}
					}
				}
				if (addBCColor_ >= 0xFF) {
					addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す

			}


#pragma endregion

		} else {
#pragma region"ゲーム画面からクリア"

			if (!isStartChange_ && isEndChange_) {
				changeTime_ += 1;
				if (changeTime_ >= 60) {
					for (int i = 0; i < kMaxWall; i++) {

						if (wallT_ < 1.0f) {
							wallT_ += (1.0f / wallMoveTime_);

						} else {
							wallT_ = 1.0f;
						}
						wallPos_[i].x = (1 - wallT_) * wallStartPos_[i].x + wallT_ * wallEndPos_[i].x;
						wallPos_[i].y = (1 - wallT_) * wallStartPos_[i].y + wallT_ * wallEndPos_[i].y;
						soundVolume_[0] = (1 - wallT_) * 0.12f + wallT_ * 0;
						Novice::SetAudioVolume(BGMHandle_[0], soundVolume_[0]);

					}
				}
			}
			if (changeTime_ >= 120) {
				/*ドアの開く効果音*/
				if (!Novice::IsPlayingAudio(openDoorSEHandle_) || openDoorSEHandle_ == -1) {
					if (SECount_ == 0) {
						openDoorSEHandle_ = Novice::PlayAudio(rs.openDoorSE_, 0, 0.12f);
						SECount_++;
					}
				}
				//goal.UpDate();
				GopenT_ += (1.0f / 120) * easeDirGO_;
				if (easeDirGO_ > 0) {
					GopenAddT_ = EaseOutQuad(GopenT_);
				}
				if (GopenT_ >= 1.0f) {
					GopenT_ = 1.0f;
					easeDirGO_ = 0;

				}
				//左上頂点
				GCVertex_[0].x = (1 - GopenAddT_) * minVertexGO_[0].x + GopenAddT_ * maxVertexGO_[0].x;
				GCVertex_[0].y = (1 - GopenAddT_) * minVertexGO_[0].y + GopenAddT_ * maxVertexGO_[0].y;
				//左下頂点
				GCVertex_[2].x = (1 - GopenAddT_) * minVertexGO_[1].x + GopenAddT_ * maxVertexGO_[1].x;
				GCVertex_[2].y = (1 - GopenAddT_) * minVertexGO_[1].y + GopenAddT_ * maxVertexGO_[1].y;


			}

			if (changeTime_ >= 210) {
				for (int i = 0; i < kMaxStairs; i++) {
					timeCount_ += 1;
					if (timeCount_ > (stairsMoveTime_ / kMaxStairs) * i) {
						//stairs[i].Update();
						if (stairsT_[i] < 1.0f) {
							stairsT_[i] += (1.0f / 24.0f);
						} else {
							stairsT_[i] = 1.0f;
						}

						stairsPos_[i].x = (1 - stairsT_[i]) * stairsStartPos_[i].x + stairsT_[i] * stairsEndPos_[i].x;
					}

				}
			}

			if (changeTime_ >= 320) {
				isEndChange_ = false;
				isStartChange_ = true;
				Scene::sceneNum_ = CLEAR;
			}

		}
#pragma endregion

#pragma endregion
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		Reset();

#pragma region"クリア画面の開始処理（ゲームからクリア）"
		if (isStartChange_) {
			if (BCWaitTimer_ > 0) {
				BCWaitTimer_ -= 2;
			} else {
				WST_ += (1.0f / WSEaseTimer_) * WSEaseDir_;
				WSAddT_ = EaseInOutBounce(WST_);
				addWSColor_ = (1 - WSAddT_) * minWSColor_ + WSAddT_ * maxWSColor_;
				soundVolume_[1] = (1 - WSAddT_) * 0 + WSAddT_ * 0.12f;
				Novice::SetAudioVolume(BGMHandle_[1], soundVolume_[1]);
				if (WST_ >= 1.0f) {
					WST_ = 1.0f;
					isStartChange_ = false;
					BCWaitTimer_ = BCWaitMaxTimer_;
				}


				if (addWSColor_ >= 0xFF) {
					addWSColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}
				if (addWSColor_ <= 0x10) {
					addWSColor_ = 0x00;//バウンドで色がオーバーフローしないように上限で無理やり止める
				}

				WallStairsColor_ = 0x00000000 + int(addWSColor_);//ここで透明度を足す

			}
		}
#pragma endregion

#pragma region"クリア画面の終了処理（クリアからセレクト）"

		if (Global::controlMode_ == 0) {
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				if (CanCS && !isStartChange_ && !isEndChange_) {//クリア画面で全ての処理が終わったとき
					isEndChange_ = true;
					clearPushSEHandle_ = Novice::PlayAudio(rs.clearPushSE_, 0, soundVolume_[1]);
				}
			}
		} else {
			if (Novice::IsTriggerButton(0, kPadButton10) or
				Novice::IsTriggerButton(0, kPadButton11)) {

				if (CanCS && !isStartChange_ && !isEndChange_) {//クリア画面で全ての処理が終わったとき
					isEndChange_ = true;
					clearPushSEHandle_ = Novice::PlayAudio(rs.clearPushSE_, 0, soundVolume_[1]);
				}
			}
		}

		//足す透明度をイージング
		if (isEndChange_) {
			BCT_ += (1.0f / (BCEaseTimer_ / 1.5f)) * BCEaseDir_;
			BCAddT_ = EaseInCubic(BCT_);
			addBCColor_ = (1 - BCAddT_) * minBCColor_ + BCAddT_ * maxBCColor_;
			soundVolume_[1] = (1 - BCAddT_) * 0.12f + BCAddT_ * 0;
			Novice::SetAudioVolume(BGMHandle_[1], soundVolume_[1]);
			if (BCT_ >= 1.0f) {
				BCT_ = 1.0f;
				BCWaitTimer_ -= 1;
				if (BCWaitTimer_ == 0) {
					isEndChange_ = false;//暗幕の透明度を変化させるフラグを下す
					isStartChange_ = true;//暗幕の透明度を変化させるフラグを下す
					BCEaseDir_ *= -1;
					Scene::sceneNum_ = SELECT;
				}
			}
			if (addBCColor_ >= 0xFF) {
				addBCColor_ = 0xFF;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			BCColor_ = 0x00000000 + int(addBCColor_);//ここで透明度を足す

		}


#pragma endregion

		break;

	default:
		break;

	}
}

void  ChangeScene::Draw(int GH, unsigned int DoorColor, Vec2 goalPos, Vec2 goalSize, bool& isPauseSelect) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
				/*------------------------------状態遷移時の暗幕----------------------------------------*/
		Novice::DrawBox(0, 0, 480, 720, 0.0f, BCColor_, kFillModeSolid);

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

#pragma region"セレクトからゲームまでの開始処理"
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

		/*---------------------------------ゲ－ムからクリア---------------------------------*/

#pragma region"ゲームからクリアまでの終了処理"
		if (isEndChange_) {

			if (!isPauseSelect) {
				Novice::DrawBox(0, 0, 480, 720, 0.0f, 0x000000ee, kFillModeSolid);
				//扉の欄間から見える光
				Novice::DrawBox(int(goalPos.x - goalSize.x / 2), int(goalPos.y - goalSize.y / 2), int(goalSize.x), int(goalSize.y),
					0.0f, 0xFFFFFFFF, kFillModeSolid);

				//扉の外枠
				Novice::DrawBox(int(goalPos.x - goalSize.x / 2), int(goalPos.y - goalSize.y / 2), int(goalSize.x), int(goalSize.y),
					0.0f, 0x00000000, kFillModeWireFrame);
				//ドア本体
				Novice::DrawQuad(static_cast<int>(GCVertex_[0].x), static_cast<int>(GCVertex_[0].y), static_cast<int>(GCVertex_[1].x), static_cast<int>(GCVertex_[1].y),
					static_cast<int>(GCVertex_[2].x), static_cast<int>(GCVertex_[2].y), static_cast<int>(GCVertex_[3].x), static_cast<int>(GCVertex_[3].y), 0, 0, 100, 200, GH, 0x000000FF);

				/*迫ってくる壁の描画*/
				for (int i = 0; i < kMaxWall; i++) {
					Novice::DrawBox(
						int(wallPos_[i].x),
						int(wallPos_[i].y),
						int(wallWidth_),
						int(wallHeight_),
						0.0f,
						WallStairsColor_,
						kFillModeSolid);
				}

				if (changeTime_ >= 200) {
					/*階段状の壁*/
					for (int i = 0; i < kMaxStairs; i++) {
						Novice::DrawBox(
							int(stairsPos_[i].x),
							int(stairsPos_[i].y),
							int(stairsWidth_),
							int(stairsHeight_),
							0.0f,
							WallStairsColor_,
							kFillModeSolid);
					}
				}
			}
		}
#pragma endregion



#pragma endregion

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================


#pragma region"クリアの描画"


#pragma region"ゲームからクリア"
		if (isStartChange_) {
			Novice::DrawBox(
				0,
				0,
				int(Global::windowSize_.x),
				int(Global::windowSize_.y),
				0.0f,
				WallStairsColor_,
				kFillModeSolid);
		}
#pragma endregion




#pragma region"クリアからステージ選択まで"
		/*------------------------------状態遷移時の暗幕----------------------------------------*/
		if (isEndChange_) {
			Novice::DrawBox(0, 0, 480, 720, 0.0f, BCColor_, kFillModeSolid);
		}
#pragma endregion

		break;

#pragma endregion

	default:
		break;
	}
}



void ChangeScene::Reset() {
#pragma region"リセット"

	if (!isStartChange_ && !isEndChange_) {
		isStartChange_ = false;
		isEndChange_ = false;
		//isChangeSelect_ = false;
		isPushEscape_ = false;
		//状態遷移イージング用
		SCCPos_ = { -200,-100 };
		SCSize_ = { 200,400 };
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


		BCWaitMaxTimer_ = 60;
		BCWaitTimer_ = BCWaitMaxTimer_;



		//EndScene以外の時

		GCT_ = 0;//SceneChangeのｔ
		GCAddT_ = 0;//SceneChangeのaddT
		GCColor_ = 0xFFFFFFFF;//欄間から見える光の色

		//扉を開けるイージング用
		GopenT_ = 0;
		GopenAddT_ = 0;
		easeDirGO_ = 1;
		for (int j = 0; j < 2; j++) {
			minVertexGO_[j] = { 0 };
			maxVertexGO_[j] = { 0 };
		}
		isEaseGO_ = false;

		/*迫ってくる壁*/

		wallWidth_ = float(Global::windowSize_.x);
		wallHeight_ = float(Global::windowSize_.y);

		//EndScene以外の時
		for (int i = 0; i < 4; i++) {
			wallPos_[i] = { 0 };
			wallStartPos_[i] = { 0 };
			wallEndPos_[i] = { 0 };
		}
		wallT_ = 0;
		wallMoveTime_ = 120;

		/*階段*/

		stairsWidth_ = 41.2f;
		stairsHeight_ = 18.5f;
		for (int i = 0; i < 5; i++) {
			stairsPos_[i] = { 0 };
			stairsStartPos_[i] = { 0 };
			stairsEndPos_[i] = { 0 };
			stairsT_[i] = { 0 };
		}
		//暗幕変数(blackoutCurtainと呼称	WS)
		WST_ = 0;
		WSAddT_ = 0;
		WSEaseTimer_ = 51;
		WSEaseDir_ = 1;
		maxWSColor_ = 0x0;
		minWSColor_ = 0xFF;
		addWSColor_ = 0x0;
		isChangeColor_ = false;

		WallStairsColor_ = 0x000000FF;

		changeTime_ = 0;
		timeCount_ = 0;

		for (int i = 0; i < kMaxWall; i++) {
			switch (i) {
				///左側の壁--------------------------------------------------
			case 0:
				wallStartPos_[i].x = -(wallWidth_);
				wallStartPos_[i].y = 0;

				wallEndPos_[i].x = GCVertex_[0].x - wallWidth_;
				wallEndPos_[i].y = wallStartPos_[i].y;
				wallPos_[i] = wallStartPos_[i];
				break;
				///右側の壁--------------------------------------------------
			case 1:
				wallStartPos_[i].x = wallWidth_;
				wallStartPos_[i].y = 0;

				wallEndPos_[i].x = GCVertex_[1].x;
				wallEndPos_[i].y = wallStartPos_[i].y;
				wallPos_[i] = wallStartPos_[i];
				break;
				///上側の壁--------------------------------------------------
			case 2:
				wallStartPos_[i].x = 0;
				wallStartPos_[i].y = -(wallHeight_);

				wallEndPos_[i].x = wallStartPos_[i].x;
				wallEndPos_[i].y = GCVertex_[0].y - wallHeight_;
				wallPos_[i] = wallStartPos_[i];
				break;
				///下側の壁--------------------------------------------------
			case 3:
				wallStartPos_[i].x = 0;
				wallStartPos_[i].y = wallHeight_;

				wallEndPos_[i].x = wallStartPos_[i].x;
				wallEndPos_[i].y = GCVertex_[3].y;
				wallPos_[i] = wallStartPos_[i];
				break;
			}
		}

		for (int i = 0; i < kMaxStairs; i++) {
			stairsStartPos_[i].x = GCVertex_[0].x - stairsWidth_;
			stairsStartPos_[i].y = GCVertex_[0].y + (82 / kMaxStairs * i);

			stairsEndPos_[i].x = GCVertex_[0].x;
			stairsEndPos_[i].y = GCVertex_[0].y + (82 / kMaxStairs * i);

			stairsPos_[i] = stairsStartPos_[i];
			stairsT_[i] = 0;
		}
		openDoorSEHandle_ = -1;

		SECount_ = 0;
	}
#pragma endregion
}