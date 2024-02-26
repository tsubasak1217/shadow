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
		/*灰色の背景*/
		Novice::DrawBox(0, 0, Global::windowSize_.x, Global::windowSize_.y, 0.0f, 0x444444FF, kFillModeSolid);

		//size_に応じてSpriteの表示サイズを変更
		Drawsize_.x = size_.x / 100;
		Drawsize_.y = size_.y / 200;

		/*天井のライトの描画*/
		for (int i = 0; i < 10; i++) {
			Novice::DrawEllipse(int(NumlightEllCPos_.x), 0, 60 + (i * 2), 5 + (i * 2), 0.0f, DLColor_, kFillModeSolid);
		}

		/*ステージロゴの文字STAGE　SELECT*/
		Novice::DrawBox(int(selectFontCPos_.x - selectFontSize_.x / 2), int(selectFontCPos_.y - selectFontSize_.y / 2), int(selectFontSize_.x), int(selectFontSize_.y), 0.0f, FColor_, kFillModeWireFrame);
		Novice::DrawSprite(int(selectFontCPos_.x - selectFontSize_.x / 2), int(selectFontCPos_.y - selectFontSize_.y / 2), rs.selectFontGH_, 0.5f, 0.5f, 0.0f, FColor_);


		//床の線
		Novice::DrawLine(0, int(NumlightEllCPos_.y - NumlightEllSize_.y - 15), Global::windowSize_.x, int(NumlightEllCPos_.y - NumlightEllSize_.y - 15), 0x000000FF);

		/*床のライトの描画*/
		for (int i = 0; i < 3; i++) {
			Novice::DrawEllipse(static_cast<int>(NumlightEllCPos_.x), static_cast<int>(NumlightEllCPos_.y),
				static_cast<int>(NumlightEllSize_.x + (i * 5)), static_cast<int>(NumlightEllSize_.y + (i * 5)), 0.0f, DLColor_, kFillModeSolid);
		}

		/*床のライトに映るステージ番号*/
		if (selectNum_ < 9) {	//一桁の時
			//今のステージの番号
			Novice::DrawQuad(static_cast<int>(NumVertex_[0].x), static_cast<int>(NumVertex_[0].y), static_cast<int>(NumVertex_[1].x), static_cast<int>(NumVertex_[1].y),
				static_cast<int>(NumVertex_[2].x), static_cast<int>(NumVertex_[2].y), static_cast<int>(NumVertex_[3].x), static_cast<int>(NumVertex_[3].y), (GHSize_ * (selectNum_ + 1)), 0, GHSize_, GHSize_, NumGH_, NumColor_);
		} else {//二桁のとき
			//今のステージの番号10の位
			Novice::DrawQuad(static_cast<int>(NumVertexOnes_[0].x), static_cast<int>(NumVertexOnes_[0].y), static_cast<int>(NumVertexOnes_[1].x), static_cast<int>(NumVertexOnes_[1].y),
				static_cast<int>(NumVertexOnes_[2].x), static_cast<int>(NumVertexOnes_[2].y), static_cast<int>(NumVertexOnes_[3].x), static_cast<int>(NumVertexOnes_[3].y), (GHSize_ * (selectNum_ - 9)), 0, GHSize_, GHSize_, NumGH_, NumColor_);
			//1の位
			Novice::DrawQuad(static_cast<int>(NumVertexTens_[0].x), static_cast<int>(NumVertexTens_[0].y), static_cast<int>(NumVertexTens_[1].x), static_cast<int>(NumVertexTens_[1].y),
				static_cast<int>(NumVertexTens_[2].x), static_cast<int>(NumVertexTens_[2].y), static_cast<int>(NumVertexTens_[3].x), static_cast<int>(NumVertexTens_[3].y), (GHSize_ * 1), 0, GHSize_, GHSize_, NumGH_, NumColor_);

		}


		//ステージの最大数を表示
		//1
		Novice::DrawQuad(static_cast<int>(maxNumVertex_[0][0].x), static_cast<int>(maxNumVertex_[0][0].y), static_cast<int>(maxNumVertex_[0][1].x), static_cast<int>(maxNumVertex_[0][1].y),
			static_cast<int>(maxNumVertex_[0][2].x), static_cast<int>(maxNumVertex_[0][2].y), static_cast<int>(maxNumVertex_[0][3].x), static_cast<int>(maxNumVertex_[0][3].y), (GHSize_ * 1), 0, GHSize_, GHSize_, NumGH_, NumColor_);
		//6
		Novice::DrawQuad(static_cast<int>(maxNumVertex_[1][0].x), static_cast<int>(maxNumVertex_[1][0].y), static_cast<int>(maxNumVertex_[1][1].x), static_cast<int>(maxNumVertex_[1][1].y),
			static_cast<int>(maxNumVertex_[1][2].x), static_cast<int>(maxNumVertex_[1][2].y), static_cast<int>(maxNumVertex_[1][3].x), static_cast<int>(maxNumVertex_[1][3].y), (GHSize_ * 6), 0, GHSize_, GHSize_, NumGH_, NumColor_);
		//[/]
		Novice::DrawQuad(static_cast<int>(slashVertex_[0].x), static_cast<int>(slashVertex_[0].y), static_cast<int>(slashVertex_[1].x), static_cast<int>(slashVertex_[1].y),
			static_cast<int>(slashVertex_[2].x), static_cast<int>(slashVertex_[2].y), static_cast<int>(slashVertex_[3].x), static_cast<int>(slashVertex_[3].y), 0, 0, 100, 100, rs.slashGH_, NumColor_);



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



