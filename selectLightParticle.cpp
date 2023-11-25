#include "selectLightParticle.h"


void SelectLightParticle::Init(float theta, Vec2 pos, float radius, float speed) {
	theta_ = theta;
	pos_ = pos;
	radius_ = radius;
	speed_ = speed;
}



void SelectLightParticle::Update(const SelectDoor& Door) {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		DrawStartPos = { Door.NumlightEllCPos_.x,0 };
		DrawEndPosL = { Door.NumlightEllCPos_.x - Door.NumlightEllSize_.x,Door.NumlightEllCPos_.y };
		DrawEndPosR = { Door.NumlightEllCPos_.x + Door.NumlightEllSize_.x,Door.NumlightEllCPos_.y };


		//particle初期化
		if (!isAlive_) {
			Init(
				float(rand() % 100) / 100,
				{ float(rand() % Global::windowSize_.x),float(rand() % Global::windowSize_.y) },
				float(rand() % 200) / 100,
				radius_
			);
			isAlive_ = true;
		
		} else {//

			//lightの範囲内でだけ表示
			if (NoInitCross(DrawStartPos, DrawEndPosL, pos_) < 0 &&
				NoInitCross(DrawStartPos, DrawEndPosR, pos_) > 0) {

				isDraw = true;

			} else {//範囲外

				isDraw = false;
			}


			pos_.x += theta_ * speed_;
			pos_.y += theta_ * speed_;
		}



		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}

}
void SelectLightParticle::Draw() {
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		My::DrawTriangle(
			pos_,radius_,0.0f,0xFFFFFFFF
		);
		//	void DrawTriangle(Vec2 center, float radius, float theta, int color);

		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}


}