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
}

void Shadow::Update(Map map) {

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

				} else if (mapChip_[i][j] == 11) {
					Novice::DrawQuad(//スイッチを踏むと現れるブロック
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

				} else if (mapChip_[i][j] == 8) {

					My::DrawStar(
						pos_[i][j],
						size_.x * 0.3f,
						0.0f,
						0x000000ff
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
			} else {

				if (mapChip_[i][j] == 11) {
					Novice::DrawQuad(//スイッチを踏むと現れるブロック(スイッチが踏まれていないとき)
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
						0x0000007f
					);
				}
			}
		}
	}
}