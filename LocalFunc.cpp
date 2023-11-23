﻿#include "LocalFunc.h"
/*===============================プレイヤーとブロックの当たり判定===================================*/
void CalcAddress(Vector2<int>* address, Vec2 pos, Vec2 size, float radius, int rowIndex, int colIndex) {

	address[LeftTop].x = int(int(pos.x - radius + 1) / size.x);
	address[LeftTop].y = int(int(pos.y - radius + 1) / size.y);

	address[RightTop].x = int(int(pos.x + radius - 1) / size.x);
	address[RightTop].y = int(int(pos.y - radius + 1) / size.y);

	address[LeftBottom].x = int(int(pos.x - radius + 1) / size.x);
	address[LeftBottom].y = int(int(pos.y + radius - 1) / size.y);

	address[RightBottom].x = int(int(pos.x + radius - 1) / size.x);
	address[RightBottom].y = int(int(pos.y + radius - 1) / size.y);

	for (int i = 0; i < 4; i++) {
		if (address[i].x >= colIndex) {
			address[i].x = colIndex - 1;

		} else if (address[i].x < 0) {
			address[i].x = 0;
		}

		if (address[i].y >= rowIndex) {
			address[i].y = rowIndex - 1;

		} else if (address[i].x < 0) {
			address[i].y = 0;
		}
	}
}

int PushBackMapChip(
	int rowMAX, int colMAX,
	Vec2* playerCenterPos,
	Vector2<int>playerAddress[4], Vector2<int>playerPreAddress[4],
	Vec2 playerSize,
	Vec2 playerVelocity,
	std::vector<std::vector<Vec2>>blockPos,
	std::vector<std::vector<int>>blockType,
	Vec2 blockSize,
	bool& isHitMapChip
) {

	enum HitSurface {
		Top = 1,
		Right = 2,
		Bottom = 3,
		Left = 4,
		Top_Right = 5,
		Right_Bottom = 6,
		Bottom_Left = 7,
		Left_Top = 8
	};

	int surface = 0;

	for (int i = 0; i < 4; i++) {

		if (playerAddress[i].x >= 0 && playerAddress[i].x < colMAX) {
			if (playerAddress[i].y >= 0 && playerAddress[i].y < rowMAX) {
				if (blockType[playerAddress[i].y][playerAddress[i].x] != 0 && 
					blockType[playerAddress[i].y][playerAddress[i].x] != 3 && 
					blockType[playerAddress[i].y][playerAddress[i].x] != 9) {
					/*------------------前フレームとX座標の番地のみが違う場合--------------------*/

					if (playerAddress[i].x != playerPreAddress[i].x &&
						playerAddress[i].y == playerPreAddress[i].y) {

						switch (i) {

						case LeftTop:

							if (playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);


								}
							}

							surface = Right;
							break;

						case RightTop:

							if (playerAddress[i].x > playerPreAddress[i].x) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

								}
							}

							surface = Left;
							break;

						case LeftBottom:

							if (playerAddress[i].x < playerPreAddress[i].x) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

								}
							}

							surface = Right;
							break;

						case RightBottom:

							if (playerAddress[i].x > playerPreAddress[i].x) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//x座標を押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

								}
							}

							surface = Left;
							break;

						default:
							break;
						}
					}

					/*------------------前フレームとY座標の番地のみが違う場合--------------------*/

					else if (playerAddress[i].x == playerPreAddress[i].x &&
						playerAddress[i].y != playerPreAddress[i].y) {

						switch (i) {

						case LeftTop:

							if (playerAddress[i].y < playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);

								}
							}

							surface = Bottom;
							break;

						case RightTop:

							if (playerAddress[i].y < playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);
								}
							}

							surface = Bottom;
							break;

						case LeftBottom:

							if (playerAddress[i].y > playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);
									surface = Top;

								}
							}

							break;

						case RightBottom:

							if (playerAddress[i].y > playerPreAddress[i].y) {
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//y座標を押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);
									surface = Top;

								}
							}

							break;

						default:
							break;
						}
					}

					/*------------------前フレームとX番地,Y番地の両方が違う場合--------------------*/

					else if (playerAddress[i].x != playerPreAddress[i].x &&
						playerAddress[i].y != playerPreAddress[i].y) {

						switch (i) {

						case LeftTop:

							//左上に侵入した場合=================================
							if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

									surface = Right_Bottom;

									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

									surface = Right;
									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);

									surface = Bottom;
									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y * 0.5f) - prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f) - prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
											(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

										surface = Right;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
											(blockSize.y * 0.5f) + (playerSize.y * 0.5f);

										surface = Bottom;
									}
								}
							}


							//左下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

								}

								surface = Right;
							}

							//右上侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);

								}

								surface = Bottom;
							}

							break;

						case RightTop:

							if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Bottom_Left;

									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Left;

									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);

									surface = Bottom;

									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y + 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] < 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y * 0.5f) - prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f) - prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

										surface = Left;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
											(blockSize.y * 0.5f) + (playerSize.y * 0.5f);
										surface = Bottom;
									}
								}

							}

							//右下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

								}

								surface = Left;
							}

							//左上に侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y +
										(blockSize.y * 0.5f) + (playerSize.y * 0.5f);

								}

								surface = Bottom;
							}

							break;

						case LeftBottom:


							if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

									surface = Top_Right;

									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

									surface = Right;

									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

									surface = Top;

									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x + 1] < 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y * 0.5f) - prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f) - prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
											(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

										surface = Right;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

										surface = Top;
									}
								}
							}

							//左上に侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x +
										(blockSize.x * 0.5f) + (playerSize.x * 0.5f);

								}

								surface = Right;
							}

							//右下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

								}

								surface = Top;
							}

							break;

						case RightBottom:

							if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								//===========================行先すべてにブロックがある場合===========================
								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//x,y両方押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Left_Top;
									//=======================プレイヤーの上にブロックがない場合========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] < 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

									surface = Left;

									//======================プレイヤーの左にブロックがない場合=========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] < 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

									surface = Top;

									//========================行先にしかブロックがない場合===========================
								} else if (blockType[playerAddress[i].y][playerAddress[i].x] == 1 &&
									blockType[playerAddress[i].y - 1][playerAddress[i].x] != 1 &&
									blockType[playerAddress[i].y][playerAddress[i].x - 1] != 1) {

									//前フレームの座標を求める
									Vector2 prePos = { playerCenterPos->x - playerVelocity.x, playerCenterPos->y - playerVelocity.y };

									/*前座標　⇒　現座標までのYの移動量の比率*/
									float rateY = sqrtf(powf(playerCenterPos->y - prePos.y, 2)) / sqrtf(powf(playerCenterPos->x - prePos.x, 2));
									/*前座標　⇒　ブロック右下までのYの移動量の比率*/
									float rateY2 =
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].y + (blockSize.y * 0.5f) - prePos.y, 2)) /
										sqrtf(powf(blockPos[playerAddress[i].y][playerAddress[i].x].x + (blockSize.x * 0.5f) - prePos.x, 2));

									if (rateY > rateY2) {
										//xを押し戻す
										playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);

										surface = Left;
									} else {
										//yを押し戻す
										playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (playerSize.y * 0.5f + 1);

										surface = Top;
									}
								}
							}


							//右上に侵入した場合=================================
							else if (playerAddress[i].y < playerPreAddress[i].y &&
								playerAddress[i].x > playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//xを押し戻す
									playerCenterPos->x = blockPos[playerAddress[i].y][playerAddress[i].x].x - (blockSize.x * 0.5f) - (playerSize.x * 0.5f);
								}

								surface = Left;
							}

							//左下に侵入した場合=================================
							else if (playerAddress[i].y > playerPreAddress[i].y &&
								playerAddress[i].x < playerPreAddress[i].x) {

								if (blockType[playerAddress[i].y][playerAddress[i].x] >= 1) {

									//yを押し戻す
									playerCenterPos->y = blockPos[playerAddress[i].y][playerAddress[i].x].y - (blockSize.y * 0.5f) - (playerSize.y * 0.5f);

								}
								surface = Top;
							}

							break;

						default:
							break;

						}
					}
				}
			} else {
				surface = false;
			}
		} else {
			surface = false;
		}
	}

	if (surface > 0) {
		isHitMapChip = true;
	}

	return surface;
}

