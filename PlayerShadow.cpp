#include "PlayerShadow.h"
#include "Particle.h"
#include "Shadow.h"
#include "SaveData.h"

bool PlayerShadow::isAlive_ = true;
bool PlayerShadow::preIsAlive_ = true;

void PlayerShadow::Init(int sceneNum, Screen screen, Shadow shadow, const char* keys, ChangeScene cs) {

	switch (sceneNum) {
		//====================================================================================
	case TITLE://							   タイトル画面
		//====================================================================================
		break;
		//====================================================================================
	case SELECT://							   ステージ選択
		//====================================================================================
		starGetCount_ = 0;
		break;
		//====================================================================================
	case GAME://								ゲーム本編
		//====================================================================================

		pos_ = {
		shadow.firstPlayerPos_.x + screen.GetScreenLeftTop().x,
		shadow.firstPlayerPos_.y + screen.GetScreenLeftTop().y,
		};
		prePos_ = pos_;

		size_ = { 32.0f,32.0f };
		direction_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		speed_ = 4.0f;
		for (int i = 0; i < 4; i++) {
			address_[i] = { 0,0 };
			preAddress_[i] = address_[i];
		}

		isAlive_ = true;
		preIsAlive_ = isAlive_;
		isBackToRespawnPos_ = false;
		preIsBackToRespawnPos_ = isBackToRespawnPos_;
		respawnTimeCount_ = 200;

		pos_.y += (shadow.GetSize().y * 0.5f);
		pos_.y += -(size_.y * 0.5f);

		isJump_ = false;
		isDrop_ = false;
		jumpSpeed_ = 0.0f;
		jumpVelocity_ = -7.5f;
		dropSpeed_ = 0.0f;
		gravity_ = 0.4f;
		hitCount_ = 0;
		isHitMapChip_ = false;
		isHitRect_ = false;
		blockCount = 0;
		boardingBlock_ = -1;
		boardingPos_ = { 0.0f,0.0f };
		boadingVecRatio_ = 0.0f;
		preBoadingVecRatio_ = boadingVecRatio_;

		hitSurface_.clear();
		hitSurface2_.clear();
		preHitSurface_.clear();
		preHitSurface2_.clear();

		jumpTimer_ = 0;
		waitTimer_ = 0;
		goalTutorialAlpha_ = 0;
		goalHoldTimer_ = 0;

		if (keys[DIK_R] or
			(cs.isStartChange_ && cs.preIsEndChange_)) {
			starGetCount_ = 0;
		}


		break;

	case CLEAR:

		Global::character_ = 0;
		break;

	default:
		break;
	}
}

void PlayerShadow::InitStar() {
	starFollowPos_.clear();
	preStarFollowPos_.clear();
	starTheta_.clear();
}

