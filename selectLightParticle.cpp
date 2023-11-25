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
		DrawStartPos = { Door.NumlightEllCPos_.x,-300 };
		DrawEndPosL = { Door.NumlightEllCPos_.x - Door.NumlightEllSize_.x,Door.NumlightEllCPos_.y };
		DrawEndPosR = { Door.NumlightEllCPos_.x + Door.NumlightEllSize_.x,Door.NumlightEllCPos_.y };


		//particle初期化
		if (!isAlive_) {
			Init(
				float(rand() % 200 - 100) / 100,
				{ float(rand() % Global::windowSize_.x),float(rand() % Global::windowSize_.y) },
				float(rand() % 200) / 100,
				radius_
			);
			alpha_ = 0x00;
			lifeTime_ = rand() % 120 + 120;
			isAlive_ = true;
			speed_ = radius_ / 5;
			alphaDir_ = 1;


		} else {

			//lightの範囲内で行われる処理
			if (NoInitCross(DrawStartPos, DrawEndPosL, pos_) < 0 &&
				NoInitCross(DrawStartPos, DrawEndPosR, pos_) > 0 &&
				pos_.y < Door.NumlightEllCPos_.y + Door.NumlightEllSize_.y/2) {
				isDraw = true;//表示
				pos_.x += theta_ * speed_;//移動処理
				pos_.y += theta_ * speed_;//移動処理

			} else {//範囲外だと
				isDraw = false;	//表示されない
			}





			if (Door.DLAddT_ <= 0.5f) {//ライトが点滅するとき
				alpha_ -= int((float(0xff) / (Door.DLAddT_ * 1.5f)));//消える
				if (alpha_ <= 0x00) {
					alpha_ = 0x00;
					alphaDir_ *= -1;
					isAlive_ = false;
				}
			} else {//ライトが点灯してるとき
				//0～255～0に透明度を変える
				alpha_ += int((float(0xff) / (lifeTime_ / 2))) * alphaDir_;
				if (alpha_ >= 0xff) {
					alpha_ = 0xff;
					alphaDir_ *= -1;
				}
				if (alpha_ <= 0x00) {
					alpha_ = 0x00;
					alphaDir_ *= -1;
					isAlive_ = false;//0になったら消える
				}
			}
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

void SelectLightParticle::Draw(char* keys) {
	bool aaa = false;
	switch (Scene::sceneNum_) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================



		if (isAlive_ && isDraw) {
			My::DrawTriangle(
				pos_, radius_, 0.0f, 0xFFFFFF00 + alpha_
			);
		}
		//	void DrawTriangle(Vec2 center, float radius, float theta, int color);

		if (keys[DIK_P]) {
			if (aaa) {
				aaa = false;
			} else {
				aaa = true;
			}
		}
		if (aaa) {
			Novice::DrawLine(int(DrawStartPos.x), int(DrawStartPos.y), int(DrawEndPosL.x), int(DrawEndPosL.y), 0xFF0000FF);
			Novice::DrawLine(int(DrawStartPos.x), int(DrawStartPos.y), int(DrawEndPosR.x), int(DrawEndPosR.y), 0xFF0000FF);
			Novice::DrawLine(int(0), 605, 500, 605, 0xFF0000FF);
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