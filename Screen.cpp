#include "Screen.h"

void Screen::Update(Map map, Light light) {

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
						map.GetPuzzleLeftTop().x + map.GetVertex(i,j).x,
						map.GetPuzzleLeftTop().y + map.GetVertex(i,j).y
					},
					map.GetPuzzleLeftTop(),
					{
						map.GetPuzzleLeftTop().x + 16,
						map.GetPuzzleLeftTop().y
					}
				).x,
				map.GetPuzzleLeftTop().y - (map.GetVertex(i,j).z * ((map.GetVertex(i,j).y / map.GetPuzzleMapSize().y) * 4.0f))
				}
			);

			//左にスクリーンアウトした時の処理
			if (j == 1) {
				if (objVertex[1].x < LRTB_.x) {
					objVertex[1] = CrossPos(
						{ map.GetPuzzleLeftTop().x + map.GetVertex(i,7).x,
						 map.GetPuzzleLeftTop().y + map.GetVertex(i,7).y},
						light.GetEmitPos(),
						{ map.GetPuzzleLeftTop().x,map.GetPuzzleLeftTop().y },
						{ map.GetPuzzleLeftTop().x,map.GetPuzzleLeftTop().y + 8 }
					);

					//objVertex[3].x = objVertex[1].x;
				}
			}


			//右にスクリーンアウトした時の処理
			/*if (j == 4) {
				if (objVertex[0].x > LRTB_.y) {
					objVertex[0] = CrossPos(
						objVertex[0],
						objVertex[4],
						{ LRTB_.y,LRTB_.z },
						{ LRTB_.y,LRTB_.w }
					);

					objVertex[2].x = objVertex[0].x;
				}
			}*/
			if (j == 0) {
				if (objVertex[0].x > LRTB_.y) {
					objVertex[0] = CrossPos(
						{ map.GetPuzzleLeftTop().x + map.GetVertex(i,6).x,
						 map.GetPuzzleLeftTop().y + map.GetVertex(i,6).y},
						light.GetEmitPos(),
						{ LRTB_.y,map.GetPuzzleLeftTop().y },
						{ LRTB_.y,map.GetPuzzleLeftTop().y + 8 }
					);

					//objVertex[3].x = objVertex[1].x;
				}
			}


		}

		for (int j = 0; j < map.GetVertex()[i].size(); j++) {

			if (objVertex[j].x < LRTB_.x) {
				objVertex[j].x = LRTB_.x;
				objVertex[0].y = objVertex[1].y;
			}

			if (objVertex[j].x > LRTB_.y) {
				objVertex[j].x = LRTB_.y;
				objVertex[1].y = objVertex[0].y;
			}
		}

		boxPos_.push_back(objVertex);
	}
};

