#include "Map.h"

int Map::stageNum_ = 0;

//コンストラクタ============================================================================================
Map::Map(const Resources& rs) {

	stageNum_ = 1;

	//要素を消去
	pos_.clear();
	posCopy_.clear();
	mapChip_.clear();
	mapChipCopy_.clear();
	touchable_.clear();
	vertex_.clear();

	//マップ読み込み
	mapChip_ = LoadFile(rs.mapCsv_[stageNum_]);
	//行を反転(ワールド座標表示のため)
//	std::reverse(mapChip_.begin(), mapChip_.end());


	//ブロックの縦横幅
	size_ = {
		((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
		((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
		((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size()
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
			if (mapChip_[i][j] == -1) {
				firstPlayerPos_ = {
			size_.x + (j * size_.x) - (size_.x * 0.5f),
			size_.y + (i * size_.y) - (size_.y * 0.5f)
				};
			}

			if (mapChip_[i][j] >= 0) {
				rowTouchable.push_back(true);

			} else {
				rowTouchable.push_back(false);
			}

			//各頂点の座標計算(3d)------------------------------------------------
			if (mapChip_[i][j] == 1 or mapChip_[i][j] == 2) {
				std::vector<Vec3>objVertex;
				float zRate = 2;

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
	puzzleLeftTop_.x = (Global::windowSize_.x * 0.5f) - (mapChip_[0].size() * size_.x) * 0.5f;
	puzzleLeftTop_.y = Global::windowSize_.y - ((mapChip_.size() * size_.y) + ((mapChip_.size() * size_.y) * 0.4f));

	//読み込んだマップチップの情報決定
	for (int i = 0; i < mapChip_.size(); i++) {
		for (int j = 0; j < mapChip_[0].size(); j++) {

			pos_[i][j].x += puzzleLeftTop_.x;
			pos_[i][j].y += puzzleLeftTop_.y;

		}
	}

	for (int i = 0; i < vertex_.size(); i++) {
		for (int j = 0; j < vertex_[0].size(); j++) {

			vertex_[i][j].x += puzzleLeftTop_.x;
			vertex_[i][j].y += puzzleLeftTop_.y;

		}
	}

	//スイッチが押されたかのフラグ
	isPressSwitch_ = false;


	mapChipCopy_ = mapChip_;
	posCopy_ = pos_;
}


//=========================================================初期化関数==============================================================
void Map::Init(const Resources& rs, int sceneNum) {

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

		//要素を消去
		pos_.clear();
		posCopy_.clear();
		mapChip_.clear();
		mapChipCopy_.clear();
		touchable_.clear();
		vertex_.clear();

		//マップ読み込み
		mapChip_ = LoadFile(rs.mapCsv_[stageNum_]);
		//行を反転(ワールド座標表示のため)
	//	std::reverse(mapChip_.begin(), mapChip_.end());


		//ブロックの縦横幅
		size_ = {
			((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
			((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size(),
			((float(Global::windowSize_.x) / 4.0f) * 3.0f) / mapChip_[0].size()
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
				if (mapChip_[i][j] == -1) {
					firstPlayerPos_ = {
				size_.x + (j * size_.x) - (size_.x * 0.5f),
				size_.y + (i * size_.y) - (size_.y * 0.5f)
					};
				}

				if (mapChip_[i][j] >= 0) {
					rowTouchable.push_back(true);

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
		puzzleLeftTop_.x = (Global::windowSize_.x * 0.5f) - (mapChip_[0].size() * size_.x) * 0.5f;
		puzzleLeftTop_.y = Global::windowSize_.y - ((mapChip_.size() * size_.y) + ((mapChip_.size() * size_.y) * 0.4f));

		//読み込んだマップチップの情報決定
		for (int i = 0; i < mapChip_.size(); i++) {
			for (int j = 0; j < mapChip_[0].size(); j++) {

				pos_[i][j].x += puzzleLeftTop_.x;
				pos_[i][j].y += puzzleLeftTop_.y;

			}
		}

		for (int i = 0; i < vertex_.size(); i++) {
			for (int j = 0; j < vertex_[0].size(); j++) {

				vertex_[i][j].x += puzzleLeftTop_.x;
				vertex_[i][j].y += puzzleLeftTop_.y;

			}
		}

		//スイッチが押されたかのフラグ
		isPressSwitch_ = false;

		mapChipCopy_ = mapChip_;
		posCopy_ = pos_;

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}


//====================================================アップデート=============================================================
void Map::Update(char* keys, const Resources& rs, const ChangeScene cs) {

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(rs, Scene::sceneNum_);
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
			Init(rs, Scene::sceneNum_);
		}

		//falseで初期化
		isPressSwitch_ = false;

		//要素を消去	
		touchable_.clear();
		vertex_.clear();

		//マップチップの情報更新
		for (int i = 0; i < mapChip_.size(); i++) {

			std::vector<Vec2>rowPos;
			std::vector<bool>rowTouchable;

			for (int j = 0; j < mapChip_[0].size(); j++) {

				//座標決定
				rowPos.push_back(pos_[i][j]);

				//存在フラグ決定
				if (mapChip_[i][j] == -1) {
					firstPlayerPos_ = {
				size_.x + (j * size_.x) - (size_.x * 0.5f),
				size_.y + (i * size_.y) - (size_.y * 0.5f)
					};
				}

				if (mapChip_[i][j] > 0) {
					rowTouchable.push_back(true);

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

			touchable_.push_back(rowTouchable);
		}

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}

};


//====================================================描画=============================================================
void Map::DrawBG(const Resources& rs) {

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

		Novice::DrawBox(
			0,
			0,
			Global::windowSize_.x,
			Global::windowSize_.y,
			0.0f,
			0x000000ff,
			kFillModeSolid
		);

		for (int row = 0; row < mapChip_.size(); row++) {
			for (int col = 0; col < mapChip_[0].size(); col++) {
				//地面
				Novice::DrawQuad(
					int(posCopy_[row][col].x - size_.x * 0.5f),
					int(posCopy_[row][col].y - size_.y * 0.5f),
					int(posCopy_[row][col].x + size_.x * 0.5f),
					int(posCopy_[row][col].y - size_.y * 0.5f),
					int(posCopy_[row][col].x - size_.x * 0.5f),
					int(posCopy_[row][col].y + size_.y * 0.5f),
					int(posCopy_[row][col].x + size_.x * 0.5f),
					int(posCopy_[row][col].y + size_.y * 0.5f),
					0, 0,
					64, 64,
					rs.blockGH_[5],
					0xffffffff
				);
			}
		}

		Novice::SetBlendMode(kBlendModeMultily);
		Novice::DrawQuad(
			int(puzzleLeftTop_.x),
			int(puzzleLeftTop_.y),
			int(puzzleLeftTop_.x + puzzleMapSize_.x),
			int(puzzleLeftTop_.y),
			int(puzzleLeftTop_.x),
			int(puzzleLeftTop_.y + puzzleMapSize_.y),
			int(puzzleLeftTop_.x + puzzleMapSize_.x),
			int(puzzleLeftTop_.y + puzzleMapSize_.y),
			0, 0,
			800, 450,
			rs.textureGH_[1],
			0xffffff3f
		);
		Novice::SetBlendMode(kBlendModeNormal);


			break;
			//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
		}

	};

	void Map::Draw(const Resources & rs) {

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

			for (int row = 0; row < mapChip_.size(); row++) {
				for (int col = 0; col < mapChip_[0].size(); col++) {
					if (mapChip_[row][col] == 1) {


						Novice::DrawQuad(
							int(pos_[row][col].x - size_.x * 0.5f),
							int(pos_[row][col].y - size_.y * 0.5f),
							int(pos_[row][col].x + size_.x * 0.5f),
							int(pos_[row][col].y - size_.y * 0.5f),
							int(pos_[row][col].x - size_.x * 0.5f),
							int(pos_[row][col].y + size_.y * 0.5f),
							int(pos_[row][col].x + size_.x * 0.5f),
							int(pos_[row][col].y + size_.y * 0.5f),
							0, 0,
							64, 64,
							rs.blockGH_[0],
							0xffffffff
						);

					} else if (mapChip_[row][col] == 2) {

						Novice::DrawQuad(
							int(pos_[row][col].x - size_.x * 0.5f),
							int(pos_[row][col].y - size_.y * 0.5f),
							int(pos_[row][col].x + size_.x * 0.5f),
							int(pos_[row][col].y - size_.y * 0.5f),
							int(pos_[row][col].x - size_.x * 0.5f),
							int(pos_[row][col].y + size_.y * 0.5f),
							int(pos_[row][col].x + size_.x * 0.5f),
							int(pos_[row][col].y + size_.y * 0.5f),
							0, 0,
							64, 64,
							rs.blockGH_[1],
							0xffffffff
						);

					} else if (mapChip_[row][col] == 8) {

						//穴が開いて通れない地面
						Novice::DrawQuad(
							int(pos_[row][col].x - size_.x * 0.5f),
							int(pos_[row][col].y - size_.y * 0.5f),
							int(pos_[row][col].x + size_.x * 0.5f),
							int(pos_[row][col].y - size_.y * 0.5f),
							int(pos_[row][col].x - size_.x * 0.5f),
							int(pos_[row][col].y + size_.y * 0.5f),
							int(pos_[row][col].x + size_.x * 0.5f),
							int(pos_[row][col].y + size_.y * 0.5f),
							0, 0,
							64, 64,
							rs.blockGH_[2],
							0xffffffff
						);

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

	void Map::DrawSwitch(const Resources& rs) {
	
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

			for (int row = 0; row < mapChip_.size(); row++) {
				for (int col = 0; col < mapChip_[0].size(); col++) {

					if (mapChipCopy_[row][col] == -2) {

						//スイッチ
						if (!isPressSwitch_) {
							Novice::DrawQuad(
								int(posCopy_[row][col].x - size_.x * 0.5f),
								int(posCopy_[row][col].y - size_.y * 0.5f),
								int(posCopy_[row][col].x + size_.x * 0.5f),
								int(posCopy_[row][col].y - size_.y * 0.5f),
								int(posCopy_[row][col].x - size_.x * 0.5f),
								int(posCopy_[row][col].y + size_.y * 0.5f),
								int(posCopy_[row][col].x + size_.x * 0.5f),
								int(posCopy_[row][col].y + size_.y * 0.5f),
								0, 0,
								64, 64,
								rs.blockGH_[3],
								0xffffffff
							);
						} else {
							Novice::DrawQuad(
								int(posCopy_[row][col].x - size_.x * 0.5f),
								int(posCopy_[row][col].y - size_.y * 0.5f),
								int(posCopy_[row][col].x + size_.x * 0.5f),
								int(posCopy_[row][col].y - size_.y * 0.5f),
								int(posCopy_[row][col].x - size_.x * 0.5f),
								int(posCopy_[row][col].y + size_.y * 0.5f),
								int(posCopy_[row][col].x + size_.x * 0.5f),
								int(posCopy_[row][col].y + size_.y * 0.5f),
								0, 0,
								64, 64,
								rs.blockGH_[4],
								0xffffffff
							);
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
