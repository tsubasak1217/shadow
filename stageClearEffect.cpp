#include"stageClearEffect.h"

void SCE::Init() {
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
#pragma region"初期化（適宜変更）"
		for (int i = 0; i < EFP_MAX; i++) {
			CPos_[i] = { 0 };
			size_[i] = float(rand() % 30 + 15);

			t_ = 0;
			addT_ = 0;
			easeTimer_ = 30.0f;
			scale_ = { 1,1 };

			rotateTheta_[i] = { 0 };
			theta_[i] = (1.0f / static_cast<int>(rand() % 30 + 10) * float(M_PI));
			for (int j = 0; j < 4; j++) {
				vertex_[i][j] = { 0 };
				affineVertex_[i][j] = { 0 };
			}
			vel_[i] = { 0 };
			Dirvel_[i] = { 0 };
			acc_ = { 0,0.5f };
			isEffect_ = false;
			moveSpeed[i] = float(rand() % 5 + 20);
			color_ = 0x000000FF;
		}
		EffectCount = 0;
		canSceneChange = false;

		for (int i = 0; i < (EFP_MAX / 2); i++) {
			CPos_[i] = { -20,float(Global::windowSize_.y) * 0.8f };
			Dirvel_[i].x = float(rand() % 5 + 5);
			Dirvel_[i].y = float(rand() % 10 - 30);
		}


		for (int i = (EFP_MAX / 2); i < EFP_MAX; i++) {
			CPos_[i] = { float(Global::windowSize_.x) + 20 ,float(Global::windowSize_.y) * 0.8f };

			Dirvel_[i].x = float(rand() % 5 - 10);
			Dirvel_[i].y = float(rand() % 10 - 30);

		}


		for (int i = 0; i < EFP_MAX; i++) {
			MatrixVertex(vertex_[i], size_[i]);
		}
#pragma endregion
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================

		break;
	}


}

void SCE::Update(float FT) {
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
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
#pragma region"回転しながら落下していく"
		for (int i = 0; i < EFP_MAX; i++) {
			
			/*文字が出現するかつ動いていないとき*/
			if (FT >= 1.0f && vel_[0].x == 0) {
				isEffect_ = true;//開始
			}

			/*パーティクルを飛ばす※１*/
			if (isEffect_) {
				NormalizeMikami(Dirvel_[i]);
				Dirvel_[i].x *= moveSpeed[i];
				Dirvel_[i].y *= moveSpeed[i];
				vel_[i].x = Dirvel_[i].x;
				vel_[i].y = Dirvel_[i].y;
			}

			/*回転させながら落としていく*/
			if (vel_[i].x != 0) {
				rotateTheta_[i] += theta_[i];
				vel_[i].y += acc_.y;
				CPos_[i].x += vel_[i].x;
				CPos_[i].y += vel_[i].y;

			}

			/*変換*/
			affineMatrix_[i] = AffineMatrix(scale_, rotateTheta_[i], CPos_[i]);
			for (int j = 0; j < 4; j++) {
				affineVertex_[i][j] = TransformMikami(vertex_[i][j], affineMatrix_[i]);

			}

		}

		//※１のすべて処理が終わるとフラグを下す
		isEffect_ = false;

		/*無限に落とし続けるのも癪なので画面外に行ったらどっかにやる*/
		for (int i = 0; i < (EFP_MAX); i++) {
			if (CPos_[i].y >= 750.0f) {
				CPos_[i] = { -1000,-1000 };
				vel_[i] = { 1,0 };
				acc_ = { 0,0 };
				EffectCount += 1;//画面外にいった回数を図る
				for (int j = 0; j < 4; j++) {
					affineVertex_[i][j] = { 0 };
				}

			}
		}

		/*全てのパーティクルが画面に言ったらシーン遷移できるようにする*/
		if (EffectCount == EFP_MAX) {
			canSceneChange = true;
		}


#pragma endregion
		break;
	}



}


void SCE::Draw() {

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
		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
#pragma region"描画"
		for (int i = 0; i < EFP_MAX; i++) {
			Novice::DrawQuad(static_cast<int>(affineVertex_[i][0].x), static_cast<int>(affineVertex_[i][0].y),
				static_cast<int>(affineVertex_[i][1].x), static_cast<int>(affineVertex_[i][1].y),
				static_cast<int>(affineVertex_[i][2].x), static_cast<int>(affineVertex_[i][2].y),
				static_cast<int>(affineVertex_[i][3].x), static_cast<int>(affineVertex_[i][3].y),
				0, 0, 1, 1, GH, color_);
		}
#pragma endregion

		break;
	}

}