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

			objVertex[7] = CrossPos(
				objVertex[1],
				{
					map.GetVertex(i,5).x,
					map.GetVertex(i,5).y
				},
				map.GetPuzzleLeftTop(),
				{
					map.GetPuzzleLeftTop().x + 16,
					map.GetPuzzleLeftTop().y
				}
			);

			objVertex[6] = CrossPos(
				objVertex[0],
				{
					map.GetVertex(i,4).x,
					map.GetVertex(i,4).y
				},
				map.GetPuzzleLeftTop(),
				{
					map.GetPuzzleLeftTop().x + 16,
					map.GetPuzzleLeftTop().y
				}
			);

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


			Vec2 drawScreenUnderShadowPos[2] = { 0.0f };

			if (boxPos_[i][2].x > boxPos_[i][6].x) {
				drawScreenUnderShadowPos[0] = boxPos_[i][6];
			} else {
				drawScreenUnderShadowPos[0] = boxPos_[i][2];
			}

			if (boxPos_[i][3].x < boxPos_[i][7].x) {
				drawScreenUnderShadowPos[1] = boxPos_[i][7];
			} else {
				drawScreenUnderShadowPos[1] = boxPos_[i][3];
			}

			Novice::DrawQuad(
				int(boxPos_[i][0].x),
				int(boxPos_[i][0].y),
				int(boxPos_[i][1].x),
				int(boxPos_[i][1].y),
				int(drawScreenUnderShadowPos[0].x),
				int(drawScreenUnderShadowPos[0].y),
				int(drawScreenUnderShadowPos[1].x),
				int(drawScreenUnderShadowPos[1].y),
				0, 0,
				1, 1,
				rs.whiteGH_,
				0x000000ff
			);

			//=======================================================================
			//                          地面に落ちる影
			//=======================================================================
		
			Vec2 drawShadowPos[4] = { 0.0f };
		if(map.GetVertex()[i][0].x > boxPos_[i][2].x) {
		
			drawShadowPos[0] = boxPos_[i][2];
			drawShadowPos[2] = { map.GetVertex()[i][0].x,map.GetVertex()[i][0].y };
		} else {
			drawShadowPos[0] = boxPos_[i][6];
			drawShadowPos[2] = { map.GetVertex()[i][4].x,map.GetVertex()[i][4].y };
		}

		if (map.GetVertex()[i][1].x < boxPos_[i][3].x) {

			drawShadowPos[1] = boxPos_[i][3];
			drawShadowPos[3] = { map.GetVertex()[i][1].x,map.GetVertex()[i][1].y };
		} else {
			drawShadowPos[1] = boxPos_[i][7];
			drawShadowPos[3] = { map.GetVertex()[i][5].x,map.GetVertex()[i][5].y };
		}

		Novice::DrawQuad(
			int(drawShadowPos[0].x),
			int(drawShadowPos[0].y),
			int(drawShadowPos[1].x),
			int(drawShadowPos[1].y),
			int(drawShadowPos[2].x),
			int(drawShadowPos[2].y),
			int(drawShadowPos[3].x),
			int(drawShadowPos[3].y),
			0, 0,
			1, 1,
			rs.whiteGH_,
			0x0000007f
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