#include "Shadow.h"

Shadow::Shadow(const Resources& rs, Screen screen) {

	pressTimeCount_ = 0;

	//要素を消去
	pos_.clear();
	mapChip_.clear();
	touchable_.clear();

	//マップ読み込み
	mapChip_ = LoadFile(rs.screenCsv_[Map::stageNum_]);

	//ブロックの縦横幅
	size_ = {
		((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
		((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size()
	};

	/*ゴール関係*/
	goalSize_ = { float(size_.x * 0.8f),float(size_.y * 1.6f) };


	//読み込んだマップチップの情報決定
	for (int i = 0; i < mapChip_.size(); i++) {

		std::vector<Vec2>rowPos;
		std::vector<bool>rowTouchable;

		for (int j = 0; j < mapChip_[0].size(); j++) {

			//座標決定
			rowPos.push_back(
				{
				size_.x + (j * size_.x) - (size_.x * 0.5f),
				size_.y + (i * size_.y) - (size_.y * 0.5f)
				}
			);

			//存在フラグ決定
			if (mapChip_[i][j] == -1) {
				firstPlayerPos_ = {
			size_.x + (j * size_.x) - (size_.x * 0.5f),
			size_.y + (i * size_.y) - (size_.y * 0.5f) - 1.0f
				};
			}
			//存在フラグ決定
			if (mapChip_[i][j] == -2) {
				goalPos_ = {
			size_.x + (j * size_.x) + (size_.x * 0.7f),
			size_.y + (i * size_.y) - (size_.y * 0.4f)
				};

			}

			if (mapChip_[i][j] > 0 && mapChip_[i][j] <= 10) {
				rowTouchable.push_back(true);

			} else {
				rowTouchable.push_back(false);
			}

		}

		pos_.push_back(rowPos);
		touchable_.push_back(rowTouchable);
	}

	//読み込んだマップチップの情報決定
	for (int i = 0; i < mapChip_.size(); i++) {
		for (int j = 0; j < mapChip_[0].size(); j++) {

			pos_[i][j].x += screen.GetScreenLeftTop().x;
			pos_[i][j].y += screen.GetScreenLeftTop().y;

		}
	}

	VectorVertexS(goalVertex_, goalPos_, goalSize_.x, goalSize_.y);
}

void Shadow::Init(const Resources& rs, Screen screen, int sceneNum) {

	switch (sceneNum) {
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

		pressTimeCount_ = 0;

		//要素を消去
		pos_.clear();
		mapChip_.clear();
		touchable_.clear();

		//マップ読み込み
		mapChip_ = LoadFile(rs.screenCsv_[Map::stageNum_]);

		//ブロックの縦横幅
		size_ = {
			((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
			((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size()
		};

		/*ゴール関係*/
		goalSize_ = { float(size_.x * 0.8f),float(size_.y * 1.6f) };


		//読み込んだマップチップの情報決定
		for (int i = 0; i < mapChip_.size(); i++) {

			std::vector<Vec2>rowPos;
			std::vector<bool>rowTouchable;

			for (int j = 0; j < mapChip_[0].size(); j++) {

				//座標決定
				rowPos.push_back(
					{
					size_.x + (j * size_.x) - (size_.x * 0.5f),
					size_.y + (i * size_.y) - (size_.y * 0.5f)
					}
				);

				//存在フラグ決定
				if (mapChip_[i][j] == -1) {
					firstPlayerPos_ = {
				size_.x + (j * size_.x) - (size_.x * 0.5f),
				size_.y + (i * size_.y) - (size_.y * 0.5f) - 1.0f
					};
				}
				//存在フラグ決定
				if (mapChip_[i][j] == -2) {
					goalPos_ = {
				size_.x + (j * size_.x) + (size_.x * 0.7f),
				size_.y + (i * size_.y) - (size_.y * 0.4f)
					};

				}

				if (mapChip_[i][j] > 0 && mapChip_[i][j] <= 10) {
					rowTouchable.push_back(true);

				} else {
					rowTouchable.push_back(false);
				}

			}

			pos_.push_back(rowPos);
			touchable_.push_back(rowTouchable);
		}

		//読み込んだマップチップの情報決定
		for (int i = 0; i < mapChip_.size(); i++) {
			for (int j = 0; j < mapChip_[0].size(); j++) {

				pos_[i][j].x += screen.GetScreenLeftTop().x;
				pos_[i][j].y += screen.GetScreenLeftTop().y;

			}
		}

		VectorVertexS(goalVertex_, goalPos_, goalSize_.x, goalSize_.y);
		
		SaveData::shadowMap_ = mapChip_;
		SaveData::savedShadowMap_ = SaveData::shadowMap_;
		
		break;

	case CLEAR:
		break;

	default:
		break;
	}
}



void Shadow::Update(char* keys, const ChangeScene& cs, const Resources& rs, const Screen& screen, Map map) {

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(rs, screen, Scene::sceneNum_);
	}

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

		//Rで初期化
		if (keys[DIK_R]) {
			if (!cs.isEndChange_) {
				Init(rs, screen, Scene::sceneNum_);
			}
		}


		//影の明るさ変更のためのタイムカウント
		if (map.GetIsPressSwitch()) {
			pressTimeCount_++;
		} else {
			pressTimeCount_--;
		}

		if (pressTimeCount_ > 32) {
			pressTimeCount_ = 32;
		}else if(pressTimeCount_ < 0){
			pressTimeCount_ = 0;
		}



		for (int i = 0; i < mapChip_.size(); i++) {
			for (int j = 0; j < mapChip_[0].size(); j++) {

				if (map.GetIsPressSwitch()) {
					if (mapChip_[i][j] > 10) {
						touchable_[i][j] = true;
					}
				} else {
					if (mapChip_[i][j] > 10) {
						touchable_[i][j] = false;
					}
				}
			}
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





void Shadow::Draw(const Resources& rs) {

	for (int i = 0; i < mapChip_.size(); i++) {
		for (int j = 0; j < mapChip_[0].size(); j++) {

			if (touchable_[i][j]) {

				if (mapChip_[i][j] == 1) {

					Novice::DrawQuad(
						int(pos_[i][j].x - size_.x * 0.5f),
						int(pos_[i][j].y - size_.y * 0.5f),
						int(pos_[i][j].x + size_.x * 0.5f + 1),
						int(pos_[i][j].y - size_.y * 0.5f),
						int(pos_[i][j].x - size_.x * 0.5f),
						int(pos_[i][j].y + size_.y * 0.5f),
						int(pos_[i][j].x + size_.x * 0.5f + 1),
						int(pos_[i][j].y + size_.y * 0.5f),
						0, 0,
						1, 1,
						rs.whiteGH_,
						0x222222ff
					);

					for (int k = 1; k < 5; k++) {
						Novice::DrawQuad(
							int((pos_[i][j].x - size_.x * 0.5f) - k * 1),
							int((pos_[i][j].y - size_.y * 0.5f) - k * 1),
							int((pos_[i][j].x + size_.x * 0.5f + 1) + k * 1),
							int((pos_[i][j].y - size_.y * 0.5f) - k * 1),
							int((pos_[i][j].x - size_.x * 0.5f) - k * 1),
							int((pos_[i][j].y + size_.y * 0.5f) + k * 1),
							int((pos_[i][j].x + size_.x * 0.5f + 1) + k * 1),
							int((pos_[i][j].y + size_.y * 0.5f) + k * 1),
							0, 0,
							1, 1,
							rs.whiteGH_,
							0x3f3f3f55
						);
					}

				} else if (mapChip_[i][j] == 2) {//トゲトゲ

					Vec2 inSideLT = { pos_[i][j].x - size_.x * 0.25f,pos_[i][j].y - size_.y * 0.25f };
					Vec2 inSideRT = { pos_[i][j].x + size_.x * 0.25f,pos_[i][j].y - size_.y * 0.25f };
					Vec2 inSideLB = { pos_[i][j].x - size_.x * 0.25f,pos_[i][j].y + size_.y * 0.25f };
					Vec2 inSideRB = { pos_[i][j].x + size_.x * 0.25f,pos_[i][j].y + size_.y * 0.25f };

					//中心の矩形
					Novice::DrawQuad(
						int(inSideLT.x),
						int(inSideLT.y),
						int(inSideRT.x),
						int(inSideRT.y),
						int(inSideLB.x),
						int(inSideLB.y),
						int(inSideRB.x),
						int(inSideRB.y),
						0, 0,
						1, 1,
						rs.whiteGH_,
						0x222222ff
					);

					//周りのトゲトゲ
					for (int k = 0; k < 3; k++) {
						Novice::DrawTriangle(
							int(inSideLT.x + k * (size_.x / 6)),
							int(inSideLT.y),
							int(inSideLT.x + k * (size_.x / 6) + size_.x / 12),
							int(pos_[i][j].y - size_.y * 0.5f),
							int(inSideLT.x + (k + 1) * (size_.x / 6)),
							int(inSideLT.y),
							0x222222ff,
							kFillModeSolid
						);

						Novice::DrawTriangle(
							int(inSideRT.x),
							int(inSideRT.y + k * (size_.y / 6)),
							int(pos_[i][j].x + size_.x * 0.5f),
							int(inSideRT.y + k * (size_.y / 6) + size_.y / 12),
							int(inSideRT.x),
							int(inSideRT.y + (k + 1) * (size_.y / 6)),
							0x222222ff,
							kFillModeSolid
						);

						Novice::DrawTriangle(
							int(inSideLB.x + k * (size_.x / 6)),
							int(inSideLB.y),
							int(inSideLB.x + k * (size_.x / 6) + size_.x / 12),
							int(pos_[i][j].y + size_.y * 0.5f),
							int(inSideLB.x + (k + 1) * (size_.x / 6)),
							int(inSideLB.y),
							0x222222ff,
							kFillModeSolid
						);

						Novice::DrawTriangle(
							int(inSideLT.x),
							int(inSideLT.y + k * (size_.y / 6)),
							int(pos_[i][j].x - size_.x * 0.5f),
							int(inSideLT.y + k * (size_.y / 6) + size_.y / 12),
							int(inSideLT.x),
							int(inSideLT.y + (k + 1) * (size_.y / 6)),
							0x222222ff,
							kFillModeSolid
						);

						for (int l = 1; l < 5; l++) {//とげの薄い影

							//中心の矩形
							Novice::DrawQuad(
								int(inSideLT.x),
								int(inSideLT.y),
								int(inSideRT.x),
								int(inSideRT.y),
								int(inSideLB.x),
								int(inSideLB.y),
								int(inSideRB.x),
								int(inSideRB.y),
								0, 0,
								1, 1,
								rs.whiteGH_,
								0x3f3f3f55
							);

							Novice::DrawTriangle(
								int(inSideLT.x + k * (size_.x / 6)) - l * 1,
								int(inSideLT.y) + l * 1,
								int(inSideLT.x + k * (size_.x / 6) + size_.x / 12),
								int(pos_[i][j].y - size_.y * 0.5f) - l * 1,
								int(inSideLT.x + (k + 1) * (size_.x / 6)) + l * 1,
								int(inSideLT.y) + l * 1,
								0x3f3f3f55,
								kFillModeSolid
							);

							Novice::DrawTriangle(
								int(inSideRT.x) - l * 1,
								int(inSideRT.y + k * (size_.y / 6)) - l * 1,
								int(pos_[i][j].x + size_.x * 0.5f) + l * 1,
								int(inSideRT.y + k * (size_.y / 6) + size_.y / 12),
								int(inSideRT.x) - l * 1,
								int(inSideRT.y + (k + 1) * (size_.y / 6)) + l * 1,
								0x3f3f3f55,
								kFillModeSolid
							);

							Novice::DrawTriangle(
								int(inSideLB.x + k * (size_.x / 6)) - l * 1,
								int(inSideLB.y)- l * 1,
								int(inSideLB.x + k * (size_.x / 6) + size_.x / 12),
								int(pos_[i][j].y + size_.y * 0.5f) + l * 1,
								int(inSideLB.x + (k + 1) * (size_.x / 6)) + l * 1,
								int(inSideLB.y) - l * 1,
								0x3f3f3f55,
								kFillModeSolid
							);

							Novice::DrawTriangle(
								int(inSideLT.x) + l * 1,
								int(inSideLT.y + k * (size_.y / 6)) - l * 1,
								int(pos_[i][j].x - size_.x * 0.5f) - l * 1,
								int(inSideLT.y + k * (size_.y / 6) + size_.y / 12),
								int(inSideLT.x) + l * 1,
								int(inSideLT.y + (k + 1) * (size_.y / 6)) + l * 1,
								0x3f3f3f55,
								kFillModeSolid
							);
						}
					}

				} else if (mapChip_[i][j] == 8) {

					//星アイテム
					My::DrawStar(
						{ pos_[i][j].x,
						pos_[i][j].y + cosf((float(Global::timeCount_) / 120.0f) * float(M_PI)) * 5.0f },
						size_.x * 0.3f,
						{ cosf((float(Global::timeCount_) / 120.0f) * float(M_PI)),1.0f },
						0.0f,
						0x3f3f3fff
					);



				} else if (mapChip_[i][j] == 7) {
					Novice::DrawQuad(
						int(pos_[i][j].x - size_.x * 0.5f),
						int(pos_[i][j].y + size_.y * 0.5f),
						int(pos_[i][j].x + size_.x * 0.5f + 1),
						int(pos_[i][j].y + size_.y * 0.5f),
						int(pos_[i][j].x - size_.x * 0.5f),
						int(pos_[i][j].y - size_.y * 0.5f),
						int(pos_[i][j].x + size_.x * 0.5f + 1),
						int(pos_[i][j].y - size_.y * 0.5f),
						0, 0,
						1, 1,
						rs.whiteGH_,
						0xffffffff
					);

				}
			}

			if (mapChip_[i][j] == 11) {
				Novice::DrawQuad(
					int(pos_[i][j].x - size_.x * 0.5f),
					int(pos_[i][j].y - size_.y * 0.5f),
					int(pos_[i][j].x + size_.x * 0.5f + 1),
					int(pos_[i][j].y - size_.y * 0.5f),
					int(pos_[i][j].x - size_.x * 0.5f),
					int(pos_[i][j].y + size_.y * 0.5f),
					int(pos_[i][j].x + size_.x * 0.5f + 1),
					int(pos_[i][j].y + size_.y * 0.5f),
					0, 0,
					1, 1,
					rs.whiteGH_,
					0x22222255 + int(float(0xaa) * EaseInOutExpo(float(pressTimeCount_) / 32.0f))
				);

				for (int k = 1; k < 5; k++) {
					Novice::DrawQuad(
						int((pos_[i][j].x - size_.x * 0.5f) - k * 1),
						int((pos_[i][j].y - size_.y * 0.5f) - k * 1),
						int((pos_[i][j].x + size_.x * 0.5f + 1) + k * 1),
						int((pos_[i][j].y - size_.y * 0.5f) - k * 1),
						int((pos_[i][j].x - size_.x * 0.5f) - k * 1),
						int((pos_[i][j].y + size_.y * 0.5f) + k * 1),
						int((pos_[i][j].x + size_.x * 0.5f + 1) + k * 1),
						int((pos_[i][j].y + size_.y * 0.5f) + k * 1),
						0, 0,
						1, 1,
						rs.whiteGH_,
						0x3f3f3f1f + int(float(0x20) * EaseInOutExpo(float(pressTimeCount_) / 32.0f))
					);
				}
			}
		}
	}
	/*CLEARのドア*/
/*欄間から見える光*/
	Novice::DrawBox(int(goalPos_.x - goalSize_.x / 2), int(goalPos_.y - goalSize_.y / 2), int(goalSize_.x), int(goalSize_.y),
		0.0f, 0xFFFFFFFF, kFillModeSolid);

	//ドア本体
	Novice::DrawQuad(static_cast<int>(goalVertex_[0].x), static_cast<int>(goalVertex_[0].y), static_cast<int>(goalVertex_[1].x), static_cast<int>(goalVertex_[1].y),
		static_cast<int>(goalVertex_[2].x), static_cast<int>(goalVertex_[2].y), static_cast<int>(goalVertex_[3].x), static_cast<int>(goalVertex_[3].y), 0, 0, 100, 200, rs.doorGH_, 0xFFFFFFFF);
	/*ドアここまで*/

}