void SelectDoor::Update(char* keys, char* preKeys, const Resources& rs, int starGetCount,bool startChange) {

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
#pragma region"選択範囲と扉を移動"

	/*----------------------------選択範囲の移動--------------------------------------*/
		/*シーン遷移が行われていないとき、かつ扉が移動していないとき*/
		if (!isChangeScene_ &&
			!isEaseM_ &&
			!startChange) {

			if (Global::controlMode_ == 0) {
				if (keys[DIK_D] && preKeys[DIK_D] ||
					keys[DIK_RIGHT] && preKeys[DIK_RIGHT]) {

					if (selectNum_ < DOOR_MAX - 1) {//ステージの右端以外なら動く
						//ステージ番号インクリメント
						selectNum_++;
						moveT_ = 0.0f;
						moveAddT_ = 0.0f;

						//扉自体をイージングするため、最大・最小座標をセット
						selectCursorSEHandle_ = Novice::PlayAudio(rs.selectCursorSE_, 0, 0.12f);
						moveMaxPos_.x = CPos_[0].x - float(Global::windowSize_.x * 0.65f);
						moveMinPos_.x = CPos_[0].x;

						isEaseM_ = true;//イージングで移動するフラグ(扉を移動)
					}
				} else if (keys[DIK_A] && preKeys[DIK_A] ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT]) {//左方向に移動
					if (selectNum_ > 0) {//ステージの左端以外なら動く
						//ステージ番号をデクリメント
						selectNum_--;
						moveT_ = 0.0f;
						moveAddT_ = 0.0f;

						//扉自体をイージングするため、最大・最小座標をセット
						selectCursorSEHandle_ = Novice::PlayAudio(rs.selectCursorSE_, 0, 0.12f);
						moveMaxPos_.x = CPos_[0].x + float(Global::windowSize_.x * 0.65f);
						moveMinPos_.x = CPos_[0].x;

						isEaseM_ = true;//イージングで移動するフラグ(扉を移動)
					}

				}
			} else {

				if (Global::leftStickValue_.x > 0 ||
					Novice::IsPressButton(0,kPadButton3)) {

					if (selectNum_ < DOOR_MAX - 1) {//ステージの右端以外なら動く
						//ステージ番号インクリメント
						selectNum_++;
						moveT_ = 0.0f;
						moveAddT_ = 0.0f;

						//扉自体をイージングするため、最大・最小座標をセット
						selectCursorSEHandle_ = Novice::PlayAudio(rs.selectCursorSE_, 0, 0.12f);
						moveMaxPos_.x = CPos_[0].x - float(Global::windowSize_.x * 0.65f);
						moveMinPos_.x = CPos_[0].x;

						isEaseM_ = true;//イージングで移動するフラグ(扉を移動)
					}
				} else if (Global::leftStickValue_.x < 0 ||
					Novice::IsPressButton(0, kPadButton2)) {//左方向に移動
					if (selectNum_ > 0) {//ステージの左端以外なら動く
						//ステージ番号をデクリメント
						selectNum_--;
						moveT_ = 0.0f;
						moveAddT_ = 0.0f;

						//扉自体をイージングするため、最大・最小座標をセット
						selectCursorSEHandle_ = Novice::PlayAudio(rs.selectCursorSE_, 0, 0.12f);
						moveMaxPos_.x = CPos_[0].x + float(Global::windowSize_.x * 0.65f);
						moveMinPos_.x = CPos_[0].x;

						isEaseM_ = true;//イージングで移動するフラグ(扉を移動)
					}

				}
			}
		} 


		selectPos_ = CPos_[selectNum_];
		Map::stageNum_ = selectNum_;

		//扉の中心座標を横に移動
		if (isEaseM_) {
			//座標をイージングで移動
			moveT_ += (1 / easeTimerM_);
			moveAddT_ = EaseInOutCubic(moveT_);
			CPos_[0].x = (1 - moveAddT_) * moveMinPos_.x + moveAddT_ * moveMaxPos_.x;
			CPos_[0].y = (1 - moveAddT_) * moveMinPos_.y + moveAddT_ * moveMaxPos_.y;
			//最大値になったら値を強制的に最大値にする
			if (moveT_ >= 1) {
				moveT_ = 0.0f;
				moveAddT_ = 0.0f;
				CPos_[0].x = moveMaxPos_.x;
				isEaseM_ = false;//フラグを下す
			}
		}

		/*移動した後の扉の形を形成*/
		for (int i = 0; i < DOOR_MAX; i++) {
			CPos_[i] = { CPos_[0].x + (float(Global::windowSize_.x * 0.65f) * i),float(Global::windowSize_.y / 2) };
			//４頂点を求める
			VectorVertexS(vertex_[i], CPos_[i], size_.x, size_.y);
		}