//矩形と円の押し戻し関数
void PushBackBox_Ball(char* keys,
	Vec2 leftTop, Vec2 rightTop, Vec2 leftBottom, Vec2 rightBottom,
	Vec2 preLeftTop, Vec2 preRightTop, Vec2 preLeftBottom, Vec2 preRightBottom,
	Vec2& ballPos, Vec2 preBallPos, float ballRadius,
	bool& isDrop, bool& isJump, float& dropSpeed, float& jumpSpeed,
	int& hitCount, int& hitSurface,int preHitSurface
) {

	//矩形と円が当たっているかの判定=========================================
	float cross[4] = { 0.0f };
	int crossInCount = 0;

	keys[DIK_A];
	preBallPos;
	jumpSpeed;
	isJump;
	isDrop;
	dropSpeed;


	cross[0] = Cross(leftTop, rightTop, ballPos);
	cross[1] = Cross(rightTop, rightBottom, ballPos);
	cross[2] = Cross(rightBottom, leftBottom, ballPos);
	cross[3] = Cross(leftBottom, leftTop, ballPos);

	for (int i = 0; i < 4; i++) {
		if (cross[i] > -ballRadius) {
			crossInCount++;
		}
	}

	//円が矩形に完全に含まれていればtrue
	if (crossInCount >= 4) {

		//どの面に当たったのか判定

		//前座標の外積を求める
		float preCross[4];

		if (crossInCount >= 4) {

			Vec2 newCrossPos;
			Vec2 NormalizedVec;

			preCross[0] = Cross(preLeftTop, preRightTop, preBallPos);
			preCross[1] = Cross(preRightTop, preRightBottom, preBallPos);
			preCross[2] = Cross(preRightBottom, preLeftBottom, preBallPos);
			preCross[3] = Cross(preLeftBottom, preLeftTop, preBallPos);

			hitCount++;

			for (int i = 0; i < 4; i++) {
				if (preCross[i] <= -ballRadius) {
					hitSurface = i + 1;
				}
			}

			//当たった面に応じた処理
			
			if (hitSurface > 0) {
				switch (hitSurface) {


				case Top:

					newCrossPos = CrossPos(
						leftTop,
						rightTop,
						ballPos,
						{
						ballPos.x + VerticleVec(preLeftTop, preRightTop).x,
						ballPos.y + VerticleVec(preLeftTop, preRightTop).y
						}
					);

					NormalizedVec = Normalize({ 0.0f,0.0f }, VerticleVec(leftTop, rightTop));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius,-ballRadius }));

					isDrop = false;
					isJump = false;
					dropSpeed = 0.0f;
					jumpSpeed = 0.0f;

					break;

				case Right:

					newCrossPos = CrossPos(
						rightTop,
						rightBottom,
						ballPos,
						{
							ballPos.x + VerticleVec(preRightTop, preRightBottom).x,
							ballPos.y + VerticleVec(preRightTop, preRightBottom).y
						}
					);

					NormalizedVec = Normalize({ 0.0f,0.0f }, VerticleVec(rightTop, rightBottom));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius - 1,-ballRadius -1}));


					break;

				case Bottom:

					newCrossPos = CrossPos(
						rightBottom,
						leftBottom,
						ballPos,
						{
							ballPos.x + VerticleVec(preRightBottom, preLeftBottom).x,
							ballPos.y + VerticleVec(preRightBottom, preLeftBottom).y
						}

					);

					NormalizedVec = Normalize({ 0.0f,0.0f }, VerticleVec(rightBottom, leftBottom));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius,-ballRadius }));


					break;

				case Left:

					newCrossPos = CrossPos(
						leftBottom,
						leftTop,
						ballPos,
						{
							ballPos.x + VerticleVec(preLeftBottom, preLeftTop).x,
							ballPos.y + VerticleVec(preLeftBottom, preLeftTop).y
						}
					);

					NormalizedVec = Normalize({ 0.0f,0.0f }, VerticleVec(leftBottom, leftTop));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius - 1,-ballRadius -1}));


					break;

				default:
					break;
				}
			
			} else {

				switch (preHitSurface) {


				case Top:

					newCrossPos = CrossPos(
						leftTop,
						rightTop,
						ballPos,
						{
						ballPos.x + VerticleVec(preLeftTop, preRightTop).x,
						ballPos.y + VerticleVec(preLeftTop, preRightTop).y
						}
					);

					NormalizedVec = Normalize({ 0.0f,0.0f, }, VerticleVec(leftTop, rightTop));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius,-ballRadius }));

					isDrop = false;
					isJump = false;
					dropSpeed = 0.0f;
					jumpSpeed = 0.0f;

					break;

				case Right:

					newCrossPos = CrossPos(
						rightTop,
						rightBottom,
						ballPos,
						{
							ballPos.x + VerticleVec(preRightTop, preRightBottom).x,
							ballPos.y + VerticleVec(preRightTop, preRightBottom).y
						}
					);

					NormalizedVec = Normalize({ 0.0f,0.0f, }, VerticleVec(rightTop, rightBottom));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius - 1,-ballRadius - 1}));


					break;

				case Bottom:

					newCrossPos = CrossPos(
						rightBottom,
						leftBottom,
						ballPos,
						{
							ballPos.x + VerticleVec(preRightBottom, preLeftBottom).x,
							ballPos.y + VerticleVec(preRightBottom, preLeftBottom).y
						}

					);

					NormalizedVec = Normalize({ 0.0f,0.0f, }, VerticleVec(rightBottom, leftBottom));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius,-ballRadius }));


					break;

				case Left:

					newCrossPos = CrossPos(
						leftBottom,
						leftTop,
						ballPos,
						{
							ballPos.x + VerticleVec(preLeftBottom, preLeftTop).x,
							ballPos.y + VerticleVec(preLeftBottom, preLeftTop).y
						}
					);

					NormalizedVec = Normalize({ 0.0f,0.0f, }, VerticleVec(leftBottom, leftTop));
					ballPos = newCrossPos.operator+(NormalizedVec.operator*({ -ballRadius - 1,-ballRadius - 1}));


					break;

				default:
					break;
				}
				
			}



		} else {
			hitSurface = 0;
		}
	}
};