void Screen::Draw(Map map, Resources rs, Light light) {

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
		rs.whiteGH,
		0xffffffff
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
			rs.whiteGH,
			0x000000ff
		);

		/*Novice::DrawQuad(
			int(boxPos_[i][1].x),
			int(boxPos_[i][1].y),
			int(boxPos_[i][3].x),
			int(boxPos_[i][3].y),
			int(boxPos_[i][5].x),
			int(boxPos_[i][5].y),
			int(boxPos_[i][7].x),
			int(boxPos_[i][7].y),
			0, 0,
			1, 1,
			rs.whiteGH,
			0x000000ff
		);

		Novice::DrawQuad(
			int(boxPos_[i][0].x),
			int(boxPos_[i][0].y),
			int(boxPos_[i][2].x),
			int(boxPos_[i][2].y),
			int(boxPos_[i][4].x),
			int(boxPos_[i][4].y),
			int(boxPos_[i][6].x),
			int(boxPos_[i][6].y),
			0, 0,
			1, 1,
			rs.whiteGH,
			0x000000ff
		);*/

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
			{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][2].x,
			map.GetPuzzleLeftTop().y + map.GetVertex()[i][2].y },
			light.GetEmitPos(),
			map.GetPuzzleLeftTop(),
			{ float(map.GetPuzzleLeftTop().x + 8),
			float(map.GetPuzzleLeftTop().y) }
		);

		bellowShadowCrossPos[1] = CrossPos(
			{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][6].x,
			map.GetPuzzleLeftTop().y + map.GetVertex()[i][6].y },
			light.GetEmitPos(),
			map.GetPuzzleLeftTop(),
			{ float(map.GetPuzzleLeftTop().x + 8),
			float(map.GetPuzzleLeftTop().y) }
		);

		bellowShadowCrossPos[2] = CrossPos(
			{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][3].x,
			map.GetPuzzleLeftTop().y + map.GetVertex()[i][3].y },
			light.GetEmitPos(),
			map.GetPuzzleLeftTop(),
			{ float(map.GetPuzzleLeftTop().x + 8),
			float(map.GetPuzzleLeftTop().y) }
		);

		bellowShadowCrossPos[3] = CrossPos(
			{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][7].x,
			map.GetPuzzleLeftTop().y + map.GetVertex()[i][7].y },
			light.GetEmitPos(),
			map.GetPuzzleLeftTop(),
			{ float(map.GetPuzzleLeftTop().x + 8),
			float(map.GetPuzzleLeftTop().y) }
		);



		//左右の縦線との交点を新しい座標にする
		//左に出た時
		if (bellowShadowCrossPos[0].x < LRTB_.x) {

			bellowShadowCrossPos[0] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][2].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][2].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x),
				float(map.GetPuzzleLeftTop().y + 8) }
			);

		} else if (bellowShadowCrossPos[0].x > LRTB_.y) {

			bellowShadowCrossPos[0] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][2].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][2].y },
				light.GetEmitPos(),
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y) },
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y + 8) }
			);
		}

		if (bellowShadowCrossPos[1].x < LRTB_.x) {

			bellowShadowCrossPos[1] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][6].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][6].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x),
				float(map.GetPuzzleLeftTop().y + 8) }
			);

		} else if (bellowShadowCrossPos[1].x > LRTB_.y) {

			bellowShadowCrossPos[1] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][6].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][6].y },
				light.GetEmitPos(),
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y) },
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y + 8) }
			);
		}

		if (bellowShadowCrossPos[2].x < LRTB_.x) {

			bellowShadowCrossPos[2] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][3].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][3].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x),
				float(map.GetPuzzleLeftTop().y + 8) }
			);

		} else if (bellowShadowCrossPos[2].x > LRTB_.y) {

			bellowShadowCrossPos[2] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][3].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][3].y },
				light.GetEmitPos(),
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y) },
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y + 8) }
			);
		}

		if (bellowShadowCrossPos[3].x < LRTB_.x) {

			bellowShadowCrossPos[3] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][7].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][7].y },
				light.GetEmitPos(),
				map.GetPuzzleLeftTop(),
				{ float(map.GetPuzzleLeftTop().x),
				float(map.GetPuzzleLeftTop().y + 8) }
			);

		} else if (bellowShadowCrossPos[3].x > LRTB_.y) {

			bellowShadowCrossPos[3] = CrossPos(
				{ map.GetPuzzleLeftTop().x + map.GetVertex()[i][7].x,
				map.GetPuzzleLeftTop().y + map.GetVertex()[i][7].y },
				light.GetEmitPos(),
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y) },
				{ float(LRTB_.y),
				float(map.GetPuzzleLeftTop().y + 8) }
			);
		}

		//描画--------------------------------------------------------


		Novice::DrawQuad(
			int(map.GetPuzzleLeftTop().x + map.GetVertex()[i][6].x),
			int(map.GetPuzzleLeftTop().y + map.GetVertex()[i][6].y),
			int(map.GetPuzzleLeftTop().x + map.GetVertex()[i][7].x),
			int(map.GetPuzzleLeftTop().y + map.GetVertex()[i][7].y),
			int(bellowShadowCrossPos[1].x),
			int(bellowShadowCrossPos[1].y),
			int(bellowShadowCrossPos[3].x),
			int(bellowShadowCrossPos[3].y),
			0, 0,
			1, 1,
			rs.whiteGH,
			0x0000ffff
		);


		//左右の矩形
		Novice::DrawQuad(
			int(map.GetPuzzleLeftTop().x + map.GetVertex()[i][2].x),
			int(map.GetPuzzleLeftTop().y + map.GetVertex()[i][2].y),
			int(map.GetPuzzleLeftTop().x + map.GetVertex()[i][6].x),
			int(map.GetPuzzleLeftTop().y + map.GetVertex()[i][6].y),
			int(bellowShadowCrossPos[0].x),
			int(bellowShadowCrossPos[0].y),
			int(bellowShadowCrossPos[1].x),
			int(bellowShadowCrossPos[1].y),
			0, 0,
			1, 1,
			rs.whiteGH,
			0x0000ffff
		);

		Novice::DrawQuad(
			int(map.GetPuzzleLeftTop().x + map.GetVertex()[i][3].x),
			int(map.GetPuzzleLeftTop().y + map.GetVertex()[i][3].y),
			int(map.GetPuzzleLeftTop().x + map.GetVertex()[i][7].x),
			int(map.GetPuzzleLeftTop().y + map.GetVertex()[i][7].y),
			int(bellowShadowCrossPos[2].x),
			int(bellowShadowCrossPos[2].y),
			int(bellowShadowCrossPos[3].x),
			int(bellowShadowCrossPos[3].y),
			0, 0,
			1, 1,
			rs.whiteGH,
			0x0000ffff
		);


		//隙間を補完する三角形
		Novice::DrawTriangle(
			int(bellowShadowCrossPos[0].x),
			int(bellowShadowCrossPos[0].y),
			int(bellowShadowCrossPos[1].x),
			int(bellowShadowCrossPos[1].y),
			int(boxPos_[i][2].x),
			int(boxPos_[i][2].y),
			0x0000ffff,
			kFillModeSolid
		);

		Novice::DrawTriangle(
			int(bellowShadowCrossPos[2].x),
			int(bellowShadowCrossPos[2].y),
			int(bellowShadowCrossPos[3].x),
			int(bellowShadowCrossPos[3].y),
			int(boxPos_[i][3].x),
			int(boxPos_[i][3].y),
			0x0000ffff,
			kFillModeSolid
		);

		Novice::DrawTriangle(
			int(bellowShadowCrossPos[1].x),
			int(bellowShadowCrossPos[1].y),
			int(boxPos_[i][7].x),
			int(boxPos_[i][7].y),
			int(boxPos_[i][2].x),
			int(boxPos_[i][2].y),
			0x0000ffff,
			kFillModeSolid
		);

		Novice::DrawTriangle(
			int(bellowShadowCrossPos[3].x),
			int(bellowShadowCrossPos[3].y),
			int(boxPos_[i][3].x),
			int(boxPos_[i][3].y),
			int(boxPos_[i][6].x),
			int(boxPos_[i][6].y),
			0x0000ffff,
			kFillModeSolid
		);

	}
}