#include "PlayerShadow.h"

void PlayerShadow::Init(int sceneNum, Screen screen, Shadow shadow) {

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

		pos_ = {
		shadow.firstPlayerPos_.x + screen.GetScreenLeftTop().x,
		shadow.firstPlayerPos_.y + screen.GetScreenLeftTop().y,
		};
		prePos_ = pos_;
		prePosCopy_ = prePos_;

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

		isInsideLightLB_ = false;
		isInsideLightRB_ = false;
		isInsideLightLT_ = false;
		isInsideLightRT_ = false;
		preIsInsideLightLB_ = false;
		preIsInsideLightRB_ = false;
		preIsInsideLightLT_ = false;
		preIsInsideLightRT_ = false;

		starGetCount_ = 0;
		break;

	case CLEAR:
		break;

	default:
		break;
	}
}

void PlayerShadow::Update(char* keys,char* Prekeys, const Resources& rs, ChangeScene& cs, Screen& screen, Shadow& shadow, Player& player, Map& map, Light& light, bool isPause) {

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(Scene::sceneNum_, screen, shadow);
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
			Init(Scene::sceneNum_, screen, shadow);
		}
		if (!isPause&&!cs.isEndChange_&&!cs.isStartChange_) {
			//前のフレームの情報保存に関するもの
			prePos_ = pos_;
			prePosCopy_ = prePos_;
			preIsAlive_ = isAlive_;
			preIsBackToRespawnPos_ = isBackToRespawnPos_;

			preIsInsideLightLB_ = isInsideLightLB_;
			preIsInsideLightRB_ = isInsideLightRB_;
			preIsInsideLightLT_ = isInsideLightLT_;
			preIsInsideLightRT_ = isInsideLightRT_;

			/*----------------------------死んだときの処理-----------------------------*/

			if (!isAlive_) {
				respawnTimeCount_--;

				if (respawnTimeCount_ < 80) {

					if (respawnTimeCount_ == 79) {

						map.Init(rs, Scene::sceneNum_);
						player.Init(Scene::sceneNum_, map);
						light.Init(Scene::sceneNum_, map);
						screen.Init(Scene::sceneNum_, map, light);
						shadow.Init(rs, screen, Scene::sceneNum_);
					}

					isBackToRespawnPos_ = true;

					if (respawnTimeCount_ <= 0) {
						Init(Scene::sceneNum_, screen, shadow);
					}
				}
			} else {

				//配列数の決定
				if (hitSurface_.size() != screen.GetPos().size()) {

					hitSurface_.clear();

					for (int i = 0; i < screen.GetPos().size(); i++) {

						hitSurface_.push_back(0);
					}
				}

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

				//ジャンプ
				if (isJump_) {
					jumpSpeed_ = jumpVelocity_;

				} else {

					if (!isDrop_) {
						if (keys[DIK_W]) {

							isJump_ = true;
							isDrop_ = true;
							jumpSpeed_ = jumpVelocity_;

						} else {
							jumpSpeed_ = 0.0f;
						}
					}

				}

				if (pos_.y < (screen.GetScreenLeftTop().y + screen.GetSize().y) - size_.y * 0.5f) {

					if (!isInsideLightLB_ && !isInsideLightRB_) {
						isDrop_ = true;
					}
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
										if (!isInsideLightLB_ && !isInsideLightRB_) {
											isDrop_ = true;
										}
									}

								} else {
									if (!isInsideLightLB_ && !isInsideLightRB_) {
										isDrop_ = true;
									}
								}
							} else {
								if (!isInsideLightLB_ && !isInsideLightRB_) {
									isDrop_ = true;
								}
							}
						} else {
							if (!isInsideLightLB_ && !isInsideLightRB_) {
								isDrop_ = true;
							}
						}
					} else {
						if (!isInsideLightLB_ && !isInsideLightRB_) {
							isDrop_ = true;
						}
					}

				}

				//ジャンプ
				if (!isJump_) {

					if (!isDrop_) {
						if (keys[DIK_W]) {

							isJump_ = true;
							isDrop_ = true;
							jumpSpeed_ = jumpVelocity_;

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
				direction_.x = float(keys[DIK_D] - keys[DIK_A]);

				velocity_.x = Normalize({ 0.0f,0.0f }, direction_).x;

				velocity_.x *= speed_;

				if (hitCount_ < 2) {
					pos_.x += velocity_.x;
					pos_.y += velocity_.y;
				}


				//乗っている影ブロックが動けば一緒に動く--------------------------------------
				if (boardingBlock_ >= 0) {
					if (isJump_) {
						boardingBlock_ = -1;
					}
				}

				preBoadingVecRatio_ = boadingVecRatio_;

				for (int i = 0; i < screen.GetPos().size(); i++) {

					hitSurface_[i] = 0;

					//
					if (boardingBlock_ >= 0) {

						boardingPos_ = CrossPos(
							screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
							pos_, { pos_.x,pos_.y + 1.0f }
						);

						boadingVecRatio_ = Dot(
							screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1),
							pos_
						);


						if (boadingVecRatio_ >= 0.0f &&
							boadingVecRatio_ <= CheckLength(screen.GetPos(boardingBlock_, 0), screen.GetPos(boardingBlock_, 1))) {
							if (Global::isMoveShadow_) {
								pos_.x = screen.GetPos(boardingBlock_, 0).x +
									Normalize(screen.GetPos(boardingBlock_, 1), screen.GetPos(boardingBlock_, 0)).x * preBoadingVecRatio_;
								pos_.y = screen.GetPos(boardingBlock_, 0).y +
									Normalize(screen.GetPos(boardingBlock_, 1), screen.GetPos(boardingBlock_, 0)).y * preBoadingVecRatio_
									- (size_.y * 0.5f);

								isDrop_ = false;
							}

							Novice::ScreenPrintf(0, 100, "%f", boadingVecRatio_);

						} else {
							boardingBlock_ = -1;
						}
					}
				}

				if (!Global::isMoveShadow_) {
					boardingBlock_ = -1;
				}

				/*-------------------------------押し戻し-------------------------------*/

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
				CalcAddress(
					address_,
					{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y + 1 },
					{ shadow.GetSize().x,shadow.GetSize().y },
					size_.x * 0.5f,
					int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
				);


				isInsideLightLB_ = false;
				isInsideLightRB_ = false;
				isInsideLightLT_ = false;
				isInsideLightRT_ = false;

				if (address_[2].y < shadow.GetMapChip().size()) {

					if (shadow.GetMapChip()[address_[0].y][address_[0].x] == 7) {
						isInsideLightLT_ = true;
					} else {
						isInsideLightLT_ = false;
					}

					if (shadow.GetMapChip()[address_[1].y][address_[1].x] == 7) {
						isInsideLightRT_ = true;
					} else {
						isInsideLightRT_ = false;
					}

					if (shadow.GetMapChip()[address_[2].y][address_[2].x] == 7) {
						isInsideLightLB_ = true;
					} else {
						isInsideLightLB_ = false;
					}

					if (shadow.GetMapChip()[address_[3].y][address_[3].x] == 7) {
						isInsideLightRB_ = true;
					} else {
						isInsideLightRB_ = false;
					}

					if (shadow.GetMapChip()[address_[2].y][address_[2].x] == 7 &&
						shadow.GetMapChip()[address_[3].y][address_[3].x] == 7) {
						return;
					}
				}

				//光が照らされて影が映らない場所の処理
				for (int i = 0; i < screen.GetPos().size(); i++) {

					if (!preIsInsideLightLT_ && !preIsInsideLightRT_ && !preIsInsideLightLB_ && !preIsInsideLightRB_) {
						break;
					}
					int loop = 0;

					//左上頂点が光から外れた時--------------------------------------------------------------------------------------------------------
					if (!isInsideLightLT_ && preIsInsideLightLT_) {

						//矩形に当たっていれば
						if (ColisionBox_Ball(screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
							{ pos_.x - size_.x * 0.5f,pos_.y - size_.y * 0.5f },
							0
						)) {

							//当たらなくなるまで押し戻す
							Vec2 pushBackVec = Normalize(prePos_, pos_);

							if (address_[0].x != preAddress_[0].x && address_[0].y == preAddress_[0].y) {
								if (pos_.x > prePos_.x) {
									pushBackVec = { -1.0f,0.0f };
								} else {
									pushBackVec = { 1.0f,0.0f };
								}

							} else if (address_[0].x == preAddress_[0].x && address_[0].y != preAddress_[0].y) {
								if (pos_.y > prePos_.y) {
									pushBackVec = { 0.0f,-1.0f };
									isDrop_ = false;
									isJump_ = false;
									jumpSpeed_ = 0.0f;
									dropSpeed_ = 0.0f;
								} else {
									pushBackVec = { 0.0f,1.0f };
								}
							} else {
								pushBackVec = Normalize(prePos_, pos_);
							}

							while (shadow.GetMapChip()[address_[0].y][address_[0].x] != 7) {

								pos_ = pos_.operator+(pushBackVec);

								CalcAddress(
									address_,
									{ pos_.x - screen.GetScreenLeftTop().x,pos_.y - screen.GetScreenLeftTop().y },
									{ shadow.GetSize().x,shadow.GetSize().y },
									size_.x * 0.5f,
									int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
								);

								loop++;
								if (loop > 640) {
									break;
								}

								if ((address_[0].x < 0 or address_[0].x >= shadow.GetPos()[0].size()) or
									(address_[0].y < 0 or address_[0].y >= shadow.GetPos().size())) {
									break;
								}

							}
						}
					}

					//右上頂点が光から外れた時--------------------------------------------------------------------------------------------------------
					if (!isInsideLightRT_ && preIsInsideLightRT_) {

						if (ColisionBox_Ball(screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
							{ pos_.x + size_.x * 0.5f,pos_.y - size_.y * 0.5f },
							0
						)) {

							//当たらなくなるまで押し戻す
							Vec2 pushBackVec = Normalize(prePos_, pos_);
							if (address_[1].x != preAddress_[1].x && address_[1].y == preAddress_[1].y) {
								if (pos_.x > prePos_.x) {
									pushBackVec = { -1.0f,0.0f };
								} else {
									pushBackVec = { 1.0f,0.0f };
								}

							} else if (address_[1].x == preAddress_[1].x && address_[1].y != preAddress_[1].y) {
								if (pos_.y > prePos_.y) {
									pushBackVec = { 0.0f,-1.0f };
									isDrop_ = false;
									isJump_ = false;
									jumpSpeed_ = 0.0f;
									dropSpeed_ = 0.0f;
								} else {
									pushBackVec = { 0.0f,1.0f };
								}
							} else {
								pushBackVec = Normalize(prePos_, pos_);
							}

							while (shadow.GetMapChip()[address_[1].y][address_[1].x] != 7) {

								pos_ = pos_.operator+(pushBackVec);

								CalcAddress(
									address_,
									{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y },
									{ shadow.GetSize().x,shadow.GetSize().y },
									size_.x * 0.5f,
									int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
								);

								loop++;
								if (loop > 640) {
									break;
								}

								if ((address_[1].x < 0 or address_[1].x >= shadow.GetPos()[0].size()) or
									(address_[1].y < 0 or address_[1].y >= shadow.GetPos().size())) {
									break;
								}
							}
						}
					}

					//左下頂点が光から外れた時--------------------------------------------------------------------------------------------------------
					if (!isInsideLightLB_ && preIsInsideLightLB_) {

						//矩形に当たっていれば
						if (ColisionBox_Ball(screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
							{ pos_.x - size_.x * 0.5f,pos_.y + size_.y * 0.5f },
							0
						)) {

							//当たらなくなるまで押し戻す
							Vec2 pushBackVec = Normalize(prePos_, pos_);
							if (address_[2].x != preAddress_[2].x && address_[2].y == preAddress_[2].y) {
								if (pos_.x > prePos_.x) {
									pushBackVec = { -1.0f,0.0f };
								} else {
									pushBackVec = { 1.0f,0.0f };
								}

							} else if (address_[2].x == preAddress_[2].x && address_[2].y != preAddress_[2].y) {
								if (pos_.y > prePos_.y) {
									pushBackVec = { 0.0f,-1.0f };
									isDrop_ = false;
									isJump_ = false;
									jumpSpeed_ = 0.0f;
									dropSpeed_ = 0.0f;
								} else {
									pushBackVec = { 0.0f,1.0f };
								}
							} else {
								pushBackVec = Normalize(prePos_, pos_);
							}

							while (shadow.GetMapChip()[address_[2].y][address_[2].x] != 7) {

								pos_ = pos_.operator+(pushBackVec);

								CalcAddress(
									address_,
									{ pos_.x - screen.GetScreenLeftTop().x,pos_.y - screen.GetScreenLeftTop().y + 1 },
									{ shadow.GetSize().x,shadow.GetSize().y },
									size_.x * 0.5f,
									int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
								);

								loop++;
								if (loop > 640) {
									break;
								}

								if ((address_[2].x < 0 or address_[2].x >= shadow.GetPos()[0].size()) or
									(address_[2].y < 0 or address_[2].y >= shadow.GetPos().size())) {
									break;
								}

							}
						}
					}

					//右下頂点が光から外れた時--------------------------------------------------------------------------------------------------------
					if (!isInsideLightRB_ && preIsInsideLightRB_) {

						if (ColisionBox_Ball(screen.GetPos(i, 0), screen.GetPos(i, 1), screen.GetPos(i, 2), screen.GetPos(i, 7),
							{ pos_.x + size_.x * 0.5f,pos_.y + size_.y * 0.5f },
							0
						)) {

							//当たらなくなるまで押し戻す
							Vec2 pushBackVec = Normalize(prePos_, pos_);
							if (address_[3].x != preAddress_[3].x && address_[3].y == preAddress_[3].y) {
								if (pos_.x > prePos_.x) {
									pushBackVec = { -1.0f,0.0f };
								} else {
									pushBackVec = { 1.0f,0.0f };
								}

							} else if (address_[3].x == preAddress_[3].x && address_[3].y != preAddress_[3].y) {
								if (pos_.y > prePos_.y) {
									pushBackVec = { 0.0f,-1.0f };
									isDrop_ = false;
									isJump_ = false;
									jumpSpeed_ = 0.0f;
									dropSpeed_ = 0.0f;
								} else {
									pushBackVec = { 0.0f,1.0f };
								}
							} else {
								pushBackVec = Normalize(prePos_, pos_);
							}

							while (shadow.GetMapChip()[address_[3].y][address_[3].x] != 7) {

								pos_ = pos_.operator+(pushBackVec);

								CalcAddress(
									address_,
									{ pos_.x - screen.GetScreenLeftTop().x + 1,pos_.y - screen.GetScreenLeftTop().y + 1 },
									{ shadow.GetSize().x,shadow.GetSize().y },
									size_.x * 0.5f,
									int(shadow.GetPos().size()), int(shadow.GetPos()[0].size())
								);

								loop++;
								if (loop > 640) {
									break;
								}

								if ((address_[3].x < 0 or address_[3].x >= shadow.GetPos()[0].size()) or
									(address_[3].y < 0 or address_[3].y >= shadow.GetPos().size())) {
									break;
								}
							}
						}
					}
				}


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
								shadow.SetMapChip(i2, j2, 0);
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

				Novice::ScreenPrintf(0, 40, "%d", isDrop_);

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
							isAlive_ = false;
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
				if (ColisionBox_Ball(shadow.GetGoalLT(), shadow.GetGoalRT(), shadow.GetGoalLB(), shadow.GetGoalRB(), pos_, (size_.x / 10))) {
					if (keys[DIK_SPACE]&&!Prekeys[DIK_SPACE]) {
						cs.isEndChange_ = true;
					}
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

			Novice::ScreenPrintf(0, 60, "%d", boardingBlock_);

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

void PlayerShadow::Draw(Screen screen) {

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
			Novice::DrawEllipse(
				int(pos_.x),
				int(pos_.y),
				int(size_.x * 0.5f),
				int(size_.y * 0.5f),
				0.0f,
				0x000000ff,
				kFillModeSolid
			);
			DrawCat(pos_, size_.x, size_.y, 0x000000ff);
		}

		Novice::ScreenPrintf(0, 20, "%f", pos_.y);

		break;

		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}
}
