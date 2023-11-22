﻿#include "Shadow.h"

Shadow::Shadow(const Resources& rs, Screen screen) {

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
	goalSize_ = { float(size_.x*0.8f),float(size_.y*1.6f) };





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
			size_.y + (i * size_.y) - (size_.y * 0.5f)
				};
			}

			//存在フラグ決定
			if (mapChip_[i][j] == -2) {
				goalPos_ = {
			size_.x + (j * size_.x) + (size_.x * 0.7f),
			size_.y + (i * size_.y) - (size_.y * 0.4f)
				};

			}


			if (mapChip_[i][j] > 0) {
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

void Shadow::Draw(const Resources& rs) {
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

#pragma region"ゲーム本編の描画"
		for (int i = 0; i < mapChip_.size(); i++) {
			for (int j = 0; j < mapChip_[0].size(); j++) {

				if (touchable_[i][j]) {
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
						0x000000ff
					);
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
