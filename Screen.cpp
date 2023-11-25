#include "Screen.h"

void Screen::Init(int sceneNum, Map map, Light light) {

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

		boxPos_.clear();
		preBoxPos_.clear();

		size_ = {
		map.GetPuzzleMapSize().x,
		map.GetPuzzleMapSize().y * 2.0f
		};

		centerPos_ = {
		map.GetPuzzleLeftTop().x + (map.GetPuzzleMapSize().x * 0.5f),
		map.GetPuzzleLeftTop().y - (map.GetPuzzleMapSize().y * 0.5f)
		};


		LRTB_ = {
			map.GetPuzzleLeftTop().x,//left
			map.GetPuzzleLeftTop().x + size_.x,//right
			map.GetPuzzleLeftTop().y - size_.y,//top
			map.GetPuzzleLeftTop().y//bottom
		};

		leftTop_ = { LRTB_.x,LRTB_.z };


		for (int i = 0; i < map.GetVertex().size(); i++) {
			std::vector<Vec2>objVertex;
			for (int j = 0; j < map.GetVertex()[i].size(); j++) {

				//手前 → 奥
				//LT,RT,LB,RB の順番

				//光源から見て手前-------------------------------
				objVertex.push_back(
					{//左上
					CrossPos(
						light.GetEmitPos(),
						{
							map.GetVertex(i,j).x,
							map.GetVertex(i,j).y
						},
						map.GetPuzzleLeftTop(),
						{
							map.GetPuzzleLeftTop().x + 16,
							map.GetPuzzleLeftTop().y
						}
					).x,
					map.GetPuzzleLeftTop().y
					- (map.GetVertex(i,j).z * (((map.GetVertex(i,j).y - map.GetPuzzleLeftTop().y) / map.GetPuzzleMapSize().y) * 4.0f))
					}
				);
			}

			boxPos_.push_back(objVertex);
		}

		

		preBoxPos_ = boxPos_;

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}

}

