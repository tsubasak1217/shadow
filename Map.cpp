#include "Map.h"

Map::Map(Global global) {

	//要素を消去
	pos_.clear();
	mapChip_.clear();
	touchable_.clear();
	vertex_.clear();

	//マップ読み込み
	mapChip_ = LoadFile("./Resources/mapChip.csv");
	//行を反転(ワールド座標表示のため)
//	std::reverse(mapChip_.begin(), mapChip_.end());


	//ブロックの縦横幅
	size_ = {
		((float(global.windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
		((float(global.windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
		((float(global.windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size()
	};

	puzzleMapSize_ = {
		size_.x * mapChip_[0].size(),
		size_.y * mapChip_.size()
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
			if (mapChip_[i][j] > 0) {
				rowTouchable.push_back(true);

				if (mapChip_[i][j] == 9) {
					firstPlayerPos_ = {
				size_.x + (j * size_.x) - (size_.x * 0.5f),
				size_.y + (i * size_.y) - (size_.y * 0.5f)
					};
				}

			} else {
				rowTouchable.push_back(false);
			}

			//各頂点の座標計算(3d)------------------------------------------------
			if (mapChip_[i][j] == 1 or mapChip_[i][j] == 2) {
				std::vector<Vec3>objVertex;
				float zRate = (5.0f / 3.0f);

				//手前 → 奥
				//LT,RT,LB,RB の順番

				//光源から見て手前-------------------------------
				objVertex.push_back(
					{//手前左上
						rowPos[j].x - (size_.x * 0.5f),
						rowPos[j].y + (size_.y * 0.5f),
						size_.z * (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
					}
				);

				objVertex.push_back(
					{//手前右上
						rowPos[j].x + (size_.x * 0.5f),
						rowPos[j].y + (size_.y * 0.5f),
						size_.z* (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
					}
				);

				objVertex.push_back(
					{//手前左下
						rowPos[j].x - (size_.x * 0.5f),
						rowPos[j].y + (size_.y * 0.5f),
						0
					}
				);

				objVertex.push_back(
					{//手前右下
						rowPos[j].x + (size_.x * 0.5f),
						rowPos[j].y + (size_.y * 0.5f),
						0
					}
				);

				//光源から見て奥-------------------------------
				objVertex.push_back(
					{//奥左上
						rowPos[j].x - (size_.x * 0.5f),
						rowPos[j].y - (size_.y * 0.5f),
						size_.z* (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
					}
				);

				objVertex.push_back(
					{//奥右上
						rowPos[j].x + (size_.x * 0.5f),
						rowPos[j].y - (size_.y * 0.5f),
						size_.z* (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
					}
				);

				objVertex.push_back(
					{//奥左下
						rowPos[j].x - (size_.x * 0.5f),
						rowPos[j].y - (size_.y * 0.5f),
						0
					}
				);

				objVertex.push_back(
					{//奥右下
						rowPos[j].x + (size_.x * 0.5f),
						rowPos[j].y - (size_.y * 0.5f),
						0
					}
				);

				//ひとつのブロックの頂点情報を格納
				vertex_.push_back(objVertex);
			}
		}

		pos_.push_back(rowPos);
		touchable_.push_back(rowTouchable);
	}


	//パズルマップの左上座標をいい感じに設定
	puzzleLeftTop_.x = (global.windowSize_.x * 0.5f) - (mapChip_[0].size() * size_.x) * 0.5f;
	puzzleLeftTop_.y = global.windowSize_.y - ((mapChip_.size() * size_.y) +((mapChip_.size() * size_.y) * 0.4f));
}

void Map::Update(char* keys,Global global) {


	//ENTERキーでホットリロードする
	if (keys[DIK_RETURN]) {
		
		//要素を消去
		pos_.clear();
		mapChip_.clear();
		touchable_.clear();
		vertex_.clear();

		//マップ読み込み
		mapChip_ = LoadFile("./Resources/mapChip.csv");
		//行を反転(ワールド座標表示のため)
	//	std::reverse(mapChip_.begin(), mapChip_.end());


		//ブロックの縦横幅
		size_ = {
			((float(global.windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
			((float(global.windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
			((float(global.windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size()
		};

		puzzleMapSize_ = {
			size_.x * mapChip_[0].size(),
			size_.y * mapChip_.size()
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
				if (mapChip_[i][j] > 0) {
					rowTouchable.push_back(true);

					if (mapChip_[i][j] == 9) {
						firstPlayerPos_ = {
					size_.x + (j * size_.x) - (size_.x * 0.5f),
					size_.y + (i * size_.y) - (size_.y * 0.5f)
						};
					}

				} else {
					rowTouchable.push_back(false);
				}

				//各頂点の座標計算(3d)------------------------------------------------
				if (mapChip_[i][j] == 1 or mapChip_[i][j] == 2) {
					std::vector<Vec3>objVertex;
					float zRate = (5.0f / 3.0f);

					//手前 → 奥
					//LT,RT,LB,RB の順番

					//光源から見て手前-------------------------------
					objVertex.push_back(
						{//手前左上
							rowPos[j].x - (size_.x * 0.5f),
							rowPos[j].y + (size_.y * 0.5f),
							size_.z * (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
						}
					);

					objVertex.push_back(
						{//手前右上
							rowPos[j].x + (size_.x * 0.5f),
							rowPos[j].y + (size_.y * 0.5f),
							size_.z * (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
						}
					);

					objVertex.push_back(
						{//手前左下
							rowPos[j].x - (size_.x * 0.5f),
							rowPos[j].y + (size_.y * 0.5f),
							0
						}
					);

					objVertex.push_back(
						{//手前右下
							rowPos[j].x + (size_.x * 0.5f),
							rowPos[j].y + (size_.y * 0.5f),
							0
						}
					);

					//光源から見て奥-------------------------------
					objVertex.push_back(
						{//奥左上
							rowPos[j].x - (size_.x * 0.5f),
							rowPos[j].y - (size_.y * 0.5f),
							size_.z * (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
						}
					);

					objVertex.push_back(
						{//奥右上
							rowPos[j].x + (size_.x * 0.5f),
							rowPos[j].y - (size_.y * 0.5f),
							size_.z * (1 + ((mapChip_[i][j] - 1) * (zRate - 1)))
						}
					);

					objVertex.push_back(
						{//奥左下
							rowPos[j].x - (size_.x * 0.5f),
							rowPos[j].y - (size_.y * 0.5f),
							0
						}
					);

					objVertex.push_back(
						{//奥右下
							rowPos[j].x + (size_.x * 0.5f),
							rowPos[j].y - (size_.y * 0.5f),
							0
						}
					);

					//ひとつのブロックの頂点情報を格納
					vertex_.push_back(objVertex);
				}
			}

			pos_.push_back(rowPos);
			touchable_.push_back(rowTouchable);
		}


		//パズルマップの左上座標をいい感じに設定
		puzzleLeftTop_.x = (global.windowSize_.x * 0.5f) - (mapChip_[0].size() * size_.x) * 0.5f;
		puzzleLeftTop_.y = global.windowSize_.y - ((mapChip_.size() * size_.y) + ((mapChip_.size() * size_.y) * 0.4f));
	}
};

void Map::Draw(Resources rs) {

	for (int row = 0; row < mapChip_.size(); row++) {
		for (int col = 0; col < mapChip_[0].size(); col++) {

			if (mapChip_[row][col] == 1) {

				Novice::DrawQuad(
					int(puzzleLeftTop_.x + pos_[row][col].x - size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y + size_.y * 0.5f),
					int(puzzleLeftTop_.x + pos_[row][col].x + size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y + size_.y * 0.5f),
					int(puzzleLeftTop_.x + pos_[row][col].x - size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y - size_.y * 0.5f),
					int(puzzleLeftTop_.x + pos_[row][col].x + size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y - size_.y * 0.5f),
					0, 0,
					1, 1,
					rs.whiteGH,
					0x0000ffff
				);
			
			}else if (mapChip_[row][col] == 2) {

				Novice::DrawQuad(
					int(puzzleLeftTop_.x + pos_[row][col].x - size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y + size_.y * 0.5f),
					int(puzzleLeftTop_.x + pos_[row][col].x + size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y + size_.y * 0.5f),
					int(puzzleLeftTop_.x + pos_[row][col].x - size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y - size_.y * 0.5f),
					int(puzzleLeftTop_.x + pos_[row][col].x + size_.x * 0.5f),
					int(puzzleLeftTop_.y + pos_[row][col].y - size_.y * 0.5f),
					0, 0,
					1, 1,
					rs.whiteGH,
					0x00ff00ff
				);
			}
		}
	}

	for (int row = 0; row < mapChip_.size() + 1; row++) {

		Novice::DrawLine(
			int(puzzleLeftTop_.x),
			int(puzzleLeftTop_.y + size_.y * row),
			int(puzzleLeftTop_.x + size_.x * mapChip_[0].size()),
			int(puzzleLeftTop_.y + size_.y * row),
			0xffffff77
		);
	}

	for (int col = 0; col < mapChip_[0].size() + 1; col++) {

		Novice::DrawLine(
			int(puzzleLeftTop_.x + size_.x * col),
			int(puzzleLeftTop_.y),
			int(puzzleLeftTop_.x + size_.x * col),
			int(puzzleLeftTop_.y + size_.y * mapChip_.size()),
			0xffffff77
		);
	}
}