#pragma endregion

#pragma region"ステージ番号表示用のライトの点滅イージング"
		//足す透明度をイージング
		if (!isChangeScene_ ||
			!isEaseM_) {
			DLT_ += (1.0f / DLEaseTimer_) * DLEaseDir_;
			DLAddT_ = EaseInOutBounce(DLT_);
			addDLColor_ = (1 - DLAddT_) * minDLColor_ + DLAddT_ * maxDLColor_;
			/*ｔが最大値になったら一定時間停止（ライトを点灯させ続ける）*/
			if (DLT_ >= 1.0f) {
				DLT_ = 1.0f;
				DLWaitTimer_ -= 1;//タイマーを減らす
				if (DLWaitTimer_ == 0) {//０になったら
					DLEaseDir_ *= -1;
					DLWaitTimer_ = DLWaitTimerMax_;
					lightSEHandle_ = Novice::PlayAudio(rs.selectLightSE_, 0, 0.4f);//点滅音
				}
			}
			/*ｔが最小値になったら即座に増加させる*/
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

#pragma region"クリアでの処理"

		/*クリアした時入手した星の数が３つならそのステージのドアの色を黄色に変更*/
		if (starGetCount == 3) {
			lightColor_[selectNum_] = 0xE7E15AFF;
			// 0xD4CD52FF;
			//0xA29B0DFF;
		}
#pragma endregion

		break;

	default:
		break;
	}

}





