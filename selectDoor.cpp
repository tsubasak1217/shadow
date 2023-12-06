#include"selectDoor.h"


void SelectDoor::Draw(Resources rs) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		Novice::StopAudio(lightSEHandle_);
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
#pragma region"描画"

		Novice::DrawBox(0, 0, Global::windowSize_.x, Global::windowSize_.y, 0.0f, 0x444444FF, kFillModeSolid);
		//size_に応じてSpriteの表示サイズを変更
		Drawsize_.x = size_.x / 100;
		Drawsize_.y = size_.y / 200;
		for (int i = 0; i < 10; i++) {
			Novice::DrawEllipse(int(NumlightEllCPos_.x), 0, 60 + (i * 2), 5 + (i * 2), 0.0f, DLColor_, kFillModeSolid);
		}

		/*ステージの文字*/
		Novice::DrawBox(int(selectFontCPos_.x - selectFontSize_.x / 2), int(selectFontCPos_.y - selectFontSize_.y / 2), int(selectFontSize_.x), int(selectFontSize_.y), 0.0f, FColor_, kFillModeWireFrame);
		Novice::DrawSprite(int(selectFontCPos_.x - selectFontSize_.x / 2), int(selectFontCPos_.y - selectFontSize_.y / 2), rs.selectFontGH_, 0.5f, 0.5f, 0.0f, FColor_);


		//床の線
		Novice::DrawLine(0, int(NumlightEllCPos_.y - NumlightEllSize_.y - 15),Global::windowSize_.x, int(NumlightEllCPos_.y - NumlightEllSize_.y - 15),0x000000FF);


		for (int i = 0; i < 3; i++) {
			Novice::DrawEllipse(static_cast<int>(NumlightEllCPos_.x), static_cast<int>(NumlightEllCPos_.y),
				static_cast<int>(NumlightEllSize_.x + (i * 5)), static_cast<int>(NumlightEllSize_.y + (i * 5)), 0.0f, DLColor_, kFillModeSolid);
		}
		Novice::DrawQuad(static_cast<int>(NumVertex_[0].x), static_cast<int>(NumVertex_[0].y), static_cast<int>(NumVertex_[1].x), static_cast<int>(NumVertex_[1].y),
			static_cast<int>(NumVertex_[2].x), static_cast<int>(NumVertex_[2].y), static_cast<int>(NumVertex_[3].x), static_cast<int>(NumVertex_[3].y), (GHSize_ * (selectNum_ + 1)), 0, GHSize_, GHSize_, NumGH_, NumColor_);


		/*------------------------------選択する扉の描画------------------------------*/
		//扉の描画
		for (int i = 0; i < DOOR_MAX; i++)
		{
			if (isDraw_[i]) {
				//扉の欄間から見える光
				Novice::DrawBox(static_cast<int>(CPos_[i].x - size_.x / 2), static_cast<int>(CPos_[i].y - size_.y / 2),
					static_cast<int>(size_.x), static_cast<int>(size_.y), 0.0f, lightColor_[i], kFillModeSolid);
				//扉の外枠
				Novice::DrawBox(static_cast<int>(CPos_[i].x - size_.x / 2), static_cast<int>(CPos_[i].y - size_.y / 2),
					static_cast<int>(size_.x), static_cast<int>(size_.y), 0.0f, 0x000000FF, kFillModeWireFrame);
				//ドア本体
				Novice::DrawQuad(static_cast<int>(vertex_[i][0].x), static_cast<int>(vertex_[i][0].y), static_cast<int>(vertex_[i][1].x), static_cast<int>(vertex_[i][1].y),
					static_cast<int>(vertex_[i][2].x), static_cast<int>(vertex_[i][2].y), static_cast<int>(vertex_[i][3].x), static_cast<int>(vertex_[i][3].y), 0, 0, 100, 200, GH_, color_);
			}
		}

		/*------------------------------選択範囲の描画------------------------------*/
		//点滅させる
		DrawTimer_ -= 1;
		if (!isEaseM_) {
			if (DrawTimer_ == 0) {
				if (isSelectDraw_) {
					isSelectDraw_ = false;
					DrawTimer_ = DrawTimerMax_;
				} else {
					isSelectDraw_ = true;
					DrawTimer_ = DrawTimerMax_;
				}
			}
		} else {
			isSelectDraw_ = false;
			DrawTimer_ = DrawTimerMax_ + 5;
		}

		//選択範囲の描画
		if (isSelectDraw_) {
			Novice::DrawBox(static_cast<int>(selectPos_.x - (size_.x / 2) - 2), static_cast<int>(selectPos_.y - (size_.y / 2) - 2),
				static_cast<int>(size_.x + 4), static_cast<int>(size_.y + 4), 0.0f, selectColor_, kFillModeWireFrame);
		}


		/*------------------------------状態遷移時の暗幕----------------------------------------*/



