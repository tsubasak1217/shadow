#include "Light.h"
#include "PlayerShadow.h"

//=========================================================初期化関数==============================================================
void Light::Init(int sceneNum, Map map) {
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

		//ステージごとのライトの初期座標
		firstEmitPos_[0] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[1] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[2] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[3] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[4] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[5] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[6] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };
		firstEmitPos_[7] = { Global::windowSize_.x * 0.5f,Global::windowSize_.y - map.GetSize().y * 0.2f };

		emitPos_ = {
		Global::windowSize_.x * 0.5f,
		Global::windowSize_.y - map.GetSize().y * 0.2f
		};
		aimPos_ = { -100.0f,-100.0f };
		lightHitSpot_.clear();
		rangeTheta_ = 0.0f;
		leftVec_ = { 0.0f,0.0f };
		rightVec_ = { 0.0f,0.0f };

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
void Light::Update(char* keys, const ChangeScene& cs, Map map, float rangeTheta,bool isPause,PlayerShadow ps) {

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(Scene::sceneNum_, map);
	}

	if (!isPause) {
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
				Init(Scene::sceneNum_, map);
			}

			lightHitSpot_.clear();

			aimPos_ = { emitPos_.x,emitPos_.y - Global::windowSize_.y };

			leftVec_ = Multiply(
				aimPos_.operator-(emitPos_),
				AffineMatrix({ 1.0f,1.0f }, -(rangeTheta * 0.5f), emitPos_)
			);

			rightVec_ = Multiply(
				aimPos_.operator-(emitPos_),
				AffineMatrix({ 1.0f,1.0f }, rangeTheta * 0.5f, emitPos_)
			);

			leftVec_ = CrossPos(emitPos_, leftVec_, { 0,0 }, { float(Global::windowSize_.x),0 });
			rightVec_ = CrossPos(emitPos_, rightVec_, { 0,0 }, { float(Global::windowSize_.x),0 });


			if (!cs.isStartChange_) {
				if (ps.GetIsAlive()) {
					if (keys[DIK_Q]) {
						Global::isMoveShadow_ = true;
						emitPos_.x -= 2.0f;
					}

					if (keys[DIK_E]) {
						Global::isMoveShadow_ = true;
						emitPos_.x += 2.0f;
					}
				}
			}

			//左右の壁
			if (emitPos_.x > Global::windowSize_.x - 32.0f) {
				emitPos_.x = Global::windowSize_.x - 32.0f;

			} else if (emitPos_.x < 32.0f) {
				emitPos_.x = 32.0f;
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
};


//====================================================描画=============================================================
void Light::Draw(const Resources& rs,Map map, ChangeScene CS) {

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
		if (!CS.isEndChange_) {//ゴールにたどり着いたとき、光を消す

			Novice::DrawTriangle(
				int(emitPos_.x),
				int(emitPos_.y),
				int(leftVec_.x),
				int(leftVec_.y),
				int(rightVec_.x),
				int(rightVec_.y),
				0xffffff01,
				kFillModeSolid
			);

			for (int i = 0; i < 2; i++) {
				Novice::DrawTriangle(
					int(emitPos_.x),
					int(emitPos_.y),
					int(leftVec_.x - i * 48.0f),
					int(leftVec_.y),
					int(rightVec_.x + i * 48.0f),
					int(rightVec_.y),
					0xffffff01,
					kFillModeSolid
				);
			}
		}


		Novice::DrawQuad(
			int(emitPos_.x - 32),
			int(emitPos_.y - 48),
			int(emitPos_.x + 32),
			int(emitPos_.y - 48),
			int(emitPos_.x - 32),
			int(emitPos_.y + 16),
			int(emitPos_.x + 32),
			int(emitPos_.y + 16),
			0, 0,
			64, 64,
			rs.blockGH_[6],
			0xffffffff
		);

		//←
		Novice::DrawSpriteRect(
			int(emitPos_.x - 64 * 0.5f - 32) - int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
			int(emitPos_.y - 64 * 0.5f - 6) - (6 * Novice::CheckHitKey(DIK_Q)),
			0, 64,
			32, 32,
			rs.keysGH_,
			(32.0f / 128.0f) + ((32.0f / 128.0f) * 0.2f) * Novice::CheckHitKey(DIK_Q),
			(32.0f / 94.0f) + ((32.0f / 94.0f) * 0.2f) * Novice::CheckHitKey(DIK_Q),
			0.0f,
			0xffffff5f + int(float(0x4f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
		);

		//→
		Novice::DrawSpriteRect(
			int(emitPos_.x + 64 * 0.5f) + int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
			int(emitPos_.y - 64 * 0.5f - 6) - (6 * Novice::CheckHitKey(DIK_E)),
			32, 64,
			32, 32,
			rs.keysGH_,
			(32.0f / 128.0f) + ((32.0f / 128.0f) *0.2f) * Novice::CheckHitKey(DIK_E),
			(32.0f / 94.0f) + ((32.0f / 94.0f) * 0.2f) * Novice::CheckHitKey(DIK_E),
			0.0f,
			0xffffff5f + int(float(0x4f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
		);

		break;


		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}

};