void PlayerShadow::Update(char* keys, char* Prekeys, const Resources& rs, ChangeScene& cs, Screen& screen,
	Shadow& shadow, Player& player, Map& map, Light& light, bool isPause) {
	Vec2 tmp = { 0.0f };

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(Scene::sceneNum_, screen, shadow, keys, cs);
		InitStar();
		prePos_ = pos_;
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
			if (!cs.isEndChange_) {
				Init(Scene::sceneNum_, screen, shadow, keys, cs);
				InitStar();
			}
		}
		if (!isPause && !cs.isEndChange_ && !cs.isStartChange_) {
			//前のフレームの情報保存に関するもの
			prePos_ = pos_;
			preIsAlive_ = isAlive_;
			preIsBackToRespawnPos_ = isBackToRespawnPos_;

			//動いてないとき、待機時間タイマーを加算
			//動いていないとき、動いていない時間タイマーを加算
			if (Global::controlMode_ == 0) {
				if (!keys[DIK_UP] && !keys[DIK_LEFT] && !keys[DIK_RIGHT]) {
					waitTimer_++;
				} else {
					waitTimer_ = 0;
				}
			} else {
				if (velocity_.x == 0 && int(velocity_.y) == 0) {
					waitTimer_++;
				} else {
					waitTimer_ = 0;
				}
			}

			/*----------------------------死んだときの処理-----------------------------*/
			if (!isAlive_) {
				Global::aliveTimer_ = 0;
				respawnTimeCount_--;

				if (respawnTimeCount_ == 135) {
					//復活音
					Novice::PlayAudio(rs.playerRespawnSE_, 0, 0.12f);

				} else if (respawnTimeCount_ < 80) {

					if (respawnTimeCount_ == 79) {

						map.Init(rs, Scene::sceneNum_);
						map.ReturnSavePoint();

						player.Init(Scene::sceneNum_, map);
						player.ReturnSavePoint(map);

						light.ReturnSavePoint();
						//shadow.Init(rs,screen,Scene::sceneNum_);

						pos_ = SaveData::savedPlayerShadowPos_;
						//screen.ReturnSavePoint();

						shadow.ReturnSavePoint();
					}

					isBackToRespawnPos_ = true;

					if (respawnTimeCount_ <= 0) {
						Init(Scene::sceneNum_, screen, shadow, keys, cs);
						pos_ = SaveData::savedPlayerShadowPos_;

						for (int i = 0; i < starFollowPos_.size(); i++) {

							starFollowPos_[i] = pos_;
						}
					}
				}
			} else {

				Global::aliveTimer_++;

				//殺す
				if (player.killSwitch_) {
					isAlive_ = false;
				}

				//配列数の決定
				if (hitSurface_.size() != screen.GetPos().size()) {

					hitSurface_.clear();

					for (int i = 0; i < screen.GetPos().size(); i++) {

						hitSurface_.push_back(0);
					}
				}

				hitSurface2_.clear();
				for (int i = 0; i < shadow.GetPos().size(); i++) {
					for (int j = 0; j < shadow.GetPos()[0].size(); j++) {

						if (shadow.GetMapChip()[i][j] == 1 or shadow.GetMapChip()[i][j] == 11) {

							hitSurface2_.push_back(0);
						}
					}
				}

				preHitSurface_ = hitSurface_;
				preHitSurface2_ = hitSurface2_;

				/*-------------------------------移動処理-------------------------------*/
				velocity_ = { 0.0f,0.0f };
				direction_ = { 0,0 };

				//ジャンプ
				if (isJump_) {
					jumpSpeed_ = jumpVelocity_;
					jumpTimer_++;

					if (jumpTimer_ > 32) {
						jumpTimer_ = 32;
					}

				} else {

					jumpTimer_ = 0;

					if (!isDrop_) {


						if (Global::controlMode_ == 0) {
							if (keys[DIK_UP]) {

								if (Global::character_ == 0) {
									isJump_ = true;
									isDrop_ = true;
									jumpSpeed_ = jumpVelocity_;
								}

							} else {
								jumpSpeed_ = 0.0f;
							}
						} else {

							if (Novice::IsPressButton(0, kPadButton10)) {

								if (Global::character_ == 0) {
									isJump_ = true;
									isDrop_ = true;
									jumpSpeed_ = jumpVelocity_;
								}
							} else {
								jumpSpeed_ = 0.0f;
							}
						}

					}

				}

				if (pos_.y < (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f) {
					isDrop_ = true;
				}

				if (address_[LeftBottom].y + 1 < shadow.GetMapChip().size()) {
					if (shadow.GetMapChip()[address_[LeftBottom].y + 1][address_[LeftBottom].x] > 0 or
						shadow.GetMapChip()[address_[RightBottom].y + 1][address_[RightBottom].x] > 0) {

						if (shadow.GetMapChip()[address_[LeftBottom].y + 1][address_[LeftBottom].x] != 2 &&
							shadow.GetMapChip()[address_[RightBottom].y + 1][address_[RightBottom].x] != 2) {

							if (shadow.GetMapChip()[address_[LeftBottom].y + 1][address_[LeftBottom].x] != 8 &&
								shadow.GetMapChip()[address_[RightBottom].y + 1][address_[RightBottom].x] != 8) {

								if (shadow.GetMapChip()[address_[LeftBottom].y + 1][address_[LeftBottom].x] != 7 &&
									shadow.GetMapChip()[address_[RightBottom].y + 1][address_[RightBottom].x] != 7) {

									if ((pos_.y <= shadow.GetPos()[address_[LeftBottom].y + 1][address_[LeftBottom].x].y - (size_.y * 0.5f) - (shadow.GetSize().y * 0.5f) + 1.0f &&
										pos_.y >= shadow.GetPos()[address_[LeftBottom].y + 1][address_[LeftBottom].x].y - (size_.y * 0.5f) - (shadow.GetSize().y * 0.5f) - 2.0f) or
										(pos_.y <= shadow.GetPos()[address_[RightBottom].y + 1][address_[RightBottom].x].y - (size_.y * 0.5f) - (shadow.GetSize().y * 0.5f) + 1.0f &&
											pos_.y >= shadow.GetPos()[address_[RightBottom].y + 1][address_[RightBottom].x].y - (size_.y * 0.5f) - (shadow.GetSize().y * 0.5f) - 2.0f)
										) {

										if (shadow.GetTouchable()[address_[RightBottom].y + 1][address_[RightBottom].x] or
											shadow.GetTouchable()[address_[LeftBottom].y + 1][address_[LeftBottom].x]) {
											isJump_ = false;
											isDrop_ = false;
											dropSpeed_ = 0.0f;
											jumpSpeed_ = 0.0f;
										}

									} else {
										isDrop_ = true;
									}

								} else {
									isDrop_ = true;
								}
							} else {
								isDrop_ = true;
							}
						} else {
							isDrop_ = true;
						}
					} else {
						isDrop_ = true;
					}

				}

				if (address_[2].y >= 0 && address_[2].y + 1 < shadow.GetMapChip().size()) {
					if ((shadow.GetMapChip()[address_[2].y + 1][address_[2].x] == 7 &&
						shadow.GetMapChip()[address_[3].y + 1][address_[3].x] == 7) or
						(shadow.GetMapChip()[address_[2].y][address_[2].x] == 7 or
							shadow.GetMapChip()[address_[3].y][address_[3].x] == 7)) {
						isDrop_ = true;
					}
				}

				//ジャンプ
				if (!isJump_) {


					if (Global::controlMode_ == 0) {
						if (keys[DIK_UP]) {

							if (Global::character_ == 0) {
								isJump_ = true;
								isDrop_ = true;
								jumpSpeed_ = jumpVelocity_;
							}

						} else {
							jumpSpeed_ = 0.0f;
						}
					} else {

						if (Novice::IsPressButton(0, kPadButton10)) {

							if (Global::character_ == 0) {
								isJump_ = true;
								isDrop_ = true;
								jumpSpeed_ = jumpVelocity_;
							}
						} else {
							jumpSpeed_ = 0.0f;
						}
					}
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
				Vector2<int>padDirection;
				Novice::GetAnalogInputLeft(0, &padDirection.x, &padDirection.y);

				if (Global::character_ == 0) {
					if (Global::controlMode_ == 0) {
						direction_.x = float(keys[DIK_RIGHT] - keys[DIK_LEFT]);
					} else {
						direction_.x = float(-padDirection.x);
					}
				}

				velocity_.x = Normalize({ 0.0f,0.0f }, direction_).x;

				velocity_.x *= speed_;

				if (hitCount_ < 2) {
					pos_.x += velocity_.x * (1.0f - (0.15f * isJump_));
					pos_.y += velocity_.y;
				}


				//乗っている影ブロックが動けば一緒に動く--------------------------------------
				preBordingBlock_ = boardingBlock_;

				if (boardingBlock_ >= 0) {
					if (isJump_) {
						boardingBlock_ = -1;
					}
				}

				preBoadingVecRatio_ = boadingVecRatio_;

				for (int i = 0; i < screen.GetPos().size(); i++) {

					hitSurface_[i] = 0;

					//
					int a = (boardingBlock_ | preBordingBlock_);

					if (a >= 0) {

						boardingPos_ = CrossPos(
							screen.GetPos(a, 0), screen.GetPos(a, 1),
							pos_, { pos_.x,pos_.y + 1.0f }
						);

						boadingVecRatio_ = Dot(
							screen.GetPos(a, 0), screen.GetPos(a, 1),
							pos_
						);

						if (player.GetIsMoveBlock()) {

							pos_.x = screen.GetPos(a, 0).x +
								Normalize(screen.GetPos(a, 1), screen.GetPos(a, 0)).x * preBoadingVecRatio_;

							if (!isJump_) {
								pos_.y = screen.GetPos(a, 0).y - (size_.y * 0.5f - 1);
							}

						} else if (Global::isMoveShadow_ && player.swapTimeCount_ == 0) {
							pos_.x = screen.GetPos(a, 0).x +
								Normalize(screen.GetPos(a, 1), screen.GetPos(a, 0)).x * preBoadingVecRatio_;

							if (!isJump_) {
								pos_.y = screen.GetPos(a, 0).y - (size_.y * 0.5f - 1);
							}

							isDrop_ = false;
						}

					}
				}

				/*------------------------------- 押し戻し-------------------------------*/

				isHitMapChip_ = false;
				isHitRect_ = false;
				hitCount_ = 0;

				//上下===============================================
				//下に出た時
				if (pos_.y >= (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f) {
					pos_.y = (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f;

					isJump_ = false;
					isDrop_ = false;
					dropSpeed_ = 0.0f;
					jumpSpeed_ = 0.0f;

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

				//前フレーム番地の保存
				for (int i = 0; i < 4; i++) {
					preAddress_[i] = address_[i];

				}


				if (player.GetIsSwapped()) {
					pos_.y -= 2;
					prePos_ = pos_;
				}

				//プレイヤーの番地計算
				CalcAddress2(
					address_,
					{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y + 1 },
					{ shadow.GetSize().x,shadow.GetSize().y },
					size_.x * 0.5f,
					int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
				);


				for (int i = 0; i < screen.GetPos().size(); i++) {

					//影の矩形との当たり判定
					if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x >= screen.GetPos(i, 3).x) {

						if (
							PushBackBox_Ball(keys,
								screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
								screen.GetPrePos(i, 0), screen.GetPrePos(i, 1), screen.GetPrePos(i, 2), screen.GetPrePos(i, 7),
								pos_, prePos_, size_.x * 0.5f,
								isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface_[i], preHitSurface_[i]
							) == Top) {


							boardingBlock_ = i;
							boadingVecRatio_ = Dot(
								screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
								pos_
							);

							break;

						} else {
							boardingBlock_ = -1;
						}

					} else if (screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x && screen.GetPos(i, 6).x <= screen.GetPos(i, 2).x) {

						if (
							PushBackBox_Ball(keys,
								screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 6), screen.GetPos(i, 3),
								screen.GetPrePos(i, 0), screen.GetPrePos(i, 1), screen.GetPrePos(i, 6), screen.GetPrePos(i, 3),
								pos_, prePos_, size_.x * 0.5f,
								isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface_[i], preHitSurface_[i]
							) == Top) {
							boardingBlock_ = i;
							boadingVecRatio_ = Dot(
								screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
								pos_
							);

							break;

						} else {
							boardingBlock_ = -1;
						}

					} else if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x) {

						if (
							PushBackBox_Ball(keys,
								screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 3),
								screen.GetPrePos(i, 0), screen.GetPrePos(i, 1), screen.GetPrePos(i, 2), screen.GetPrePos(i, 3),
								pos_, prePos_, size_.x * 0.5f,
								isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface_[i], preHitSurface_[i]
							) == Top) {
							boardingBlock_ = i;
							boadingVecRatio_ = Dot(
								screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
								pos_
							);

							break;

						} else {
							boardingBlock_ = -1;
						}
					}
				}


				//マップチップの当たり判定
				for (int i2 = 0; i2 < shadow.GetPos().size(); i2++) {
					for (int j2 = 0; j2 < shadow.GetPos()[0].size(); j2++) {

						//星アイテムの取得
						if (shadow.GetMapChip()[i2][j2] == 8) {
							if (ColisionBox_Ball(
								{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
								pos_,
								size_.x * 0.25f
							)) {
								starGetCount_++;
								starFollowPos_.push_back(pos_);
								preStarFollowPos_.push_back(pos_);
								starTheta_.push_back(0.0f);
								itemGetSEHandle_ = Novice::PlayAudio(rs.itemGetSE_, 0, 0.4f);
								shadow.SetMapChip(i2, j2, 0);
								SaveData::shadowMap_ = shadow.GetMapChip();
								SaveData::savedShadowMap_ = SaveData::shadowMap_;
							}
						}

						//プレイヤーがスイッチを押したら現れるブロックと重なっていたらスイッチを押せなくする
						if (shadow.GetMapChip()[i2][j2] == 11) {
							if (ColisionBox_Ball(
								{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
								pos_,
								size_.x * 0.35f
							)) {
								if (!shadow.GetTouchable()[i2][j2]) {
									player.SetSwitchPushable(false);
								}
							} else {
								player.SetSwitchPushable(true);
							}
						}

						if (shadow.GetMapChip()[i2][j2] != 2 && shadow.GetMapChip()[i2][j2] != 7 && shadow.GetMapChip()[i2][j2] != 8) {
							if (shadow.GetMapChip()[i2][j2] == 1 or shadow.GetMapChip()[i2][j2] == 11) {

								blockCount++;

								if (shadow.GetTouchable()[i2][j2]) {
									PushBackBox_Ball(keys,
										{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
										{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
										pos_, prePos_, size_.x * 0.5f,
										isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface2_[blockCount - 1], preHitSurface2_[blockCount - 1]
									);
								}
							}
						}

						if (shadow.GetMapChip()[i2][j2] == 2) {

							if (ColisionBox_Ball(
								{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
								{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
								pos_,
								size_.x * 0.4f
							)) {

								isAlive_ = false;

							}
						}
					}
				}

				blockCount = 0;

				//一回以上当たっていた時、当たらなくなるまで再計算
				if (hitCount_ >= 1) {

					isHitRect_ = true;
					int loopCount = 0;

					while (isHitRect_) {

						int saveHitCount = hitCount_;

						for (int i2 = 0; i2 < shadow.GetMapChip().size(); i2++) {
							for (int j2 = 0; j2 < shadow.GetMapChip()[0].size(); j2++) {

								if (shadow.GetMapChip()[i2][j2] != 7 && shadow.GetMapChip()[i2][j2] != 8) {
									if (shadow.GetMapChip()[i2][j2] == 1 or shadow.GetMapChip()[i2][j2] == 11) {

										blockCount++;
										if (shadow.GetTouchable()[i2][j2]) {

											PushBackBox_Ball(keys,
												{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y - shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x - shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
												{ shadow.GetPos()[i2][j2].x + shadow.GetSize().x * 0.5f,shadow.GetPos()[i2][j2].y + shadow.GetSize().y * 0.5f },
												pos_, prePos_, size_.x * 0.5f,
												isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface2_[blockCount - 1], preHitSurface2_[blockCount - 1]
											);
										}
									}
								}
							}
						}
						blockCount = 0;

						for (int i = 0; i < screen.GetPos().size(); i++) {

							if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x >= screen.GetPos(i, 3).x) {

								if (
									PushBackBox_Ball(keys,
										screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
										screen.GetPrePos(i, 0), screen.GetPrePos(i, 1), screen.GetPrePos(i, 2), screen.GetPrePos(i, 7),
										pos_, prePos_, size_.x * 0.5f,
										isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface_[i], preHitSurface_[i]
									) == Top) {
									boardingBlock_ = i;
									boadingVecRatio_ = Dot(
										screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
										pos_
									);
								}

							} else if (screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x && screen.GetPos(i, 6).x <= screen.GetPos(i, 2).x) {

								if (
									PushBackBox_Ball(keys,
										screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 6), screen.GetPos(i, 3),
										screen.GetPrePos(i, 0), screen.GetPrePos(i, 1), screen.GetPrePos(i, 6), screen.GetPrePos(i, 3),
										pos_, prePos_, size_.x * 0.5f,
										isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface_[i], preHitSurface_[i]
									) == Top) {
									boardingBlock_ = i;
									boadingVecRatio_ = Dot(
										screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
										pos_
									);
								}

							} else if (screen.GetPos(i, 6).x >= screen.GetPos(i, 2).x && screen.GetPos(i, 7).x <= screen.GetPos(i, 3).x) {

								if (
									PushBackBox_Ball(keys,
										screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 3),
										screen.GetPrePos(i, 0), screen.GetPrePos(i, 1), screen.GetPrePos(i, 2), screen.GetPrePos(i, 3),
										pos_, prePos_, size_.x * 0.5f,
										isDrop_, isJump_, dropSpeed_, jumpSpeed_, hitCount_, hitSurface_[i], preHitSurface_[i]
									) == Top) {
									boardingBlock_ = i;
									boadingVecRatio_ = Dot(
										screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
										pos_
									);
								}
							}
						}

						//上下===============================================
						//下に出た時
						if (pos_.y > (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f) {
							pos_.y = (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f;

							isJump_ = false;
							isDrop_ = false;
							dropSpeed_ = 0.0f;
							jumpSpeed_ = .0f;

							hitCount_++;

							//上に出た時
						} else if (pos_.y < screen.GetScreenLeftTop().y + size_.y * 0.5f) {
							pos_.y = screen.GetScreenLeftTop().y + size_.y * 0.5f;

							hitCount_++;

						}

						//左右===============================================
						//右に出た時
						if (pos_.x > (screen.GetScreenLeftTop().x + screen.GetSize().x) - size_.x * 0.5f) {
							pos_.x = (screen.GetScreenLeftTop().x + screen.GetSize().x) - size_.x * 0.5f;

							hitCount_++;

							//左に出た時
						} else if (pos_.x < screen.GetScreenLeftTop().x + size_.x * 0.5f) {
							pos_.x = screen.GetScreenLeftTop().x + size_.x * 0.5f;

							hitCount_++;
						}

						//ループ回数を加算
						loopCount++;

						//ループを抜ける-------------------------------
						if (loopCount > 64) {//無限ループになりそうなときにブレイク
							loopCount = 0;
							isHitRect_ = false;

							//if (player.killSwitch_) {
							isAlive_ = false;
							//}

							break;
						}

						if (saveHitCount == hitCount_) {//当たらなくなった時
							isHitRect_ = false;
						}
					}
				}

				//二つの矩形に当たっていたら前の座標に戻す
				if (hitCount_ >= 3) {
					//pos_ = prePos_;
					isJump_ = false;
					isDrop_ = false;
					dropSpeed_ = 0.0f;
					jumpSpeed_ = 0.0f;
				}
				//}


				//ゴールと当たったらクリアに移動
				if (ColisionBox_Ball(shadow.GetGoalLT(), shadow.GetGoalRT(), shadow.GetGoalLB(), shadow.GetGoalRB(), pos_, (size_.x / 10)) &&
					int(dropSpeed_) < 1) {

					if (Global::character_ == 0) {

						goalTutorialAlpha_ += 0x04;

						if (Global::controlMode_ == 0) {

							if (keys[DIK_SPACE] && !Prekeys[DIK_SPACE]) {
								cs.isEndChange_ = true;
								pushSEHandle_ = Novice::PlayAudio(rs.selectPushSE_, 0, 0.5f);
							}
						} else {
							if (Novice::IsPressButton(0, kPadButton11)) {

								cs.isEndChange_ = true;
								pushSEHandle_ = Novice::PlayAudio(rs.selectPushSE_, 0, 0.5f);
							}
						}
					}

				} else {
					goalTutorialAlpha_ -= 0x04;
				}

				if (Global::character_ == 1) {
					goalTutorialAlpha_ -= 0x04;
				}

				if (goalTutorialAlpha_ > 0xff) {
					goalTutorialAlpha_ = 0xff;
				} else if (goalTutorialAlpha_ < 0) {
					goalTutorialAlpha_ = 0;
				}

				//プレイヤーの番地を再計算
				CalcAddress(
					address_,
					{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y + 1 },
					{ shadow.GetSize().x,shadow.GetSize().y },
					size_.x * 0.5f,
					int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
				);
			}


			//星をプレイヤーに追尾させる
			for (int i = 0; i < starFollowPos_.size(); i++) {

				preStarFollowPos_[i] = starFollowPos_[i];

				starFollowPos_[i] =
					starFollowPos_[i].operator+(
						{
							(pos_.x - starFollowPos_[i].x) / (i * 16.0f + 8.0f),
							(pos_.y - starFollowPos_[i].y) / (i * 16.0f + 8.0f) }
				);

				starTheta_[i] += ((CheckLength(starFollowPos_[i], preStarFollowPos_[i])) / 2.0f) + 1.0f;

				//速度に応じて角度を加算する

			}


			// 下にとげがあるとき以外に座標を保存する
			tmp = (pos_ - screen.GetScreenLeftTop()) / shadow.GetSize();
			centerAddress_ = { int(tmp.y),int(tmp.x) };

			for (int i = 0; i < shadow.GetMapChip().size(); i++) {



				if (i == shadow.GetMapChip().size() - 1) {

					if (shadow.GetMapChip()[i][centerAddress_.y] == 2) {// とげ
						break;
					}

					SaveData::playerShadowPos_ = pos_.operator+({ 0.0f,-1.0f });// 一番下に到達したとき
					break;
				} else {

					if (i <= centerAddress_.x) { continue; }

					if (shadow.GetMapChip()[i][centerAddress_.y] != 0) {


						if (shadow.GetMapChip()[i][centerAddress_.y] == 1) {
							SaveData::playerShadowPos_ = pos_.operator+({ 0.0f,-1.0f });// 通常影
							break;

						} else if (shadow.GetMapChip()[i][centerAddress_.y] == 11) {// スイッチ影
							if (map.GetIsPressSwitch()) {
								SaveData::playerShadowPos_ = pos_.operator+({ 0.0f,-1.0f });
								break;
							}
						} else if (shadow.GetMapChip()[i][centerAddress_.y] == 2) {// とげ
							break;
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
}

void PlayerShadow::Draw(const Resources& rs, Screen screen) {

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

		if (isAlive_) {

			//追尾する星
			for (int i = 0; i < starFollowPos_.size(); i++) {
				//星アイテム
				My::DrawStar(
					starFollowPos_[i],
					(size_.x * 0.6f) / (1.0f + (CheckLength(starFollowPos_[i], pos_) * 0.01f * 2.0f)),
					{ cosf((starTheta_[i] / 120.0f) * float(M_PI)),1.0f },
					(starTheta_[i] / 120.0f) * float(M_PI),
					0x3f3f3fff
				);
			}

			//プレイヤー
			if (!isJump_) {

				if (fabsf(velocity_.x) <= 2 && fabsf(velocity_.y) <= 2) {
					//停止しているとき-------------------------------------

					DrawCat(
						{
							pos_.x,
							(pos_.y + 4.0f) - fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI)))
						},
						(size_.x + 8.0f) - fabsf(8.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))),
						(size_.y - 4.0f) + fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))),
						0x555555ff
					);

					for (int i = 1; i < 5; i++) {
						DrawCat(
							{
							pos_.x,
							(pos_.y + 4.0f) - fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI)))
							},
							(size_.x + 8.0f) - fabsf(8.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))) + i * 0.6f,
							(size_.y - 4.0f) + fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))) + i * 0.6f,
							0x55555555);
					}
				} else {//左右移動しているとき-------------------------------------

					DrawCat(
						{
							pos_.x,
							(pos_.y + 8.0f) - fabsf(8.0f * cosf((float(Global::timeCount_) / 24.0f) * float(M_PI)))
						},
						size_.x - fabsf(4.0f * cosf((float(Global::timeCount_) / 24.0f) * float(M_PI))),
						(size_.y - 8.0f) + fabsf(8.0f * cosf((float(Global::timeCount_) / 24.0f) * float(M_PI))),
						0x555555ff
					);

					for (int i = 1; i < 5; i++) {
						DrawCat(
							{
								pos_.x,
								(pos_.y + 8.0f) - fabsf(8.0f * cosf((float(Global::timeCount_) / 24.0f) * float(M_PI)))
							},
							size_.x - fabsf(4.0f * cosf((float(Global::timeCount_) / 24.0f) * float(M_PI))) + i * 0.6f,
							(size_.y - 8.0f) + fabsf(8.0f * cosf((float(Global::timeCount_) / 24.0f) * float(M_PI))) + i * 0.6f,
							0x55555555
						);
					}
				}
			} else {//ジャンプ
				DrawCat(
					{ pos_.x,pos_.y + size_.y * 0.2f },
					(size_.x * 0.5f) + ((size_.x * 0.7f) * (float(jumpTimer_) / 46.0f)),
					size_.y * 1.2f - ((size_.y) * (float(jumpTimer_) / 42.0f)),
					0x555555ff
				);

				for (int i = 1; i < 5; i++) {
					DrawCat(
						{ pos_.x,pos_.y + size_.y * 0.2f },
						(size_.x * 0.5f) + ((size_.x * 0.7f) * (float(jumpTimer_) / 46.0f)) + i * 0.6f,
						size_.y * 1.2f - ((size_.y) * (float(jumpTimer_) / 42.0f)) + i * 0.6f,
						0x55555555
					);
				}
			}




			if (Global::character_ == 0) {

				if (waitTimer_ > 240) {

					//W
					Novice::DrawSpriteRect(
						int(pos_.x - size_.x * 0.5f),
						int(pos_.y - size_.y * 0.5f - 32) - int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
						0, 0,
						32, 32,
						rs.keysGH_,
						32.0f / 128.0f, 32.0f / 94.0f,
						0.0f,
						0xffffff3f + int(float(0x2f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
					);

					//A
					Novice::DrawSpriteRect(
						int(pos_.x - size_.x * 0.5f - 32) - int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
						int(pos_.y - size_.y * 0.5f),
						32, 0,
						32, 32,
						rs.keysGH_,
						32.0f / 128.0f, 32.0f / 94.0f,
						0.0f,
						0xffffff3f + int(float(0x2f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
					);


					//D
					Novice::DrawSpriteRect(
						int(pos_.x + size_.x * 0.5f) + int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
						int(pos_.y - size_.y * 0.5f),
						64, 0,
						32, 32,
						rs.keysGH_,
						32.0f / 128.0f, 32.0f / 94.0f,
						0.0f,
						0xffffff3f + int(float(0x2f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
					);

				}
			} else {

				if (Global::controlMode_ == 0) {
					//W
					/*Novice::DrawSpriteRect(
						int(pos_.x - size_.x * 1.5f),
						int(pos_.y - size_.y * 0.5f - 32) - int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
						0, 0,
						96, 32,
						rs.changeGH_[1],
						1, 1,
						0.0f,
						0x1f1f1f3f + int(float(0x2f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
					);*/

				} else {

					//W
					/*Novice::DrawSpriteRect(
						int(pos_.x - size_.x * 1.0f),
						int(pos_.y - size_.y * 0.5f - 32) - int(4.0f * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
						0, 0,
						64, 32,
						rs.changeGH_[0],
						1, 1,
						0.0f,
						0x1f1f1f3f + int(float(0x2f) * cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))
					);*/


				}
			}

		} else {

			if (respawnTimeCount_ < 45) {

				if (respawnTimeCount_ < 24) {
					DrawCat(
						{
							pos_.x,
							(pos_.y)
							- fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI)))
						},
						(size_.x + 8.0f) - fabsf(8.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))),
						(size_.y - 4.0f) + fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))),
						0x555555ff
					);

					for (int i = 1; i < 5; i++) {
						DrawCat(
							{
							pos_.x,
							pos_.y
							- fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI)))
							},
							(size_.x + 8.0f) - fabsf(8.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))) + i * 0.6f,
							(size_.y - 4.0f) + fabsf(4.0f * cosf((float(Global::timeCount_) / 56.0f) * float(M_PI))) + i * 0.6f,
							0x55555555);
					}
				}

				for (int i = 0; i < 4; i++) {
					Novice::DrawEllipse(
						int(pos_.x),
						int(pos_.y),
						int((size_.x - 4) * sinf(((45.0f - float(respawnTimeCount_)) / 45.0f) * float(M_PI)) + i * 2),
						int((size_.y - 4) * sinf(((45.0f - float(respawnTimeCount_)) / 45.0f) * float(M_PI)) + i * 2),
						0.0f,
						0x3f3f3f7f,
						kFillModeSolid
					);
				}
			}

			if (preIsAlive_) {
				//死亡効果音
				killedSEHandle_ = Novice::PlayAudio(rs.playerKilledSE_, 0, 0.5f);
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

void PlayerShadow::PlayerShadowManager(const Resources& rs, PlayerShadow playerShadow) {
	DrawResetAction(rs, 155 - (respawnTimeCount_), 138);
}

void PlayerShadow::DrawResetAction(const Resources& rs, int timeCount, int kActionTime) {

	switch (Scene::sceneNum_) {

	case TITLE:
		break;

	case SELECT:
		break;

	case GAME:

		if (Global::character_ == 0) {
			for (int i = 0; i < 5; i++) {
				Novice::DrawBox(
					int(pos_.x - 40 - i * 2),
					int(pos_.y - 80 - i * 2),
					84 + i * 4,
					42 + i * 4,
					0.0f,
					0x00000000 + int(float(0x26) * (float(goalTutorialAlpha_) / float(0xff))),
					kFillModeSolid
				);
			}


			if (Global::controlMode_ == 1) {

				//ゴール
				My::DrawQuad(
					{
						pos_.x,
						pos_.y - 55.0f
					},
					{ 46.0f,46.0f },
					0, 0,
					32,
					32,
					1.0f,
					1.0f,
					rs.changeGH_[0],
					0.0f,
					0xffffff00 + goalTutorialAlpha_
				);

			} else {
				//ゴール
				My::DrawQuad(
					{
						pos_.x + 2.0f,
						pos_.y - 60.0f
					},
					{ 92.0f,46.0f },
					0, 0,
					64,
					128,
					1.0f,
					1.0f,
					rs.tutorial_[1],
					0.0f,
					0xffffff00 + goalTutorialAlpha_
				);
			}
		}


		if (!isAlive_) {

			const int kRowMax = 2;
			const int kColMax = 8;

			kActionTime;
			timeCount;

			Vec2 pos[kRowMax][kColMax] = { 0.0f };
			Vec2 size[kRowMax][kColMax] = { 0.0f };
			float moveT[kRowMax][kColMax] = { 0.0f };

			float devideTime = (float(kActionTime) / kColMax) / 4;

			//表示する情報の決定
			for (int i = 0; i < kRowMax; i++) {
				for (int j = 0; j < kColMax; j++) {

					size[i][j] = { float(Global::windowSize_.x) / float(kColMax), float(Global::windowSize_.y) };
					size[i][j].y += size[i][j].y * i;
				}
			}

			for (int i = 0; i < kRowMax; i++) {
				for (int j = 0; j < kColMax; j++) {
					//座標の初期化
					pos[i][j].x = (float(Global::windowSize_.x) / float(kColMax)) * j + (float(Global::windowSize_.x) / float(kColMax * 2));
					pos[i][j].y = -size[i][j].y / 2.0f;

					//媒介へ変数Tの決定
					moveT[i][j] = (float(timeCount) - devideTime * j) / (float(kActionTime) - devideTime * j);

					devideTime;

					//0~1に収める
					if (moveT[i][j] > 1.0f) {
						moveT[i][j] = 1.0f;
					} else if (moveT[i][j] < 0.0f) {
						moveT[i][j] = 0.0f;
					}
				}
			}

			for (int i = 0; i < kRowMax; i++) {
				for (int j = 0; j < kColMax; j++) {

					//媒介変数Tに応じて座標を更新
					pos[i][j].y = pos[kRowMax - 1][j].y +
						((-pos[kRowMax - 1][j].y * 2.0f) + Global::windowSize_.y) * EaseInOutExpo(moveT[i][j]);

				}
			}

			int color = 0x7f;

			//描画
			for (int i = kRowMax - 1; i >= 0; i--) {
				for (int j = 0; j < kColMax; j++) {

					Novice::DrawQuad(
						int(pos[i][j].x - size[i][j].x * 0.5f),
						int(pos[i][j].y - size[i][j].y * 0.5f + size[i][j].x),
						int(pos[i][j].x + size[i][j].x * 0.5f),
						int(pos[i][j].y - size[i][j].y * 0.5f + size[i][j].x),
						int(pos[i][j].x - size[i][j].x * 0.5f),
						int(pos[i][j].y + size[i][j].y * 0.5f - size[i][j].x),
						int(pos[i][j].x + size[i][j].x * 0.5f),
						int(pos[i][j].y + size[i][j].y * 0.5f - size[i][j].x),
						0, 0,
						1, 1,
						rs.whiteGH_,
						0x3f3f3fff + ((color * (j % 2)) << 8) + ((color * (j % 2)) << 16) + ((color * (j % 2)) << 24)
					);
				}
			}

			for (int j = 0; j < kColMax; j++) {
				My::DrawStar(
					{
					pos[kRowMax - 1][j].x,
					pos[kRowMax - 1][j].y + size[kRowMax - 1][j].y * 0.5f - size[0][j].x
					},
					size[0][j].x,
					(float(Global::timeCount_) / 64.0f) * float(M_PI),
					0x3f3f3fff + ((color * (j % 2)) << 8) + ((color * (j % 2)) << 16) + ((color * (j % 2)) << 24)
				);


				My::DrawStar(
					{
					pos[kRowMax - 1][j].x,
					pos[kRowMax - 1][j].y - size[kRowMax - 1][j].y * 0.5f + size[0][j].x
					},
					size[0][j].x,
					(float(Global::timeCount_) / 64.0f) * float(M_PI),
					0x3f3f3fff + ((color * (j % 2)) << 8) + ((color * (j % 2)) << 16) + ((color * (j % 2)) << 24)
				);

			}
		}
		break;

	case CLEAR:
		break;

	default:
		break;

	}
}

void PlayerShadow::DrawFrame(Map map, Screen screen) {

	if (Scene::sceneNum_ == GAME) {

		switch (Global::character_) {

		case 0:

			Novice::DrawBox(
				int(screen.GetScreenLeftTop().x),
				int(screen.GetScreenLeftTop().y),
				int(screen.GetSize().x),
				int(screen.GetSize().y),
				0.0f,
				0xffffffff,
				kFillModeWireFrame
			);

			for (int i = 0; i < 12; i++) {

				Novice::DrawBox(
					int(screen.GetScreenLeftTop().x) - i,
					int(screen.GetScreenLeftTop().y) - i,
					int(screen.GetSize().x) + i * 2,
					int(screen.GetSize().y) + i * 2,
					0.0f,
					0xffffa500 + int((float(0xff) * (1.0f / i)) * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
					kFillModeWireFrame
				);
			}

			break;

		case 1:

			Novice::DrawBox(
				int(map.GetPuzzleLeftTop().x),
				int(map.GetPuzzleLeftTop().y),
				int(map.GetPuzzleMapSize().x),
				int(map.GetPuzzleMapSize().y),
				0.0f,
				0xffffffff,
				kFillModeWireFrame
			);

			for (int i = 0; i < 12; i++) {

				Novice::DrawBox(
					int(map.GetPuzzleLeftTop().x) - i,
					int(map.GetPuzzleLeftTop().y) - i,
					int(map.GetPuzzleMapSize().x) + i * 2,
					int(map.GetPuzzleMapSize().y) + i * 2,
					0.0f,
					0xffffa500 + int((float(0xff) * (1.0f / i)) * fabsf(cosf((float(Global::timeCount_) / 64.0f) * float(M_PI)))),
					kFillModeWireFrame
				);
			}

			break;

		default:
			break;
		}

	}
}