#pragma endregion

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================
		Novice::StopAudio(lightSEHandle_);

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}



void SelectDoor::Update(char* keys, char* preKeys, const Resources& rs, int starGetCount) {

	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================

#pragma region"タイトルでの処理"
		Reset();

#pragma endregion


		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
#pragma region"選択範囲の移動"

	/*----------------------------選択範囲の移動--------------------------------------*/
		if (!isChangeScene_ &&
			!isEaseM_) {
			//左方向に移動
			if (keys[DIK_A] && preKeys[DIK_A] ||
				keys[DIK_LEFT] && preKeys[DIK_LEFT]) {
				if (selectNum_ > 0) {
					selectNum_--;
					moveT_ = 0.0f;
					moveAddT_ = 0.0f;
					selectCursorSEHandle_ = Novice::PlayAudio(rs.selectCursorSE_, 0, 0.12f);
					moveMaxPos_.x = CPos_[0].x + float(Global::windowSize_.x * 0.65f);
					moveMinPos_.x = CPos_[0].x;
					//CPos_[0].x += float(Global::windowSize_.x / 2);

					isEaseM_ = true;//イージングで移動するフラグ(select)
				}

			} else if (keys[DIK_D] && preKeys[DIK_D] ||
				keys[DIK_RIGHT] && preKeys[DIK_RIGHT]) {
				if (selectNum_ < DOOR_MAX-1) {
					selectNum_++;
					moveT_ = 0.0f;
					moveAddT_ = 0.0f;
					selectCursorSEHandle_ = Novice::PlayAudio(rs.selectCursorSE_, 0, 0.12f);
					moveMaxPos_.x = CPos_[0].x - float(Global::windowSize_.x * 0.65f);
					moveMinPos_.x = CPos_[0].x;
					//CPos_[0].x -= float(Global::windowSize_.x / 2);
					isEaseM_ = true;//イージングで移動するフラグ(select)
				}


			}
		} else {
			selectPos_ = CPos_[selectNum_];
		}

		//Numを範囲内に収める
		//selectNumは扉の添え字用の変数なので、0～7の範囲内
		/*
		if (selectNum_ == 8) {
			selectNum_ = 0;
		}
		if (selectNum_ == -1) {
			selectNum_ = 7;
		}*/

		//現地点と指定されたドアの位置を保存

		selectPos_ = CPos_[selectNum_];
		Map::stageNum_ = selectNum_;



		//選択範囲の移動
		if (isEaseM_) {
			//座標をイージングで移動
			moveT_ += (1 / easeTimerM_);
			moveAddT_ = EaseInOutCubic(moveT_);
			CPos_[0].x = (1 - moveAddT_) * moveMinPos_.x + moveAddT_ * moveMaxPos_.x;
			CPos_[0].y = (1 - moveAddT_) * moveMinPos_.y + moveAddT_ * moveMaxPos_.y;
			if (moveT_ >= 1) {
				moveT_ = 0.0f;
				moveAddT_ = 0.0f;
				CPos_[0].x = moveMaxPos_.x;
				isEaseM_ = false;//フラグを下す
			}
		}
		for (int i = 0; i < DOOR_MAX; i++) {
			CPos_[i] = { CPos_[0].x + (float(Global::windowSize_.x * 0.65f) * i),float(Global::windowSize_.y / 2) };
			//４頂点を求める
			VectorVertexS(vertex_[i], CPos_[i], size_.x, size_.y);
		}


#pragma endregion

#pragma region"シーン遷移開始させる"
		/*
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] &&
			!isChangeScene_) {
			//何か条件を追加しないと連打でバグるかも
			isChangeScene_ = true;
		}
		*/
#pragma endregion

#pragma region"ステージ番号表示用のライトの点滅イージング"
		//足す透明度をイージング
		if (!isChangeScene_ ||
			!isEaseM_) {
			DLT_ += (1.0f / DLEaseTimer_) * DLEaseDir_;
			DLAddT_ = EaseInOutBounce(DLT_);
			addDLColor_ = (1 - DLAddT_) * minDLColor_ + DLAddT_ * maxDLColor_;

			if (DLT_ >= 1.0f) {
				DLT_ = 1.0f;
				DLWaitTimer_ -= 1;
				if (DLWaitTimer_ == 0) {
					DLEaseDir_ *= -1;
					DLWaitTimer_ = DLWaitTimerMax_;
					lightSEHandle_ = Novice::PlayAudio(rs.selectLightSE_, 0, 0.4f);
				}
			}

			if (DLT_ <= 0.0f) {
				DLT_ = 0.0f;
				DLEaseDir_ *= -1;

			}

			if (addDLColor_ >= maxDLColor_) {
				addDLColor_ = maxDLColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			if (addDLColor_ <= minDLColor_) {
				addDLColor_ = minDLColor_;//バウンドで色がオーバーフローしないように上限で無理やり止める
			}
			//Novice::ScreenPrintf(0, 150, "SCColor=%x", SCColor_);
			DLColor_ = 0xFFFFFF00 + int(addDLColor_);//で透明度を足す
			NumColor_ = 0x44444400 + int(addDLColor_ + 55);//文字も色変更
		}
#pragma endregion

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

#pragma region"ゲームでの処理"
		Reset();
#pragma endregion

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================

		if (starGetCount == 3) {
			lightColor_[selectNum_] = 0xE7E15AFF;
			// 0xD4CD52FF;
			//0xA29B0DFF;
		}

		break;

	default:
		break;
	}

}