void SelectDoor::Reset() {

#pragma region"リセット"


	/*変数の値リセット*/

	//ドア本体の変数
	for (int i = 0; i < DOOR_MAX; i++) {
		//CPos_[i] = { 0 };
		size_ = { 200,400 };
		Drawsize_ = { 0 };
		isDraw_[i] = true;

		for (int j = 0; j < 4; j++) {
			vertex_[i][j] = { 0 };
		}

	}
	color_ = 0x000000FF;

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



	//*-------------------------------各ドアの座標を求める----------------------------------*//

	for (int i = 0; i < DOOR_MAX; i++) {
		if (Scene::sceneNum_ == TITLE) {
			CPos_[i] = { float(Global::windowSize_.x / 2) + (float(Global::windowSize_.x / 2) * i),float(Global::windowSize_.y / 2) };
		}
		//４頂点を求める
		VectorVertexS(vertex_[i], CPos_[i], size_.x, size_.y);
	}


	//ライトの頂点を表示
	NumCPosTens_ = { NumCPos_.x - NumlightEllSize_.x * 0.22f,NumCPos_.y };
	NumCPosOnes_ = { NumCPos_.x + NumlightEllSize_.x * 0.22f,NumCPos_.y };
	/*現在のステージ番号の各頂点を計算（1ケタの時）*/
	VectorVertexS(NumVertex_, NumCPos_, NumlightEllSize_.x, NumlightEllSize_.y);
	/*現在のステージ番号の各頂点を計算（10ケタの時）*/
	//10のけた
	VectorVertexS(NumVertexTens_, NumCPosTens_, NumlightEllSize_.x * 0.8f, NumlightEllSize_.y * 0.8f);
	//1のけた
	VectorVertexS(NumVertexOnes_, NumCPosOnes_, NumlightEllSize_.x * 0.8f, NumlightEllSize_.y * 0.8f);
	//ステージ最大数の各頂点を計算
	VectorVertexS(maxNumVertex_[0], maxNumCPos_[0], maxNumSize_.x, maxNumSize_.y);
	VectorVertexS(maxNumVertex_[1], maxNumCPos_[1], maxNumSize_.x, maxNumSize_.y);
	//スラッシュのスプライトの各頂点を計算
	VectorVertexS(slashVertex_, slashCPos_, slashSize_.x, slashSize_.y);

	//*-------------------------------選択範囲の座標-------------------------------------*//
	selectPos_ = CPos_[selectNum_];//CPos_[0]が決定したのでここでselectPos_に代入


#pragma endregion


}