void Screen::Update(char* keys, const ChangeScene& cs, Map map, Light light) {

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(Scene::sceneNum_, map, light);
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
			Init(Scene::sceneNum_, map, light);
		}
					
		preBoxPos_ = boxPos_;

		boxPos_.clear();

		//描画する座標決定
		for (int i = 0; i < map.GetVertex().size(); i++) {
			std::vector<Vec2>objVertex;
			for (int j = 0; j < map.GetVertex()[i].size(); j++) {

				//手前 → 奥
				//LT,RT,LB,RB の順番

				//光源から見て手前-------------------------------
				objVertex.push_back(
					{//左上
					CrossPos(
						light.GetEmitPos(),
						{
							map.GetVertex(i,j).x,
							map.GetVertex(i,j).y
						},
						map.GetPuzzleLeftTop(),
						{
							map.GetPuzzleLeftTop().x + 16,
							map.GetPuzzleLeftTop().y
						}
					).x,
					map.GetPuzzleLeftTop().y
					- (map.GetVertex(i,j).z * (((map.GetVertex(i,j).y - map.GetPuzzleLeftTop().y) / map.GetPuzzleMapSize().y) * 4.0f))
					}
				);
			}

			boxPos_.push_back(objVertex);
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

void Screen::Draw(Map map, const Resources& rs, Light light) {

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

		Novice::DrawQuad(
			int(LRTB_.x),
			int(LRTB_.z),
			int(LRTB_.y),
			int(LRTB_.z),
			int(LRTB_.x),
			int(LRTB_.w),
			int(LRTB_.y),
			int(LRTB_.w),
			0, 0,
			1, 1,
			rs.whiteGH_,
			0xbbbbbbff
		);


		for (int i = 0; i < boxPos_.size(); i++) {

			Novice::DrawQuad(
				int(boxPos_[i][0].x),
				int(boxPos_[i][0].y),
				int(boxPos_[i][1].x),
				int(boxPos_[i][1].y),
				int(boxPos_[i][2].x),
				int(boxPos_[i][2].y),
				int(boxPos_[i][3].x),
				int(boxPos_[i][3].y),
				0, 0,
				1, 1,
				rs.whiteGH_,
				0x000000ff
			);


			Novice::DrawTriangle(
				int(boxPos_[i][1].x),
				int(boxPos_[i][1].y),
				int(boxPos_[i][3].x),
				int(boxPos_[i][3].y),
				int(boxPos_[i][7].x),
				int(boxPos_[i][7].y),
				0x000000ff,
				kFillModeSolid
			);

			Novice::DrawTriangle(
				int(boxPos_[i][0].x),
				int(boxPos_[i][0].y),
				int(boxPos_[i][2].x),
				int(boxPos_[i][2].y),
				int(boxPos_[i][6].x),
				int(boxPos_[i][6].y),
				0x000000ff,
				kFillModeSolid
			);

			//=======================================================================
			//                          地面に落ちる影
			//=======================================================================

			//交点を求める------------------------------------------------
			Vec2 bellowShadowCrossPos[4] = { 0.0f };

			bellowShadowCrossPos[0] = CrossPos(
				{ map.GetVertex()[i][2].x,
				map.GetVertex()[i][2].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x + 8),
				float(map.GetPuzzleLeftTop().y) }
			);

			bellowShadowCrossPos[1] = CrossPos(
				{ map.GetVertex()[i][6].x,
				map.GetVertex()[i][6].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x + 8),
				float(map.GetPuzzleLeftTop().y) }
			);

			bellowShadowCrossPos[2] = CrossPos(
				{ map.GetVertex()[i][3].x,
				map.GetVertex()[i][3].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x + 8),
				float(map.GetPuzzleLeftTop().y) }
			);

			bellowShadowCrossPos[3] = CrossPos(
				{ map.GetVertex()[i][7].x,
				map.GetVertex()[i][7].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x + 8),
				float(map.GetPuzzleLeftTop().y) }
			);



			//左右の縦線との交点を新しい座標にする
			//左に出た時
			if (bellowShadowCrossPos[0].x < LRTB_.x) {

				bellowShadowCrossPos[0] = CrossPos(
					{ map.GetVertex()[i][2].x,
					map.GetVertex()[i][2].y },
					light.GetEmitPos(),
					map.GetPuzzleLeftTop(),
					{ float(map.GetPuzzleLeftTop().x),
					float(map.GetPuzzleLeftTop().y + 8) }
				);

			} else if (bellowShadowCrossPos[0].x > LRTB_.y) {

				bellowShadowCrossPos[0] = CrossPos(
					{ map.GetVertex()[i][2].x,
					map.GetVertex()[i][2].y },
					light.GetEmitPos(),
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y) },
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y + 8) }
				);
			}

			if (bellowShadowCrossPos[1].x < LRTB_.x) {

				bellowShadowCrossPos[1] = CrossPos(
					{ map.GetVertex()[i][6].x,
					map.GetVertex()[i][6].y },
					light.GetEmitPos(),
					map.GetPuzzleLeftTop(),
					{ float(map.GetPuzzleLeftTop().x),
					float(map.GetPuzzleLeftTop().y + 8) }
				);

			} else if (bellowShadowCrossPos[1].x > LRTB_.y) {

				bellowShadowCrossPos[1] = CrossPos(
					{ map.GetVertex()[i][6].x,
					map.GetVertex()[i][6].y },
					light.GetEmitPos(),
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y) },
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y + 8) }
				);
			}

			if (bellowShadowCrossPos[2].x < LRTB_.x) {

				bellowShadowCrossPos[2] = CrossPos(
					{ map.GetVertex()[i][3].x,
					map.GetVertex()[i][3].y },
					light.GetEmitPos(),
					map.GetPuzzleLeftTop(),
					{ float(map.GetPuzzleLeftTop().x),
					float(map.GetPuzzleLeftTop().y + 8) }
				);

			} else if (bellowShadowCrossPos[2].x > LRTB_.y) {

				bellowShadowCrossPos[2] = CrossPos(
					{ map.GetVertex()[i][3].x,
					map.GetVertex()[i][3].y },
					light.GetEmitPos(),
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y) },
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y + 8) }
				);
			}

			if (bellowShadowCrossPos[3].x < LRTB_.x) {

				bellowShadowCrossPos[3] = CrossPos(
					{ map.GetVertex()[i][7].x,
					map.GetVertex()[i][7].y },
					light.GetEmitPos(),
					map.GetPuzzleLeftTop(),
					{ float(map.GetPuzzleLeftTop().x),
					float(map.GetPuzzleLeftTop().y + 8) }
				);

			} else if (bellowShadowCrossPos[3].x > LRTB_.y) {

				bellowShadowCrossPos[3] = CrossPos(
					{ map.GetVertex()[i][7].x,
					map.GetVertex()[i][7].y },
					light.GetEmitPos(),
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y) },
					{ float(LRTB_.y),
					float(map.GetPuzzleLeftTop().y + 8) }
				);
			}

			//描画--------------------------------------------------------

			Novice::DrawQuad(
				int(map.GetVertex()[i][6].x),
				int(map.GetVertex()[i][6].y),
				int(map.GetVertex()[i][7].x),
				int(map.GetVertex()[i][7].y),
				int(bellowShadowCrossPos[1].x),
				int(bellowShadowCrossPos[1].y),
				int(bellowShadowCrossPos[3].x),
				int(bellowShadowCrossPos[3].y),
				0, 0,
				1, 1,
				rs.whiteGH_,
				0x666666ff
			);


			//左右の矩形
			Novice::DrawQuad(
				int(map.GetVertex()[i][2].x),
				int(map.GetVertex()[i][2].y),
				int(map.GetVertex()[i][6].x),
				int(map.GetVertex()[i][6].y),
				int(bellowShadowCrossPos[0].x),
				int(bellowShadowCrossPos[0].y),
				int(bellowShadowCrossPos[1].x),
				int(bellowShadowCrossPos[1].y),
				0, 0,
				1, 1,
				rs.whiteGH_,
				0x666666ff
			);

			Novice::DrawQuad(
				int(map.GetVertex()[i][3].x),
				int(map.GetVertex()[i][3].y),
				int(map.GetVertex()[i][7].x),
				int(map.GetVertex()[i][7].y),
				int(bellowShadowCrossPos[2].x),
				int(bellowShadowCrossPos[2].y),
				int(bellowShadowCrossPos[3].x),
				int(bellowShadowCrossPos[3].y),
				0, 0,
				1, 1,
				rs.whiteGH_,
				0x666666ff
			);


			//隙間を補完する三角形
			Novice::DrawTriangle(
				int(bellowShadowCrossPos[0].x),
				int(bellowShadowCrossPos[0].y),
				int(bellowShadowCrossPos[1].x),
				int(bellowShadowCrossPos[1].y),
				int(boxPos_[i][2].x),
				int(boxPos_[i][2].y),
				0x666666ff,
				kFillModeSolid
			);

			Novice::DrawTriangle(
				int(bellowShadowCrossPos[2].x),
				int(bellowShadowCrossPos[2].y),
				int(bellowShadowCrossPos[3].x),
				int(bellowShadowCrossPos[3].y),
				int(boxPos_[i][3].x),
				int(boxPos_[i][3].y),
				0x666666ff,
				kFillModeSolid
			);

			Novice::DrawTriangle(
				int(bellowShadowCrossPos[1].x),
				int(bellowShadowCrossPos[1].y),
				int(boxPos_[i][7].x),
				int(boxPos_[i][7].y),
				int(boxPos_[i][2].x),
				int(boxPos_[i][2].y),
				0x666666ff,
				kFillModeSolid
			);

			Novice::DrawTriangle(
				int(bellowShadowCrossPos[3].x),
				int(bellowShadowCrossPos[3].y),
				int(boxPos_[i][3].x),
				int(boxPos_[i][3].y),
				int(boxPos_[i][6].x),
				int(boxPos_[i][6].y),
				0x666666ff,
				kFillModeSolid
			);
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