#pragma region"シーン遷移"
/*--------------------------------シーン遷移-----------------------------------*/
/*
//スペースキーを押したらシーン遷移用の扉の座標を設定&&暗幕を下す
if (keys[DIK_0] && !preKeys[DIK_0] &&
	!isChangeScene_) {
	//何か条件を追加しないと連打でバグるかも
	isChangeScene_ = true;
	isSetSCPos_ = true;
	isChangeColor_ = true;
}

//選択した扉の位置を状態遷移用の扉の座標に代入する
if (isSetSCPos_) {
	SCCPos_ = CPos_[selectNum_];
	minSCSize_ = SCSize_;
	maxSCSize_ = { 480,960 };//元300,600//画面全体覆うサイズに変更
	minSCCPos_ = SCCPos_;
	maxSCCPos_ = { 240,360 };
	isSetSCPos_ = false;
}

/*-------------------------------暗幕のイージング--------------------------------*/
/*
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
		for (int i = 0; i < DOOR_MAX; i++) {
			isDraw_[i] = false;//描画されている他の扉を消す//扉の上のレイヤーに暗幕を下すので必要ないかも
		}
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
Novice::ScreenPrintf(0, 100, "SCColor=%x", SCColor_);

/*-------------------------------状態遷移用扉を中央に持っていくイージング--------------------------------*/
/*
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
/*-------------------------------状態遷移用扉を開くイージング--------------------------------*/
/*
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
			isAllDraw_ = false;
		}
		//左上頂点
		SCVertex_[0].x = (1 - openAddT_) * minVertexO_[0].x + openAddT_ * maxVertexO_[0].x;
		SCVertex_[0].y = (1 - openAddT_) * minVertexO_[0].y + openAddT_ * maxVertexO_[0].y;
		//左下頂点
		SCVertex_[2].x = (1 - openAddT_) * minVertexO_[1].x + openAddT_ * maxVertexO_[1].x;
		SCVertex_[2].y = (1 - openAddT_) * minVertexO_[1].y + openAddT_ * maxVertexO_[1].y;
	}

#pragma endregion
	//ここまで


#pragma endregion

}



void DOOR::Debug(char* keys, char* preKeys) {

#pragma region"デバック用"
#if _DEBUG
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
	case 1:
		if (keys[DIK_W]) {
			EllPos_.y -= 1;
		}
		if (keys[DIK_S]) {
			EllPos_.y += 1;
		}
		if (keys[DIK_A]) {
			EllPos_.x -= 1;
		}
		if (keys[DIK_D]) {
			EllPos_.x += 1;
		}
		break;
	case 2:
		if (keys[DIK_W]) {
			EllSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			EllSize_.y += 1;
		}
		if (keys[DIK_A]) {
			EllSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			EllSize_.x += 1;
		}
		break;
	case 3:
		if (keys[DIK_W]) {
			length_.y -= 1;
		}
		if (keys[DIK_S]) {
			length_.y += 1;
		}
		if (keys[DIK_A]) {
			length_.x -= 1;
		}
		if (keys[DIK_D]) {
			length_.x += 1;
		}
		break;
	default:
		break;
	}
	Novice::ScreenPrintf(0, 0, "debugNum=%d", debugNum);
	Novice::ScreenPrintf(0, 20, "EllPos_ x=%f,y=%f", EllPos_.x, EllPos_.y);
	Novice::ScreenPrintf(0, 40, "Ellsize_ x=%f,y=%f", EllSize_.x, EllSize_.y);
	Novice::ScreenPrintf(0, 60, "length_ x=%f,y=%f", length_.x, length_.y);

#endif // _DEBUG


}
*/
#pragma endregion





