#include "PlayerShadow.h"

void PlayerShadow::Update(char* keys, Screen screen, Shadow shadow) {


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

		//前のフレームの情報保存に関するもの
		prePos_ = pos_;
		prePosCopy_ = prePos_;

		/*-------------------------------移動処理-------------------------------*/
		velocity_ = { 0.0f,0.0f };


		if (address_[LeftBottom].y + 1 < shadow.GetMapChip().size()) {
			if (shadow.GetMapChip()[address_[LeftBottom].y + 1][address_[LeftBottom].x] > 0 or
				shadow.GetMapChip()[address_[RightBottom].y + 1][address_[RightBottom].x] > 0) {

				if (pos_.y == shadow.GetPos()[address_[LeftBottom].y + 1][address_[LeftBottom].x].y - (size_.y * 0.5f) - (shadow.GetSize().y * 0.5f) or
					pos_.y == shadow.GetPos()[address_[RightBottom].y + 1][address_[RightBottom].x].y - (size_.y * 0.5f) - (shadow.GetSize().y * 0.5f)) {

					isJump_ = false;
					isDrop_ = false;
					dropSpeed_ = 0.0f;
					jumpSpeed_ = 0.0f;

				} else {

					isDrop_ = true;
				}

			} else {
				isDrop_ = true;
			}
		}

		//ジャンプ
		if (isJump_) {
			jumpSpeed_ = -8.0f;

		} else {

			if (!isDrop_) {
				if (keys[DIK_W]) {

					isJump_ = true;
					isDrop_ = true;
					jumpSpeed_ = -8.0f;

				} else {
					jumpSpeed_ = 0.0f;
				}
			}

		}

		if (pos_.y < (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f) {

			isDrop_ = true;
		}

		//落下
		if (isDrop_) {

			dropSpeed_ += gravity_;
		} else {
			dropSpeed_ = 0.0f;
		}

		//移動量の決定
		velocity_.y = jumpSpeed_ + dropSpeed_;


		//左右移動
		direction_.x = float(keys[DIK_D] - keys[DIK_A]);

		velocity_.x = Normalize({ 0.0f,0.0f }, direction_).x;

		velocity_.x *= speed_;

		if (hitCount_ < 2) {
			pos_.x += velocity_.x;
			pos_.y += velocity_.y;
		}

		/*-------------------------------押し戻し-------------------------------*/

		isHitMapChip_ = false;
		hitCount_ = 0;

			//上下===============================================
			//下に出た時
		if (pos_.y >= (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f) {
			pos_.y = (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f;

			isJump_ = false;
			isDrop_ = false;
			dropSpeed_ = 0.0f;
			jumpSpeed_ = .0f;

			//上に出た時
		} else if (pos_.y <= screen.GetScreenLeftTop().y + size_.y * 0.5f) {
			pos_.y = screen.GetScreenLeftTop().y + size_.y * 0.5f;

		}

		//左右===============================================
		//右に出た時
		if (pos_.x >= (screen.GetScreenLeftTop().x + screen.GetSize().x) - size_.x * 0.5f) {
			pos_.x = (screen.GetScreenLeftTop().x + screen.GetSize().x) - size_.x * 0.5f - 1;

			//左に出た時
		} else if (pos_.x <= screen.GetScreenLeftTop().x + size_.x * 0.5f) {
			pos_.x = screen.GetScreenLeftTop().x + size_.x * 0.5f;

		}


		//マップチップの当たり判定=======================================================================
		// 
				//前フレーム番地の保存
		for (int i = 0; i < 4; i++) {
			preAddress_[i] = address_[i];

		}

		//影の矩形との当たり判定
		for (int i = 0; i < screen.GetPos().size(); i++) {

			if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x >= screen.GetPos(i, 3).x) {

				PushBackBox_Ball(
					screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
					pos_, prePos_, size_.x * 0.5f,
					isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_
				);

			} else if (screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x && screen.GetPos(i, 6).x <= screen.GetPos(i, 2).x) {

				PushBackBox_Ball(
					screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 6), screen.GetPos(i, 3),
					pos_, prePos_, size_.x * 0.5f,
					isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_
				);
			
			} else if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x) {

				PushBackBox_Ball(
					screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 3),
					pos_, prePos_, size_.x * 0.5f,
					isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_
				);
			}
		}

		//位階以上当たっていた時、再計算
		if (hitCount_ >= 1) {

			for (int i = 0; i < screen.GetPos().size(); i++) {

				if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x >= screen.GetPos(i, 3).x) {

					PushBackBox_Ball(
						screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
						pos_, prePos_, size_.x * 0.5f,
						isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_
					);

				} else if (screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x && screen.GetPos(i, 6).x <= screen.GetPos(i, 2).x) {

					PushBackBox_Ball(
						screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 6), screen.GetPos(i, 3),
						pos_, prePos_, size_.x * 0.5f,
						isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_
					);

				} else if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x) {

					PushBackBox_Ball(
						screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 3),
						pos_, prePos_, size_.x * 0.5f,
						isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_
					);
				}
			}
		}

		//二つの矩形に当たっていたら前の座標に戻す
		if (hitCount_ >= 2) {
			pos_ = prePos_;
			isJump_ = false;
			isDrop_ = false;
			dropSpeed_ = 0.0f;
			jumpSpeed_ = 0.0f;
		}

		//プレイヤーの番地計算
		CalcAddress(
			address_,
			{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y + 1 },
			{ shadow.GetSize().x,shadow.GetSize().y },
			size_.x * 0.5f
		);



		//マップチップの当たり判定
		PushBackMapChip(
			int(shadow.GetMapChip().size()), int(shadow.GetMapChip()[0].size()),
			&pos_,
			address_, preAddress_,
			size_,
			velocity_,
			shadow.GetPos(),
			shadow.GetMapChip(),
			{ shadow.GetSize().x,shadow.GetSize().y },
			isHitMapChip_
		);

		if (PushBackMapChip(
			int(shadow.GetMapChip().size()), int(shadow.GetMapChip()[0].size()),
			&pos_,
			address_, preAddress_,
			size_,
			velocity_,
			shadow.GetPos(),
			shadow.GetMapChip(),
			{ shadow.GetSize().x,shadow.GetSize().y },
			isHitMapChip_
		) == Top) {

			isJump_ = false;
			isDrop_ = false;
			dropSpeed_ = 0.0f;
		}

		if (hitCount_ >= 1 && isHitMapChip_) {
			pos_ = prePos_;
			isJump_ = false;
			isDrop_ = false;
			dropSpeed_ = 0.0f;
			jumpSpeed_ = 0.0f;
		}

		//プレイヤーの番地を再計算
		CalcAddress(
			address_,
			{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y + 1 },
			{ shadow.GetSize().x,shadow.GetSize().y },
			size_.x * 0.5f
		);


		Novice::ScreenPrintf(0, 120, "%d",hitCount_);

		break;
		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}

void PlayerShadow::Draw() {

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

		Novice::DrawEllipse(
			int(pos_.x),
			int(pos_.y),
			int(size_.x * 0.5f),
			int(size_.y * 0.5f),
			0.0f,
			0xff0000ff,
			kFillModeSolid
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
