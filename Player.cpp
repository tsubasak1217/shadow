#include "Player.h"

//====================================================初期化関数=============================================================
void Player::Init(int sceneNum,Map map) {

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
			map.firstPlayerPos_.x + map.GetPuzzleLeftTop().x,
			map.firstPlayerPos_.y + map.GetPuzzleLeftTop().y,
		};
		prePos_ = pos_;

		size_ = { 24.0f,24.0f };
		direction_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		speed_ = 4.0f;
		for (int i = 0; i < 4; i++) {
			address_[i] = { 0,0 };
			preAddress_[i] = address_[i];
		}
		centerAddress_ = { 0,0 };

		isMoveBlock_ = false;
		blockMoveT_ = 0.0f;
		moveTime_ = 32;
		moveDirection_ = 0;
		moveBlockAddress_ = { 0,0 };
		moveStartPos_ = { 0.0f,0.0f };
		savedPlayerPos_ = { 0.0f,0.0f };

		isHitMapChip_ = 0;

		isSwitchPushable_ = true;

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
void Player::Update(char* keys, const ChangeScene& cs, Map& map) {

	//シーン遷移の始まった瞬間にシーンに合わせて初期化
	if (cs.isStartChange_ && cs.preIsEndChange_) {
		Init(Scene::sceneNum_, map);
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

		//前のフレームの情報保存に関するもの
		prePos_ = pos_;

		/*------------------------------ブロックを動かすフラグを立てる-------------------------------*/
		if (!isMoveBlock_) {

			for (int i = 0; i < 4; i++) {

				if (address_[i].x >= 0 && address_[i].x < map.GetMapChip()[0].size()) {
					if (address_[i].y >= 0 && address_[i].y < map.GetMapChip().size()) {

						switch (i) {

						case LeftTop://---------------------------------------------------------------------------------------
							if (keys[DIK_SPACE]) {

								if (keys[DIK_RIGHT]) {

									//左側にブロックがあり
									if (address_[i].x - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y][address_[i].x - 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x - 1] <= 2) {

												//すぐ左にブロックがあるとき(接しているとき)
												if (pos_.x - 2 <=
													map.GetPos()[address_[i].y][address_[i].x - 1].x
													+ (map.GetSize().x * 0.5f) + (size_.x * 0.5f)) {

													//プレイヤーの右側が空いていれば
													if (address_[i].x + 1 < map.GetMapChip()[0].size()) {
														if (map.GetMapChip()[address_[i].y][address_[i].x + 1] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Right;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x - 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x - 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_LEFT]) {

									//左側にブロックがあり
									if (address_[i].x - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y][address_[i].x - 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x - 1] <= 2) {

												//すぐ左にブロックがあるとき(接しているとき)
												if (pos_.x - 2 <=
													map.GetPos()[address_[i].y][address_[i].x - 1].x
													+ (map.GetSize().x * 0.5f) + (size_.x * 0.5f)) {

													//動かすブロックの左側が空いていれば
													if (address_[i].x - 2 >= 0) {
														if (map.GetMapChip()[address_[i].y][address_[i].x - 2] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Left;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x - 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x - 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}

								if (keys[DIK_UP]) {

									//上側にブロックがあり
									if (address_[i].y - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y - 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y - 1][address_[i].x] <= 2) {

												//すぐ上にブロックがあるとき(接しているとき)
												if (pos_.y - 2 <=
													map.GetPos()[address_[i].y - 1][address_[i].x].y
													+ (map.GetSize().y * 0.5f) + (size_.y * 0.5f)) {

													//ブロックのの上側が空いていれば
													if (address_[i].y - 2 >= 0) {
														if (map.GetMapChip()[address_[i].y - 2][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Top;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y - 1 };
															moveStartPos_ = map.GetPos()[address_[i].y - 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_DOWN]) {

									//上側にブロックがあり
									if (address_[i].y - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y - 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y - 1][address_[i].x] <= 2) {

												//すぐ上にブロックがあるとき(接しているとき)
												if (pos_.y - 2 <=
													map.GetPos()[address_[i].y - 1][address_[i].x].y
													+ (map.GetSize().x * 0.5f) + (size_.x * 0.5f)) {

													//プレイヤーの下側が空いていれば
													if (address_[i].y + 1 < map.GetMapChip().size()) {
														if (map.GetMapChip()[address_[i].y + 1][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Bottom;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y - 1 };
															moveStartPos_ = map.GetPos()[address_[i].y - 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}
							}

							break;

						case RightTop://---------------------------------------------------------------------------------------

							if (keys[DIK_SPACE]) {

								if (keys[DIK_RIGHT]) {

									//右側にブロックがあり
									if (address_[i].x + 1 < map.GetMapChip()[0].size()) {
										if (map.GetMapChip()[address_[i].y][address_[i].x + 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x + 1] <= 2) {

												//プレイヤーが右のブロックと接しているとき
												if (pos_.x + 2 >=
													map.GetPos()[address_[i].y][address_[i].x + 1].x
													- (map.GetSize().x * 0.5f) - (size_.x * 0.5f)) {

													//動かすブロックの右が空いているとき
													if (address_[i].x + 2 < map.GetMapChip()[0].size()) {
														if (map.GetMapChip()[address_[i].y][address_[i].x + 2] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Right;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x + 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x + 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_LEFT]) {

									//右側にブロックがあり
									if (address_[i].x + 1 < map.GetMapChip()[0].size()) {
										if (map.GetMapChip()[address_[i].y][address_[i].x + 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x + 1] <= 2) {

												//プレイヤーが右のブロックと接しているとき
												if (pos_.x + 2 >=
													map.GetPos()[address_[i].y][address_[i].x + 1].x
													- (map.GetSize().x * 0.5f) - (size_.x * 0.5f)) {

													//動かすブロックの左側が空いていれば
													if (address_[i].x - 1 >= 0) {
														if (map.GetMapChip()[address_[i].y][address_[i].x - 1] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Left;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x + 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x + 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}

								if (keys[DIK_UP]) {

									//上側にブロックがあり
									if (address_[i].y - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y - 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y - 1][address_[i].x] <= 2) {

												//すぐ上にブロックがあるとき(接しているとき)
												if (pos_.y - 2 <=
													map.GetPos()[address_[i].y - 1][address_[i].x].y
													+ (map.GetSize().y * 0.5f) + (size_.y * 0.5f)) {

													//ブロックのの上側が空いていれば
													if (address_[i].y - 2 >= 0) {
														if (map.GetMapChip()[address_[i].y - 2][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Top;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y - 1 };
															moveStartPos_ = map.GetPos()[address_[i].y - 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_DOWN]) {

									//上側にブロックがあり
									if (address_[i].y - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y - 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y - 1][address_[i].x] <= 2) {

												//すぐ上にブロックがあるとき(接しているとき)
												if (pos_.y - 2 <=
													map.GetPos()[address_[i].y - 1][address_[i].x].y
													+ (map.GetSize().x * 0.5f) + (size_.x * 0.5f)) {

													//プレイヤーの下側が空いていれば
													if (address_[i].y + 1 < map.GetMapChip().size()) {
														if (map.GetMapChip()[address_[i].y + 1][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Bottom;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y - 1 };
															moveStartPos_ = map.GetPos()[address_[i].y - 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}
							}

							break;
						case LeftBottom://---------------------------------------------------------------------------------------

							if (keys[DIK_SPACE]) {

								if (keys[DIK_RIGHT]) {

									//左側にブロックがあり
									if (address_[i].x - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y][address_[i].x - 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x - 1] <= 2) {

												//すぐ左にブロックがあるとき(接しているとき)
												if (pos_.x - 2 <=
													map.GetPos()[address_[i].y][address_[i].x - 1].x
													+ (map.GetSize().x * 0.5f) + (size_.x * 0.5f)) {

													//プレイヤーの右側が空いていれば
													if (address_[i].x + 1 < map.GetMapChip()[0].size()) {
														if (map.GetMapChip()[address_[i].y][address_[i].x + 1] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Right;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x - 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x - 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_LEFT]) {

									//左側にブロックがあり
									if (address_[i].x - 1 >= 0) {
										if (map.GetMapChip()[address_[i].y][address_[i].x - 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x - 1] <= 2) {

												//すぐ左にブロックがあるとき(接しているとき)
												if (pos_.x - 2 <=
													map.GetPos()[address_[i].y][address_[i].x - 1].x
													+ (map.GetSize().x * 0.5f) + (size_.x * 0.5f)) {

													//動かすブロックの左側が空いていれば
													if (address_[i].x - 2 >= 0) {
														if (map.GetMapChip()[address_[i].y][address_[i].x - 2] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Left;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x - 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x - 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}

								if (keys[DIK_UP]) {

									//下側にブロックがあり
									if (address_[i].y + 1 < map.GetMapChip().size()) {
										if (map.GetMapChip()[address_[i].y + 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y + 1][address_[i].x] <= 2) {

												//すぐ下にブロックがあるとき(接しているとき)
												if (pos_.y + 2 >=
													map.GetPos()[address_[i].y + 1][address_[i].x].y
													- (map.GetSize().y * 0.5f) - (size_.y * 0.5f)) {

													//プレイヤーの上側が空いていれば
													if (address_[i].y - 1 >= 0) {
														if (map.GetMapChip()[address_[i].y - 1][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Top;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y + 1 };
															moveStartPos_ = map.GetPos()[address_[i].y + 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_DOWN]) {

									//下側にブロックがあり
									if (address_[i].y + 1 < map.GetMapChip().size()) {
										if (map.GetMapChip()[address_[i].y + 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y + 1][address_[i].x] <= 2) {

												//すぐ下にブロックがあるとき(接しているとき)
												if (pos_.y + 2 >=
													map.GetPos()[address_[i].y + 1][address_[i].x].y
													- (map.GetSize().y * 0.5f) - (size_.y * 0.5f)) {

													//動かすブロックの下側が空いていれば
													if (address_[i].y + 2 < map.GetMapChip().size()) {
														if (map.GetMapChip()[address_[i].y + 2][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Bottom;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y + 1 };
															moveStartPos_ = map.GetPos()[address_[i].y + 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}
							}

							break;

						case RightBottom://---------------------------------------------------------------------------------------

							if (keys[DIK_SPACE]) {

								if (keys[DIK_RIGHT]) {

									//右側にブロックがあり
									if (address_[i].x + 1 < map.GetMapChip()[0].size()) {
										if (map.GetMapChip()[address_[i].y][address_[i].x + 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x + 1] <= 2) {

												//プレイヤーが右のブロックと接しているとき
												if (pos_.x + 2 >=
													map.GetPos()[address_[i].y][address_[i].x + 1].x
													- (map.GetSize().x * 0.5f) - (size_.x * 0.5f)) {

													//動かすブロックの右が空いているとき
													if (address_[i].x + 2 < map.GetMapChip()[0].size()) {
														if (map.GetMapChip()[address_[i].y][address_[i].x + 2] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Right;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x + 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x + 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_LEFT]) {

									//右側にブロックがあり
									if (address_[i].x + 1 < map.GetMapChip()[0].size()) {
										if (map.GetMapChip()[address_[i].y][address_[i].x + 1] > 0) {
											if (map.GetMapChip()[address_[i].y][address_[i].x + 1] <= 2) {

												//プレイヤーが右のブロックと接しているとき
												if (pos_.x + 2 >=
													map.GetPos()[address_[i].y][address_[i].x + 1].x
													- (map.GetSize().x * 0.5f) - (size_.x * 0.5f)) {

													//動かすブロックの左側が空いていれば
													if (address_[i].x - 1 >= 0) {
														if (map.GetMapChip()[address_[i].y][address_[i].x - 1] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Left;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x + 1,address_[i].y };
															moveStartPos_ = map.GetPos()[address_[i].y][address_[i].x + 1];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}

								if (keys[DIK_UP]) {

									//下側にブロックがあり
									if (address_[i].y + 1 < map.GetMapChip().size()) {
										if (map.GetMapChip()[address_[i].y + 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y + 1][address_[i].x] <= 2) {

												//すぐ下にブロックがあるとき(接しているとき)
												if (pos_.y + 2 >=
													map.GetPos()[address_[i].y + 1][address_[i].x].y
													- (map.GetSize().y * 0.5f) - (size_.y * 0.5f)) {

													//プレイヤーの上側が空いていれば
													if (address_[i].y - 1 >= 0) {
														if (map.GetMapChip()[address_[i].y - 1][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Top;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y + 1 };
															moveStartPos_ = map.GetPos()[address_[i].y + 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								} else if (keys[DIK_DOWN]) {

									//下側にブロックがあり
									if (address_[i].y + 1 < map.GetMapChip().size()) {
										if (map.GetMapChip()[address_[i].y + 1][address_[i].x] > 0) {
											if (map.GetMapChip()[address_[i].y + 1][address_[i].x] <= 2) {

												//すぐ下にブロックがあるとき(接しているとき)
												if (pos_.y + 2 >=
													map.GetPos()[address_[i].y + 1][address_[i].x].y
													- (map.GetSize().y * 0.5f) - (size_.y * 0.5f)) {

													//動かすブロックの下側が空いていれば
													if (address_[i].y + 2 < map.GetMapChip().size()) {
														if (map.GetMapChip()[address_[i].y + 2][address_[i].x] <= 0) {

															//動かすフラグを立てる
															isMoveBlock_ = true;
															moveDirection_ = Bottom;
															//動かすブロックのアドレスを保存
															moveBlockAddress_ = { address_[i].x,address_[i].y + 1 };
															moveStartPos_ = map.GetPos()[address_[i].y + 1][address_[i].x];

															//プレイヤーの座標を保存
															savedPlayerPos_ = pos_;
														}
													}
												}
											}
										}
									}
								}
							}

							break;

						default:
							break;
						}
					}
				}
			}
		}



		/*-------------------------------移動処理-------------------------------*/
		velocity_ = { 0.0f,0.0f };

		direction_.x = float(keys[DIK_RIGHT] - keys[DIK_LEFT]);
		direction_.y = float(keys[DIK_DOWN] - keys[DIK_UP]);

		velocity_ = Normalize({ 0.0f,0.0f }, direction_);

		velocity_.x *= speed_;
		velocity_.y *= speed_;

		if (!isMoveBlock_) {
			pos_.x += velocity_.x;
			pos_.y += velocity_.y;
		}



		/*------------------------------ブロックを動かす-------------------------------*/
		if (isMoveBlock_) {

			switch (moveDirection_) {

			case Top:

				//ブロックの移動
				map.SetPos(
					moveBlockAddress_.y, moveBlockAddress_.x,
					{
					moveStartPos_.x,
					moveStartPos_.y + EaseInOutQuint(blockMoveT_) * -map.GetSize().y,
					}
				);

				//ブロックと一緒にプレイヤーも動く
				pos_.y = savedPlayerPos_.y + EaseInOutQuint(blockMoveT_) * -map.GetSize().y;


				break;

			case Right:

				//ブロックの移動
				map.SetPos(
					moveBlockAddress_.y, moveBlockAddress_.x,
					{
					moveStartPos_.x + EaseInOutQuint(blockMoveT_) * map.GetSize().x,
					moveStartPos_.y
					}
				);

				//ブロックと一緒にプレイヤーも動く
				pos_.x = savedPlayerPos_.x + EaseInOutQuint(blockMoveT_) * map.GetSize().x;

				break;

			case Bottom:

				//ブロックの移動
				map.SetPos(
					moveBlockAddress_.y, moveBlockAddress_.x,
					{
					moveStartPos_.x,
					moveStartPos_.y + EaseInOutQuint(blockMoveT_) * map.GetSize().y,
					}
				);

				//ブロックと一緒にプレイヤーも動く
				pos_.y = savedPlayerPos_.y + EaseInOutQuint(blockMoveT_) * map.GetSize().y;


				break;

			case Left:

				//ブロックの移動
				map.SetPos(
					moveBlockAddress_.y, moveBlockAddress_.x,
					{
					moveStartPos_.x + EaseInOutQuint(blockMoveT_) * -map.GetSize().x,
					moveStartPos_.y
					}
				);

				//ブロックと一緒にプレイヤーも動く
				pos_.x = savedPlayerPos_.x + EaseInOutQuint(blockMoveT_) * -map.GetSize().x;

				break;

			default:
				break;
			}

			//媒介変数を加算
			if (blockMoveT_ < 1.0f) {
				blockMoveT_ += (1.0f / moveTime_);

			} else if (blockMoveT_ >= 1.0f) {//-----------------------------------------------------

				//フラグと媒介変数を元に戻す
				isMoveBlock_ = false;
				blockMoveT_ = 0.0f;

				//ブロック番号を更新して座標を戻す
				switch (moveDirection_) {

				case Top:

					//座標を元に戻す
					map.SetPos(
						moveBlockAddress_.y, moveBlockAddress_.x,
						moveStartPos_
					);

					//マップチップ番号を0に更新
					map.SetMapChip(
						moveBlockAddress_.y - 1, moveBlockAddress_.x,
						map.GetMapChip()[moveBlockAddress_.y][moveBlockAddress_.x]
					);

					map.SetMapChip(
						moveBlockAddress_.y, moveBlockAddress_.x,
						0
					);

					if (centerAddress_.y < moveBlockAddress_.y) {
						pos_.y = map.GetPos()[moveBlockAddress_.y - 1][moveBlockAddress_.x].y - ((map.GetSize().y*0.5f )+ (size_.y * 0.5f)) - 1;
					}

					break;

				case Right:

					//座標を元に戻す
					map.SetPos(
						moveBlockAddress_.y, moveBlockAddress_.x,
						moveStartPos_
					);

					//マップチップ番号を0に更新
					map.SetMapChip(
						moveBlockAddress_.y, moveBlockAddress_.x + 1,
						map.GetMapChip()[moveBlockAddress_.y][moveBlockAddress_.x]
					);

					map.SetMapChip(
						moveBlockAddress_.y, moveBlockAddress_.x,
						0
					);

					break;

				case Bottom:

					//座標を元に戻す
					map.SetPos(
						moveBlockAddress_.y, moveBlockAddress_.x,
						moveStartPos_
					);

					//マップチップ番号を0に更新
					map.SetMapChip(
						moveBlockAddress_.y + 1, moveBlockAddress_.x,
						map.GetMapChip()[moveBlockAddress_.y][moveBlockAddress_.x]
					);

					map.SetMapChip(
						moveBlockAddress_.y, moveBlockAddress_.x,
						0
					);

					break;

				case Left:

					//座標を元に戻す
					map.SetPos(
						moveBlockAddress_.y, moveBlockAddress_.x,
						moveStartPos_
					);

					//マップチップ番号を0に更新
					map.SetMapChip(
						moveBlockAddress_.y, moveBlockAddress_.x - 1,
						map.GetMapChip()[moveBlockAddress_.y][moveBlockAddress_.x]
					);

					map.SetMapChip(
						moveBlockAddress_.y, moveBlockAddress_.x,
						0
					);

					break;

				default:
					break;
				}

				//プレイヤーの番地計算
				CalcAddress(
					address_,
					{ pos_.x - map.GetPuzzleLeftTop().x + 1,pos_.y - map.GetPuzzleLeftTop().y + 1 },
					{ map.GetSize().x,map.GetSize().y },
					size_.x * 0.5f,
					int(map.GetPos().size()), int(map.GetPos()[0].size())
				);

			}
		}

		Novice::ScreenPrintf(0, 100, "%d", centerAddress_.y);

		/*map.SetPos(
			3, 4,
			{ 0.0f,0.0f }
		);*/


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

		//座標が動いているときのみ処理
		if (pos_.x != prePos_.x or pos_.y != prePos_.y) {
			if (keys[DIK_UP] or keys[DIK_DOWN] or keys[DIK_LEFT] or keys[DIK_RIGHT]) {

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
					size_.x * 0.5f,
					int(map.GetPos().size()), int(map.GetPos()[0].size())
				);

				centerAddress_.x = int((pos_.x - map.GetPuzzleLeftTop().x) / map.GetSize().x);
				centerAddress_.y = int((pos_.y - map.GetPuzzleLeftTop().y) / map.GetSize().y);

				//マップチップの当たり判定
				PushBackMapChip(
					int(map.GetMapChip().size()), int(map.GetMapChip()[0].size()),
					&pos_,
					address_, preAddress_,
					size_,
					velocity_,
					map.GetPos(),
					map.GetMapChip(),
					{ map.GetSize().x,map.GetSize().y },
					isHitMapChip_
				);


				//プレイヤーの番地を再計算
				CalcAddress(
					address_,
					{ pos_.x - map.GetPuzzleLeftTop().x + 1,pos_.y - map.GetPuzzleLeftTop().y + 1 },
					{ map.GetSize().x,map.GetSize().y },
					size_.x * 0.5f,
					int(map.GetPos().size()), int(map.GetPos()[0].size())
				);

				centerAddress_.x = int((pos_.x - map.GetPuzzleLeftTop().x) / map.GetSize().x);
				centerAddress_.y = int((pos_.y - map.GetPuzzleLeftTop().y) / map.GetSize().y);
			}
		}

		//プレイヤーがスイッチを踏んだかどうか判定-------------------------------------------------
		for (int i = 0; i < 4; i++) {
			//プレイヤーが直接踏んで起動させる場合
			if (map.GetMapChipCopy()[address_[i].y][address_[i].x] == -2) {

				if (isSwitchPushable_) {
					map.SetIsPressSwitch(true);
				}
				break;
			}
		}

		for (int i = 0; i < map.GetMapChip().size(); i++) {
			for (int j = 0; j < map.GetMapChip()[0].size(); j++) {
				//ブロックを置いて起動させる場合
				if (map.GetMapChip()[i][j] == 1 or map.GetMapChip()[i][j] == 2) {
					if (map.GetMapChipCopy()[i][j] == -2) {

						if (isSwitchPushable_) {
							map.SetIsPressSwitch(true);
						}
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


//====================================================描画=============================================================
void Player::Draw(const Resources& rs) {

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
		break;

		//====================================================================================
	case CLEAR://								クリア画面
		//====================================================================================
		break;

	default:
		break;
	}

}