void SelectDoor::Reset() {

#pragma region"リセット"


	/*変数の値リセット*/

	//ドア本体の変数
	for (int i = 0; i < DOOR_MAX; i++) {
		//CPos_[i] = { 0 };
		size_ = { 200,400 };
		Drawsize_ = { 0 };
		theta_[i] = { 0 };
		isDraw_[i] = true;
		rotateLength_[i] = { 0 };
		for (int j = 0; j < 4; j++) {
			vertex_[i][j] = { 0 };
		}

	}
	color_ = 0x000000FF;

	//lightColor_ = 0xFFFFFFFF;


	//GH_ = Novice::LoadTexture("./images/Door.png");
	//円周上に並んでいるドアの原点
	originPos_ = { 240,512 };
	length_ = { 215,0 };

	//選択範囲の変数
	if (Scene::sceneNum_ == TITLE) {
		selectNum_ = 0;
		selectPos_ = { 0 };
		moveMinPos_ = CPos_[0];
		moveMaxPos_ = CPos_[0];
	}
	selectColor_ = 0xFF0000FF;
	isSelectDraw_ = false;
	isEaseM_ = false;
	DrawTimerMax_ = 45;
	DrawTimer_ = DrawTimerMax_;
	easeTimerM_ = 20;//フレーム指定
	moveT_ = 0.0f;
	moveAddT_ = 0.0f;

	//床の円
	EllSize_ = { 185,85 };//{ 260,276 };
	EllPos_ = { 240,640 }; //{ 240,615 };


	//*-------------------------------各ドアの座標を求める----------------------------------*//

	for (int i = 0; i < DOOR_MAX; i++) {
		//角度を決める
		//theta_[i] = theta_[0] + (1.0f / 7.0f * float(M_PI)) * i;
		//theta_[0] = (float(M_PI));
		//移動
		//rotateLength_[i] = rotateVect(length_, sinf(theta_[i]), cosf(theta_[i]));
		//円形に配置
		if (Scene::sceneNum_ == TITLE) {
			CPos_[i] = { float(Global::windowSize_.x / 2) + (float(Global::windowSize_.x / 2) * i),float(Global::windowSize_.y / 2) };
		}
		//４頂点を求める
		VectorVertexS(vertex_[i], CPos_[i], size_.x, size_.y);
	}

	VectorVertexS(NumVertex_, NumlightEllCPos_, NumlightEllSize_.x, NumlightEllSize_.y);


	//*-------------------------------選択範囲の座標-------------------------------------*//
	selectPos_ = CPos_[selectNum_];//CPos_[0]が決定したのでここでselectPos_に代入


#pragma endregion


}
void SelectDoor::Debug(char* keys, char* preKeys) {
#pragma region"デバック用"
#if _DEBUG
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
			NumVertex_[3].y -= 1;
		}
		if (keys[DIK_S]) {
			NumVertex_[3].y += 1;
		}
		if (keys[DIK_A]) {
			NumVertex_[3].x -= 1;
		}
		if (keys[DIK_D]) {
			NumVertex_[3].x += 1;
		}
		break;
	case 1:
		if (keys[DIK_W]) {
			NumlightEllCPos_.y -= 1;
		}
		if (keys[DIK_S]) {
			NumlightEllCPos_.y += 1;
		}
		if (keys[DIK_A]) {
			NumlightEllCPos_.x -= 1;
		}
		if (keys[DIK_D]) {
			NumlightEllCPos_.x += 1;
		}
		break;
	case 2:
		if (keys[DIK_W]) {
			NumlightEllSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			NumlightEllSize_.y += 1;
		}
		if (keys[DIK_A]) {
			NumlightEllSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			NumlightEllSize_.x += 1;
		}
		break;
	case 3:
		if (keys[DIK_W]) {
			NumVertex_[2].y -= 1;
		}
		if (keys[DIK_S]) {
			NumVertex_[2].y += 1;
		}
		if (keys[DIK_A]) {
			NumVertex_[2].x -= 1;
		}
		if (keys[DIK_D]) {
			NumVertex_[2].x += 1;
		}
		break;
	default:
		break;
	}
	Novice::ScreenPrintf(0, 0, "debugNum=%d", debugNum);
	Novice::ScreenPrintf(0, 20, "NumlightEllCPos_ x=%f,y=%f", NumlightEllCPos_.x, NumlightEllCPos_.y);
	Novice::ScreenPrintf(0, 40, "NumlightEllSize_x = %f, y = %f", NumlightEllSize_.x, NumlightEllSize_.y);
	Novice::ScreenPrintf(0, 60, "length_ x=%f,y=%f", length_.x, length_.y);
#endif // _DEBUG
#pragma endregion

}
