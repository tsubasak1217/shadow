#include "Player.h"

//====================================================初期化関数=============================================================
void Player::Init(int sceneNum) {

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
void Player::Update(char* keys,Map map) {

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
		

		/*-------------------------------移動処理-------------------------------*/
		velocity_ = { 0.0f,0.0f };

		direction_.x = float(keys[DIK_RIGHT] - keys[DIK_LEFT]);
		direction_.y = float(keys[DIK_DOWN] - keys[DIK_UP]);

		velocity_ = Normalize({ 0.0f,0.0f }, direction_);

		velocity_.x *= speed_;
		velocity_.y *= speed_;

		pos_.x += velocity_.x;
		pos_.y += velocity_.y;



		/*-------------------------------押し戻し-------------------------------*/
		
		//上下===============================================
		//下に出た時
		if (pos_.y >= (map.GetPuzzleLeftTop().y + map.GetPuzzleMapSize().y) - size_.y * 0.5f) {
			pos_.y = (map.GetPuzzleLeftTop().y + map.GetPuzzleMapSize().y) - size_.y * 0.5f;

			//上に出た時
		} else if (pos_.y <= map.GetPuzzleLeftTop().y + size_.y * 0.5f) {
			pos_.y = map.GetPuzzleLeftTop().y + size_.y * 0.5f;

		}

		//左右===============================================
		//右に出た時
		if (pos_.x >= (map.GetPuzzleLeftTop().x + map.GetPuzzleMapSize().x) - size_.x * 0.5f) {
			pos_.x = (map.GetPuzzleLeftTop().x + map.GetPuzzleMapSize().x) - size_.x * 0.5f;
		
			//左に出た時
		} else if (pos_.x <= map.GetPuzzleLeftTop().x + size_.x * 0.5f) {
			pos_.x = map.GetPuzzleLeftTop().x + size_.x * 0.5f;
		
		}

		//前フレーム番地の保存
		for (int i = 0; i < 4; i++) {
			preAddress_[i] = address_[i];

			Novice::ScreenPrintf(0, i * 20, "[%d,%d]", address_[i].x, address_[i].y);
		}

		//プレイヤーの番地計算
		CalcAddress(
			address_,
			{ pos_.x - map.GetPuzzleLeftTop().x + 1,pos_.y - map.GetPuzzleLeftTop().y + 1 },
			{ map.GetSize().x,map.GetSize().y },
			size_.x * 0.5f
		);


		//マップチップの当たり判定
		PushBackMapChip(
			int(map.GetMapChip().size()), int(map.GetMapChip()[0].size()),
			&pos_,
			address_, preAddress_,
			size_,
			velocity_,
			map.GetPos(),
			map.GetMapChip(),
			{ map.GetSize().x,map.GetSize().y }
		);

		Novice::ScreenPrintf(0,200, "%d", PushBackMapChip(
			int(map.GetMapChip().size()), int(map.GetMapChip()[0].size()),
			&pos_,
			address_, preAddress_,
			size_,
			velocity_,
			map.GetPos(),
			map.GetMapChip(),
			{ map.GetSize().x,map.GetSize().y }
		));

		//プレイヤーの番地を再計算
		CalcAddress(
			address_,
			{ pos_.x - map.GetPuzzleLeftTop().x + 1,pos_.y - map.GetPuzzleLeftTop().y + 1},
			{ map.GetSize().x,map.GetSize().y}, 
			size_.x * 0.5f
		);

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}


//====================================================描画=============================================================
void Player::Draw(const Resources& rs, Map map) {

	//シーンに応じて処理を分ける
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
			int(pos_.x - size_.x * 0.5f),
			int(pos_.y + size_.y * 0.5f),
			int(pos_.x + size_.x * 0.5f),
			int(pos_.y + size_.y * 0.5f),
			int(pos_.x - size_.x * 0.5f),
			int(pos_.y - size_.y * 0.5f),
			int(pos_.x + size_.x * 0.5f),
			int(pos_.y - size_.y * 0.5f),
			0, 0,
			1, 1,
			rs.whiteGH_,
			0xff0000ff
		);

		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
	
}