void SelectDoor::Debug(char* keys, char* preKeys) {
	if (keys, preKeys) {

	}
#pragma region"デバック用"
#if _DEBUG
	/*
	//操作したい番号選択
	if (keys[DIK_T] && !preKeys[DIK_T]) {
		debugNum += 1;
		//[1]=originPos_
		//[2]=size_
		//[3]=length_
		if (debugNum == 7) {
			debugNum = 0;
		}

	}
	switch (debugNum)
	{

	case 0:
		if (keys[DIK_W]) {
			slashCPos_.y--;//slashVertex_[0].y -= 1;
		}
		if (keys[DIK_S]) {
			slashCPos_.y++;//slashVertex_[0].y += 1;
		}
		if (keys[DIK_A]) {
			slashCPos_.x--;//slashVertex_[0].x -= 1;
		}
		if (keys[DIK_D]) {
			slashCPos_.x++;//slashVertex_[0].x += 1;
		}
		break;
	case 1:
		if (keys[DIK_W]) {
			slashSize_.y--;//slashVertex_[1].y -= 1;
		}
		if (keys[DIK_S]) {
			slashSize_.y++;//slashVertex_[1].y += 1;
		}
		if (keys[DIK_A]) {
			slashSize_.x--;//slashVertex_[1].x -= 1;
		}
		if (keys[DIK_D]) {
			slashSize_.x++;//slashVertex_[1].x += 1;
		}
		break;
	case 2:
		if (keys[DIK_W]) {
			maxNumCPos_[0].y -= 1;
		}
		if (keys[DIK_S]) {
			maxNumCPos_[0].y += 1;
		}
		if (keys[DIK_A]) {
			maxNumCPos_[0].x -= 1;
		}
		if (keys[DIK_D]) {
			maxNumCPos_[0].x += 1;
		}
		break;
	case 3:
		if (keys[DIK_W]) {
			maxNumCPos_[1].y -= 1;
		}
		if (keys[DIK_S]) {
			maxNumCPos_[1].y += 1;
		}
		if (keys[DIK_A]) {
			maxNumCPos_[1].x -= 1;
		}
		if (keys[DIK_D]) {
			maxNumCPos_[1].x += 1;
		}
		break;
	case 4:
		if (keys[DIK_W]) {
			maxNumSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			maxNumSize_.y += 1;
		}
		if (keys[DIK_A]) {
			maxNumSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			maxNumSize_.x += 1;
		}
		break;
	case 5:
		if (keys[DIK_W]) {
			NumCPos_.y--;//slashCPos_.y--;//slashVertex_[0].y -= 1;
		}
		if (keys[DIK_S]) {
			NumCPos_.y++;//slashCPos_.y++;//slashVertex_[0].y += 1;
		}
		if (keys[DIK_A]) {
			NumCPos_.x--;//slashCPos_.x--;//slashVertex_[0].x -= 1;
		}
		if (keys[DIK_D]) {
			NumCPos_.x++;	//slashCPos_.x++;//slashVertex_[0].x += 1;
		}
		break;

	case 6:
		if (keys[DIK_W]) {
			//	maxNumSize_.y -= 1;
		}
		if (keys[DIK_S]) {
			//maxNumSize_.y += 1;
		}
		if (keys[DIK_A]) {
			//maxNumSize_.x -= 1;
		}
		if (keys[DIK_D]) {
			//maxNumSize_.x += 1;
		}
		break;

	default:
		break;
	}
	VectorVertexS(NumVertex_, NumCPos_, NumlightEllSize_.x, NumlightEllSize_.y);
	VectorVertexS(maxNumVertex_[0], maxNumCPos_[0], maxNumSize_.x, maxNumSize_.y);
	VectorVertexS(maxNumVertex_[1], maxNumCPos_[1], maxNumSize_.x, maxNumSize_.y);

	VectorVertexS(slashVertex_, slashCPos_, slashSize_.x, slashSize_.y);


	Novice::ScreenPrintf(0, 0, "debugNum=%d", debugNum);
	Novice::ScreenPrintf(0, 20, "NumlightEllCPos_ x=%f,y=%f", NumlightEllCPos_.x, NumlightEllCPos_.y);
	Novice::ScreenPrintf(0, 40, "NumlightEllSize_x = %f, y = %f", NumlightEllSize_.x, NumlightEllSize_.y);
	Novice::ScreenPrintf(0, 60, "NumCPos_ x=%f,y=%f", NumCPos_.x, NumCPos_.y);
	Novice::ScreenPrintf(0, 80, "NummaxCPos_[0] x=%f,y=%f", maxNumCPos_[0].x, maxNumCPos_[0].y);
	Novice::ScreenPrintf(0, 100, "NummaxCPos_[1] x=%f,y=%f", maxNumCPos_[1].x, maxNumCPos_[1].y);

	Novice::ScreenPrintf(0, 120, "Vertex[0] x=%f,y=%f", slashVertex_[0].x, slashVertex_[0].y);
	Novice::ScreenPrintf(0, 140, "Vertex[1] x=%f,y=%f", slashVertex_[1].x, slashVertex_[1].y);
	Novice::ScreenPrintf(0, 160, "Vertex[2] x=%f,y=%f", slashVertex_[2].x, slashVertex_[2].y);
	Novice::ScreenPrintf(0, 180, "Vertex[3] x=%f,y=%f", slashVertex_[3].x, slashVertex_[3].y);
	Novice::ScreenPrintf(0, 200, "CPos x=%f,y=%f", slashCPos_.x, slashCPos_.y);

	*/
#endif // _DEBUG
#pragma endregion

}
